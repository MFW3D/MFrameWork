//#include "Net_ClientHandler.h"
//#include "NetUtility.h"
//#include "log4z.h"
//#include<tchar.h>
//#include<locale>
//#include<codecvt>
//#include<iostream>
//#include "Common_Base.pb.h"
//#include "Login_Client.pb.h"
//#include "Net_Handler.h"
//#include "Net_DBHandler.h"
//
//using namespace std;
//using namespace zsummer::log4z;
//void Net_ClientHandler::init()
//{
//}
//void Net_ClientHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, HttpRequest& httpRequest, NNTCPNode& netNode)
//{
//	std::string data = httpRequest.GetUrl();
//	if (httpRequest.GetMethod() != EHttpMethod::POST)
//	{
//		std::map<std::string, std::string>params;
//		httpMgr.SendData(session, "error", params,netNode);
//		return;
//	}
//	PCommon_Base::NetHead head;
//	if (!head.ParseFromString(data))
//	{
//		std::map<std::string, std::string>params;
//		httpMgr.SendData(session, "error", params, netNode);
//		LOGI("Error msg head");
//		return;
//	}
//	std::string msg = data.substr(head.ByteSize(), head.datalength());
//	switch (head.cmd())
//	{
//	case (int)PLogin_Client::ELC_CMD_Login:
//		break;
//	default:
//		break;
//	}
//	return;
//}
//void Net_ClientHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
//{
//	LOGI("Client Connected IP:"<<session->mIPStr<<" port"<<session->mPort);
//}
//void Net_ClientHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
//{
//	LOGI("Client DisConnected IP:" << session->mIPStr << " port" << session->mPort);
//}
//void Net_ClientHandler::OnTime()
//{
//
//}
//
//void Net_ClientHandler::HandleLogin(std::shared_ptr<NNTCPLinkNode>&  session, int& cmd, std::string& data, NNTCPNode& netNode)
//{
//	PLogin_Client::CL_Login login;
//	if (login.ParseFromString(data))
//	{
//		std::map<std::string, std::string>params;
//		httpMgr.SendData(session, "error", params, netNode);
//		LOGI("Error msg");
//		return;
//	}
//	//传给数据服务器做处理
//	NetTransMsg netTransMsg(session->mId,cmd,data);
//	Net_DBHandler::GetInstance()->PushSendMsg(netTransMsg);
//}
//void Net_ClientHandler::HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, int& cmd, std::string& data, NNTCPNode& netNode)
//{
//	
//}