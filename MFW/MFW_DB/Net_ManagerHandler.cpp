#include "Net_ManagerHandler.h"
#include "Common_Base.pb.h"
#include "DB_Manager.pb.h"
#include "log4z.h"
Net_ManagerHandler::Net_ManagerHandler()
{

}
void Net_ManagerHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void Net_ManagerHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("管理服务器连入");
}
void Net_ManagerHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("管理服务器断开");
}
void Net_ManagerHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);
}
