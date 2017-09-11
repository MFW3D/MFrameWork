#include "Que_DBHandler.h"
#include "DB_Login.pb.h"
#include "Manager_Login.pb.h"
#include "Que_ManagerHandler.h"

void Que_DBHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//注册消息分发
	HandleFunctions.insert(std::pair<int, QueFunction>((int)PDB_Login::EDL_CMD_UserCheck,
		std::bind(&Que_DBHandler::OnUserCheck, this, std::placeholders::_1)));
}

void Que_DBHandler::Process()
{
	::Que_Handler::Process();
}

void Que_DBHandler::OnUserCheck(std::string& Data)
{
	PDB_Login::DL_UserCheck dl_UserCheck;
	if (!dl_UserCheck.ParseFromString(Data))
	{
		return;
	}
	if (dl_UserCheck.ret() == PCommon_Base::EPublic_Ret_OK)
	{
		//返回成功,验证账户密码
		auto clLogin = dl_UserCheck.mutable_loginmsg();
		auto dbAcc = dl_UserCheck.mutable_dbaccount();
		if (clLogin->acc() == dbAcc->sacc())
		{
			//密码正确登录系统，向manager发送服务器分配请求
			PManager_Login::LM_ClientKey lm_clientkey;
			lm_clientkey.set_uid(dl_UserCheck.dbaccount().uluid());
			lm_clientkey.set_conid(dl_UserCheck.conid());
			Que_ManagerHandler::GetInstance()->SendData((int)PManager_Login::EMC_CMD_ClientKey,&lm_clientkey);
		}
		else
		{
			//返回密码错误

		}

	}
	else
	{
		//返回错误
	}
}