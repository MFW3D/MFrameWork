#include "Que_Handler.h"
#include "log4z.h"

void Que_Handler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	mTQue = tque;
	mFQue = fque;
}

void Que_Handler::Process()
{
	mData = "";
	while (mFQue->PopData(mData))
	{
		OnRead(mData);
	}

}
void Que_Handler::OnRead(std::string data)
{
	if (data.size() == 0)
		return;
	int headLength = (int)data[0];
	std::string headStr = data.substr(1, headLength);
	if (data.size() < headLength +1)
		return;
	data = data.substr(headLength + 1, data.size() - headLength - 1);
	PCommon_Base::NetHead head;
	if (!head.ParseFromString(headStr))
	{
		//错误连接信息，收到后关闭，防止恶性连接
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
		itr->second(msg);
	}
	data = data.substr(0, data.size()- head.datalength());
	if (data.size() > 0)
	{
		OnRead(data);
	}
}

void Que_Handler::SendData(int cmd, google::protobuf::Message* msg)
{
	std::string data = msg->SerializeAsString();
	PCommon_Base::NetHead netHead;
	netHead.set_cmd(cmd);
	netHead.set_count(1);
	netHead.set_index(1);
	netHead.set_datalength(data.size());
	netHead.set_key(0);
	int netHeadL = netHead.ByteSize();
	char netHeadLChr = (char)netHeadL;
	std::string sendData = "";
	sendData += netHeadLChr;
	sendData.append(netHead.SerializeAsString());
	sendData.append(data);
	mTQue->PushData(sendData);
}
void Que_Handler::SendData(int cmd, std::string& msg)
{
	PCommon_Base::NetHead netHead;
	netHead.set_cmd(cmd);
	netHead.set_count(1);
	netHead.set_index(1);
	netHead.set_datalength(msg.size());
	netHead.set_key(0);
	int netHeadL = netHead.ByteSize();
	char netHeadLChr = (char)netHeadL;
	std::string sendData = "";
	sendData+=netHeadLChr;
	sendData.append(netHead.SerializeAsString());
	sendData.append(msg);
	mTQue->PushData(sendData);
}

