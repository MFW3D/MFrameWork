#include "Net_ManagerHandler.h"
#include "Common_Base.pb.h"
#include "log4z.h"
Net_ManagerHandler::Net_ManagerHandler()
{

}
void Net_ManagerHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetClient_Handler::OnRead(session, data, netNode);


}
void Net_ManagerHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnConnected(session, netNode);
	LOGI("������������ӳɹ�");
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