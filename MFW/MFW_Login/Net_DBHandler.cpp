#include "Net_DBHandler.h"
#include "Common_Base.pb.h"
#include "log4z.h"

Net_DBHandler::Net_DBHandler()
{

}
void Net_DBHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetClient_Handler::OnRead(session, data, netNode);

}
void Net_DBHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnConnected(session,netNode);
	LOGI("���ݷ��������ӳɹ�");
}
void Net_DBHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetClient_Handler::OnDisConnected(session, netNode);
	LOGI("�Ͽ����ݷ���������");
}
void Net_DBHandler::OnTimered(uv_timer_t* handle)
{
	::NetClient_Handler::OnTimered(handle);

}