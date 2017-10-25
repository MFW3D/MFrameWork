#include "MFW3D_NetHandler.h"
#include "Common_Base.pb.h"
#include "DB_Login.pb.h"
#include "DB_Option.pb.h"
#include "DB_Login.pb.h"
#include "log4z.h"
#include <functional>
#include <memory>

MFW3D_NetHandler::MFW3D_NetHandler()
{
	//注册消息处理
	HandleFunctions.insert(std::pair<int, HandleBackFunction>((int)PLogin_Client::ELC_CMD::ELC_CMD_Login,
			std::bind(&MFW3D_NetHandler::HandleLogin, this,
				std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4)));
}
void MFW3D_NetHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	::NetServer_Handler::OnRead(session, data, netNode);
}
void MFW3D_NetHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnConnected(session, netNode);
	LOGI("数据服务器连接成功");
}
void MFW3D_NetHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	::NetServer_Handler::OnDisConnected(session, netNode);
	LOGI("断开数据服务器连接");
}
void MFW3D_NetHandler::OnTimered(uv_timer_t* handle)
{
	::NetServer_Handler::OnTimered(handle);

}

void MFW3D_NetHandler::HandleLogin(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
}
void MFW3D_NetHandler::HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode)
{
	
}