#include "Net_ClientHandler.h"
#include "Common_Base.pb.h"
#include "DB_Option.pb.h"
#include "Net_DBHandler.h"
#include "log4z.h"
#include <functional>
#include <memory>

Net_ClientHandler::Net_ClientHandler()
{
	//注册消息处理
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PLogin_Client::ELC_CMD::ELC_CMD_Login,
			std::bind(&Net_ClientHandler::HandleLogin, this,
				std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4)));
}
void Net_ClientHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void Net_ClientHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("数据服务器连接成功");
}
void Net_ClientHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("断开数据服务器连接");
}
void Net_ClientHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);

}

void Net_ClientHandler::HandleLogin(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	PLogin_Client::CL_Login login;
	if (login.ParseFromString(data))
	{
		return;
	}
}
void Net_ClientHandler::HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	
}