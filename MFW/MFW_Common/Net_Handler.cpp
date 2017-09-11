#include "Net_Handler.h"
#include "log4z.h"


void Net_Handler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	if (data.size() == 0)
		return;
	int headLength = (int)data[0];
	std::string headStr = data.substr(1, headLength);
	if (data.size() < headLength + 1)
		return;
	data = data.substr(headLength + 1, data.size() - headLength - 1);
	PCommon_Base::NetHead head;
	if (!head.ParseFromString(headStr))
	{
		//错误连接信息，收到后关闭，防止恶性连接
		//netNode.CloseSession(session);
		LOGE("error Connection");
		return;
	}
	if (data.size() < head.datalength())
		return;
	std::string msg = data.substr(0, head.datalength());
	//消息分发器
	auto itr = HandleFunctions.find(head.cmd());
	if (itr != HandleFunctions.end())
	{
		itr->second(session, head.cmd(), msg, netNode);
	}
	data = data.substr(0, data.size()- head.datalength());
	if (data.size() > 0)
	{
		OnRead(session, data, netNode);
	}
}
void Net_Handler::PushSendMsg(NetTransMsg& netTransferMsg)
{
	std::lock_guard<std::mutex> lg(SendNetTransferMsgsMutex);
	SendNetTransferMsgs.push(netTransferMsg);
}
bool Net_Handler::PopSendMsg(NetTransMsg& netTransferMsg)
{
	std::lock_guard<std::mutex> lg(SendNetTransferMsgsMutex);
	if (SendNetTransferMsgs.size() <= 0)
		return false;
	netTransferMsg = SendNetTransferMsgs.front();
	SendNetTransferMsgs.pop();
	return true;
}
void Net_Handler::SendData(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cmd, google::protobuf::Message* msg)
{
	std::string data = msg->SerializeAsString();
	PCommon_Base::NetHead netHead;
	netHead.set_cmd(cmd);
	netHead.set_count(1);
	netHead.set_index(1);
	netHead.set_key(0);
	netHead.set_datalength(data.size());
	int netHeadL = netHead.ByteSize();
	char netHeadLChr = (char)netHeadL;
	std::string sendData = "";
	sendData += netHeadLChr;
	sendData.append(netHead.SerializeAsString());
	sendData.append(data);
	netNode.SendData(session, sendData);
}
void Net_Handler::SendData(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cmd, std::string& msg)
{
	PCommon_Base::NetHead netHead;
	netHead.set_cmd(cmd);
	netHead.set_count(1);
	netHead.set_index(1);
	netHead.set_key(0);
	netHead.set_datalength(msg.size());
	int netHeadL = netHead.ByteSize();
	char netHeadLChr = (char)netHeadL;
	std::string sendData = "";
	sendData += netHeadLChr;
	sendData.append(netHead.SerializeAsString());
	sendData.append(msg);
	netNode.SendData(session, sendData);
}

void NetClient_Handler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::Net_Handler::OnRead(session, data, netNode);
	mServerNetNode = &netNode;
	mServerSession = session;
}
void NetClient_Handler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	mServerNetNode = &netNode;
	mServerSession = session;
}
void NetClient_Handler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	mServerNetNode = &netNode;
	mServerSession = session;
}
void NetClient_Handler::OnTimered(uv_timer_t* handle)
{
	if (mServerNetNode == nullptr ||
		mServerSession == nullptr)
		return;
	//封包发送
	PCommon_Base::NetTransferMsgs netTransferMsgs;
	NetTransMsg netTransferMsg;
	while (true)
	{
		if (PopSendMsg(netTransferMsg))
		{
			PCommon_Base::NetTransferMsg* msg = netTransferMsgs.add_nettransfermsgs();
			msg->set_id(netTransferMsg.GetNetId());
			msg->set_data(netTransferMsg.GetData());
		}
		else
		{
			break;
		}
	}
	if (netTransferMsgs.nettransfermsgs_size() > 0)
	{
		SendData(mServerSession, *mServerNetNode, (int)PCommon_Base::EPublic_CMD::EPublic_CMD_PackTransferMsg, &netTransferMsgs);
	}
}


void NetServer_Handler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::Net_Handler::OnRead(session, data, netNode);
	mServerNetNode = (NNTCPServer*)&netNode;
}
void NetServer_Handler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	mServerNetNode = (NNTCPServer*)&netNode;
}
void NetServer_Handler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	mServerNetNode = (NNTCPServer*)&netNode;
}
void NetServer_Handler::OnTimered(uv_timer_t* handle)
{
	if (mServerNetNode == nullptr)
		return;
	//发送到对应客户端
	NetTransMsg netTransferMsg;
	while (true)
	{
		if (PopSendMsg(netTransferMsg))
		{
			auto itr = mServerNetNode->Clients.find(netTransferMsg.GetNetId());
			if (itr == mServerNetNode->Clients.end())
			{
				continue;
			}
			SendData(itr->second, *mServerNetNode, netTransferMsg.GetCmd(), netTransferMsg.GetData());
		}
		else
		{
			break;
		}
	}
}