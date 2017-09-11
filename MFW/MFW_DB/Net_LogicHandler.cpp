#include "Net_LogicHandler.h"
#include "Common_Base.pb.h"
#include "DB_Logic.pb.h"
#include "log4z.h"
Net_LogicHandler::Net_LogicHandler()
{

}
void Net_LogicHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void Net_LogicHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("逻辑服务器连入");
}
void Net_LogicHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("逻辑服务器断开");
}
void Net_LogicHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);
}

void Net_LogicHandler::OnIdentification(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	PDB_Logic::LDIdentification ldIdentification;
	if (!ldIdentification.ParseFromString(data))
	{
		return;
	}
}