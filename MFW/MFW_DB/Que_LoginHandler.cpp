#include "Que_LoginHandler.h"
#include "DB_Login.pb.h"
#include "RedisReader.h"
#include "DBTypes.h"
#include "Common_Base.pb.h"
#include "AssistantMG.h"

void Que_LoginHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//注册消息分发
	HandleFunctions.insert(std::pair<int, QueFunction>((int)PDB_Login::EDL_CMD_UserCheck,
		std::bind(&Que_LoginHandler::OnUserCheck,this,std::placeholders::_1)));
}
void Que_LoginHandler::Process()
{
	::Que_Handler::Process();
}


void Que_LoginHandler::OnUserCheck(std::string& Data)
{
	PDB_Login::LD_UserCheck usercheck;
	if (!usercheck.ParseFromString(Data))
	{
		return;
	}
	long long uid=-1;
	if (!AssistantMG::GetInstance()->GetUserId(uid, usercheck.loginmsg().acc()))
	{
		return;
	}
	if (uid == -1)
	{
		return;
	}
	std::shared_ptr<DBProduce::DBAccount> AccountPtr(new DBProduce::DBAccount());
	if (!DBProduce::RedisReader::GetDBAccount(AccountPtr, std::to_string(uid)))
	{
		return;
	}
	//回复loginServer
	PDB_Login::DL_UserCheck dl_userCheck;
	dl_userCheck.set_conid(usercheck.conid());
	auto clLogin = dl_userCheck.mutable_loginmsg();
	*clLogin = *usercheck.mutable_loginmsg();
	auto dbAcc = dl_userCheck.mutable_dbaccount();
	dbAcc->set_uluid(AccountPtr->uid);
	dbAcc->set_sacc(AccountPtr->acc);
	dbAcc->set_spwd(AccountPtr->pwd);
	dbAcc->set_stel(AccountPtr->tel);
	dbAcc->set_swx(AccountPtr->wx);
	dbAcc->set_sqq(AccountPtr->qq);
	dbAcc->set_ullastlogin(AccountPtr->lastlogin);
	dbAcc->set_ulcreatetime(AccountPtr->createtime);
	dl_userCheck.set_ret(0);
	SendData((int)PDB_Login::EDL_CMD_UserCheck, &dl_userCheck);
}