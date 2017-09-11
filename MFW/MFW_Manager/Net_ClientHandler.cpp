#include "Net_ClientHandler.h"
#include "Common_Base.pb.h"
#include "Manager_Client.pb.h"
#include "log4z.h"
Net_ClientHandler::Net_ClientHandler()
{

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