#include "Net_LogicHandler.h"
#include "Common_Base.pb.h"
#include "Manager_Logic.pb.h"
#include "Manager_Client.pb.h"
#include "Net_ClientHandler.h"
#include "log4z.h"

#include"LogicServerMgr.h"
Net_LogicHandler::Net_LogicHandler()
{
	//ע����Ϣ����
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PManager_Logic::EMG_CMD::EMG_CMD_Register,
		std::bind(&Net_LogicHandler::HandleRegister, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4)));

	//ע����Ϣ����
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PManager_Logic::EMG_CMD::EMG_CMD_ClientKey,
		std::bind(&Net_LogicHandler::HandleClientKey, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4)));
}
void Net_LogicHandler::OnRead(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);

}
void Net_LogicHandler::OnConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("�߼����������ӳɹ�");
	
}
void Net_LogicHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("�߼��������Ͽ�");
	LogicServerMgr::GetInstance()->RemoveLogicServer(session->mId);
}
void Net_LogicHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);

}

void Net_LogicHandler::HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	LOGI("�߼�������ע��");
	PManager_Logic::GM_Register regis;
	if (!regis.ParseFromString(data))
	{
		//������Ϣ����
		return;
	}
	PManager_Logic::MG_Register response;
	response.set_ret(PCommon_Base::EPublic_Ret::EPublic_Ret_OK);
	std::shared_ptr<LogicServerInfo> logicServerInfo(new LogicServerInfo());
	logicServerInfo->Ip = session->mIP;
	logicServerInfo->Port = session->mPort;
	logicServerInfo->netNode = &netNode;
	logicServerInfo->serverKey = regis.key();
	logicServerInfo->session = session;
	logicServerInfo->ServerId = session->mId;
	LogicServerMgr::GetInstance()->AddLogicServer(logicServerInfo);
	SendData(session,netNode, cmd, &response);
	LOGI("�߼�������ע��ɹ�");
}

void Net_LogicHandler::HandleClientKey(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	PManager_Logic::GM_ClientKey clientKey;
	if (!clientKey.ParseFromString(data))
	{
		//������Ϣ����
		return;
	}
	PManager_Client::MC_Login login;
	login.set_ret(PCommon_Base::EPublic_Ret_OK);
	login.set_key(clientKey.key());
	login.set_gameip(clientKey.ip());
	login.set_gameport(clientKey.port());
	long long conid = clientKey.conid();
	NetTransMsg netTransMsg(conid, (int)PManager_Client::EMC_CMD::EMC_CMD_Login, login.SerializeAsString());
	Net_ClientHandler::GetInstance()->PushSendMsg(netTransMsg);
}