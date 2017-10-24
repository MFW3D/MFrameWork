#include "Que_LoginHandler.h"
#include "Manager_Login.pb.h"
#include "Chess_Global.h"
#include "ClientsKeyMgr.h"

void Que_LoginHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//注册消息分发
	HandleFunctions.insert(std::pair<int, QueFunction>((int)PManager_Login::EMC_CMD_ClientKey,
		std::bind(&Que_LoginHandler::OnClientKey, this, std::placeholders::_1)));
}
void Que_LoginHandler::Process()
{
	::Que_Handler::Process();
}

void Que_LoginHandler::OnClientKey(std::string& data)
{
	PManager_Login::LM_ClientKey lm_ClientKey;
	if (!lm_ClientKey.ParseFromString(data))
	{
		return;
	}
	//制作token并返回
	std::string token = ClientsKeyMgr::GetInstance()->GetKey(lm_ClientKey.conid());
	ClientsKeyMgr::GetInstance()->SetClientsTokens(lm_ClientKey.uid(), token);

	PManager_Login::ML_ClientKey ml_ClientKey;
	ml_ClientKey.set_conid(lm_ClientKey.conid());
	ml_ClientKey.set_key(token);
	ml_ClientKey.set_ret(PCommon_Base::EPublic_Ret_OK);
	ml_ClientKey.set_uid(lm_ClientKey.uid());
	SendData((int)PManager_Login::EMC_CMD_ClientKey, &ml_ClientKey);
}