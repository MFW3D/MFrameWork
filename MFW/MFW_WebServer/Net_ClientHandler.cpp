#include "Net_ClientHandler.h"
#include "NetUtility.h"
#include "log4z.h"
#include<tchar.h>
#include<locale>
#include<codecvt>
#include<iostream>
#include "Common_Base.pb.h"
#include "Login_Client.pb.h"
#include "Net_Handler.h"

using namespace std;
using namespace zsummer::log4z;
void Net_ClientHandler::init()
{
}
void Net_ClientHandler::OnRead(std::shared_ptr<NNTCPLinkNode>  session, HttpRequest& httpRequest, NNTCPNode& netNode)
{

	if (httpRequest.GetMethod() != EHttpMethod::POST)
	return;
	std::string url = httpRequest.GetUrl();
	std::string body = httpRequest.GetBody();
	std::map<std::string, std::string>params;
	httpMgr.SendData(session, "hello", params, netNode);
	HandleData(session, body, netNode);
	return;
}
void Net_ClientHandler::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	LOGI("Client Connected IP:" << session->mIPStr << " port" << session->mPort);
}
void Net_ClientHandler::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	LOGI("Client DisConnected IP:" << session->mIPStr << " port" << session->mPort);
}
void Net_ClientHandler::OnTime()
{

}


void Net_ClientHandler::HandleData(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(data, root))
	{
		return;
	}

	int cgsid = root["cgsId"].asInt();
	Json::Value dd = root["data"];
	HandleMsgData(session, netNode,cgsid, dd);
	//std::map<std::string, std::string>params;
	//httpMgr.SendData(session, "hello", params, netNode);
}
void Net_ClientHandler::HandleMsgData(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid, Json::Value data)
{
	EMethod method = (EMethod)data["EMethod"].asInt();
	switch (method)
	{
	case EMethod::ECreateGameTable:
	{
		CreateGameTable(session, netNode, cgsid, data);
	}
	break;
	case EMethod::EDestroyGameTable:
	{
		DestroyGameTable(session, netNode, cgsid, data);
	}
	break;
	case EMethod::EGameTableStartGame:
	{
		GameTableStartGame(session, netNode, cgsid, data);
	}
	break;
	case EMethod::EGameTableGetState:
	{
		GameTableGetState(session, netNode, cgsid, data);
	}
	break;
	case EMethod::EGameTableSetAction:
	{
		GameTableSetAction(session, netNode, cgsid, data);
	}
	break;
	case EMethod::EGameTableResetGame:
	{
		GameTableResetGame(session, netNode, cgsid, data);
	}
	break;
	default:
		break;
	}
}

void Net_ClientHandler::CreateGameTable(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid, Json::Value data)
{
	Json::Value root;
	root["cgsId"] = Json::Value(cgsid);

	std::map<std::string, std::string>params;
	httpMgr.SendData(session, "hello", params, netNode);
}
void Net_ClientHandler::DestroyGameTable(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode,  int cgsid, Json::Value data)
{

}
void Net_ClientHandler::GameTableStartGame(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode,  int cgsid, Json::Value data)
{

}
void Net_ClientHandler::GameTableGetState(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode,  int cgsid, Json::Value data)
{

}
void Net_ClientHandler::GameTableSetAction(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid, Json::Value data)
{

}
void Net_ClientHandler::GameTableResetGame(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode,int cgsid, Json::Value data)
{
}