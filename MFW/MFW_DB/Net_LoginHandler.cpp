#include "Net_LoginHandler.h"
#include "Common_Base.pb.h"
#include "DB_Login.pb.h"
#include "log4z.h"
Net_LoginHandler::Net_LoginHandler()
{
	//注册消息处理
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PCommon_Base::EPublic_CMD::EPublic_CMD_PackTransferMsg,
		std::bind(&Net_LoginHandler::HandleLoginPackMsg, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4)));
}
void Net_LoginHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void Net_LoginHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("登录服务器连入");
}
void Net_LoginHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("登录服务器断开");

}
void Net_LoginHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);
}


void Net_LoginHandler::HandleLoginPackMsg(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	//解析玩家打包消息
	PCommon_Base::NetTransferMsgs netTransferMsgs;
	if (!netTransferMsgs.ParseFromString(data))
	{
		LOGE("Error Info");
		return;
	}
	//验证玩家账户信息



}