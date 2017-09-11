#include "Que_ManagerHandler.h"
#include "Manager_Login.pb.h"
#include "Common_Base.pb.h"
#include "Login_Client.pb.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"

void Que_ManagerHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);

	//注册消息分发
	HandleFunctions.insert(std::pair<int, QueFunction>((int)PManager_Login::EMC_CMD_ClientKey,
		std::bind(&Que_ManagerHandler::OnClientKey, this, std::placeholders::_1)));

}
void Que_ManagerHandler::Process()
{
	::Que_Handler::Process();
}

void Que_ManagerHandler::OnClientKey(std::string& data)
{
	PManager_Login::ML_ClientKey ml_ClientKey;
	if (!ml_ClientKey.ParseFromString(data))
	{
		return ;
	}
	if (ml_ClientKey.ret() == PCommon_Base::EPublic_Ret_OK)
	{
		//成功获取到token
		PLogin_Client::LC_Login lc_login;
		lc_login.set_key(ml_ClientKey.key());
		lc_login.set_ret(PCommon_Base::EPublic_Ret_OK);
		lc_login.set_uid(ml_ClientKey.uid());
		lc_login.set_managerip(ServerCfg::GetInstance()->Manager_IP);
		lc_login.set_managerport(ServerCfg::GetInstance()->Manager_Port2Client);
		long long conid = ml_ClientKey.conid();
		NetTransMsg netTransMsg(conid,(int)PLogin_Client::ELC_CMD_Login, lc_login.SerializeAsString());
		Net_ClientHandler::GetInstance()->PushSendMsg(netTransMsg);
	}
	else
	{
		//返回失败


		return;
	}

}