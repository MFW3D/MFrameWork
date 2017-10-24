#include "Net_ManagerHandler.h"
#include "Manager_Logic.pb.h"
#include "Common_Base.pb.h"
#include "ServerGlobal.h"
#include "log4z.h"
Net_ManagerHandler::Net_ManagerHandler()
{
	//ע����Ϣ����
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PManager_Logic::EMG_CMD::EMG_CMD_Register,
		std::bind(&Net_ManagerHandler::HandleRegister, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4)));
	//ע����Ϣ����
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PManager_Logic::EMG_CMD::EMG_CMD_ClientKey,
		std::bind(&Net_ManagerHandler::HandleLogin, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4)));
}
void Net_ManagerHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetClient_Handler::OnRead(session, data, netNode);


}
void Net_ManagerHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnConnected(session, netNode);
	LOGI("������������ӳɹ�");
	//����ע����Ϣ
	PManager_Logic::GM_Register regis;
	regis.set_key("dasdasdaqsd");
	SendData(session, netNode, (int)PManager_Logic::EMG_CMD_Register, &regis);
}
void Net_ManagerHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnDisConnected(session, netNode);
	LOGI("�Ͽ��������������");
}
void Net_ManagerHandler::OnTimered(uv_timer_t* handle)
{
	::NetClient_Handler::OnTimered(handle);

}


void Net_ManagerHandler::HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	PManager_Logic::MG_Register response;
	if (!response.ParseFromString(data))
	{
		//������Ϣ����
		return;
	}
	if (response.ret() == 0)
	{
		LOGI("���������ע��ɹ�");
	}
	else
	{
		LOGI("���������ע��ʧ��");
	}


}


void Net_ManagerHandler::HandleLogin(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	PManager_Logic::MG_ClientKey  clientKey;
	if (!clientKey.ParseFromString(data))
	{
		//������Ϣ����
		return;
	}
	PManager_Logic::GM_ClientKey  response;
	response.set_conid(clientKey.conid());
	response.set_ret(PCommon_Base::EPublic_Ret_OK);
	response.set_uid(clientKey.uid());
	response.set_ip(ServerCfg::GetInstance()->Logic_IP);
	response.set_port(ServerCfg::GetInstance()->Logic_Port2Client);
	response.set_ret(PCommon_Base::EPublic_Ret::EPublic_Ret_OK);
	response.set_key(clientKey.key());
	LOGI("�洢���key�ɹ�");
	SendData(session, netNode, (int)PManager_Logic::EMG_CMD_ClientKey, &response);
}