#include "Net_ClientHandler.h"
#include "Common_Base.pb.h"
#include "Manager_Client.pb.h"
#include "Manager_Logic.pb.h"
#include "ClientsKeyMgr.h"
#include "Net_LogicHandler.h"
#include "LogicServerMgr.h"
#include "log4z.h"
Net_ClientHandler::Net_ClientHandler()
{
	//ע����Ϣ����
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PManager_Client::EMC_CMD::EMC_CMD_Login,
		std::bind(&Net_ClientHandler::HandleLogin, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4)));
}
void Net_ClientHandler::OnRead(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void Net_ClientHandler::OnConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("�ͻ��˳ɹ�");

}
void Net_ClientHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("�ͻ��˶Ͽ�");
}
void Net_ClientHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);

}

void Net_ClientHandler::HandleLogin(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	PManager_Client::CM_Login login;
	if (!login.ParseFromString(data))
	{
		//������Ϣ����
		return;
	}
	std::string key = "";
	if (ClientsKeyMgr::GetInstance()->GetClientsTokens(login.uid(), key))
	{
		if (key == login.key())
		{
			LOGI("��ҵ�¼��֤�ɹ�,������Ϸ������");
			PManager_Logic::MG_ClientKey  clientKey;
			clientKey.set_conid(session->mId);
			clientKey.set_key(key);
			clientKey.set_uid(login.uid());
			long long conid = LogicServerMgr::GetInstance()->DistributePlayer(login.uid());
			NetTransMsg netTransMsg(conid, (int)PManager_Logic::EMG_CMD::EMG_CMD_ClientKey, clientKey.SerializeAsString());
			Net_LogicHandler::GetInstance()->PushSendMsg(netTransMsg);
		}
	}
	else
	{
		LOGI("���δ���е�¼��֤");
	}
}