#include "Net_LoginHandler.h"
#include "Common_Base.pb.h"
#include "Manager_Login.pb.h"
#include "log4z.h"

Net_LoginHandler::Net_LoginHandler()
{

}

void Net_LoginHandler::OnRead(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void Net_LoginHandler::OnConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("��¼���������ӳɹ�");
}
void Net_LoginHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("�߼��������Ͽ�");
}
void Net_LoginHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);

}