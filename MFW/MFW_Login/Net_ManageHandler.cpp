#include "Net_ManageHandler.h"
#include "Common_Base.pb.h"
#include "Manager_Logic.pb.h"
#include "log4z.h"
#include "ServerGlobal.h"
Net_ManageHandler::Net_ManageHandler()
{
	//注册消息处理
}
void Net_ManageHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetClient_Handler::OnRead(session, data, netNode);


}
void Net_ManageHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnConnected(session, netNode);
	LOGI("管理服务器连接成功");
}
void Net_ManageHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnDisConnected(session, netNode);
	LOGI("断开管理服务器连接");
}
void Net_ManageHandler::OnTimered(uv_timer_t* handle)
{
	::NetClient_Handler::OnTimered(handle);

}
