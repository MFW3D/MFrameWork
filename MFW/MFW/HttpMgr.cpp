#include "HttpMgr.h"
#include <fstream>
#include "HttpParser.h"

void HttpMgr::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	if (netNode.nNNodeInfo.IsClient)
	{
		HttpResPonse httpResPonse;
		if (HttpParser::ParseDataResponse(data, httpResPonse))
		{
			if (OnReadClientPtr != nullptr)
			{
				OnReadClientPtr(session, httpResPonse, netNode);
			}
		}
		else
		{

		}
	}
	else
	{
		HttpRequest httpRequest;
		if (HttpParser::ParseDataRequest(data, httpRequest))
		{
			if (OnReadServerPtr != nullptr)
			{
				OnReadServerPtr(session, httpRequest, netNode);
			}
		}
		else
		{

		}
	}
}
void HttpMgr::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	if (OnConnectedPtr != nullptr)
	{
		OnConnectedPtr(session, netNode);
	}
}
void HttpMgr::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	if (OnDisConnectedPtr != nullptr)
	{
		OnDisConnectedPtr(session, netNode);
	}
}
void HttpMgr::OnTimer(uv_timer_t* handle)
{
}
void HttpMgr::Start(std::vector<HttpStartInfo> startInfos)
{
	std::vector<NNNodeInfo> nodes;
	for (int i = 0; i < startInfos.size(); i++)
	{
		NNNodeInfo nNNodeInfo;
		nNNodeInfo.Ip = startInfos[i].mIp;
		nNNodeInfo.IsClient = startInfos[i].mIsClient;
		nNNodeInfo.Port = startInfos[i].mPort;
		nNNodeInfo.OnConnected = std::bind(&HttpMgr::OnConnected, this, std::placeholders::_1, std::placeholders::_2);
		nNNodeInfo.OnDisConnected = std::bind(&HttpMgr::OnDisConnected, this, std::placeholders::_1, std::placeholders::_2);
		nNNodeInfo.OnRead = std::bind(&HttpMgr::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		nNNodeInfo.OnTimered = std::bind(&HttpMgr::OnTimer, this, std::placeholders::_1);
		nodes.push_back(nNNodeInfo);
	}

	NNTCPServerMgr::RunServer(nodes);
}
void HttpMgr::SendDataClient(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode, std::map<std::string, std::string> params, std::string Url)
{
	if (netNode.nNNodeInfo.IsClient)
	{
		HttpRequest httpRequest;
		httpRequest.SetUrl(Url);
		httpRequest.SetVesionMajor(1);
		httpRequest.SetVesionMinor(1);
		httpRequest.SetMethod(EHttpMethod::GET);
		for (auto itr = params.begin(); itr != params.end(); itr++)
		{
			httpRequest.AddParam(itr->first, itr->second);
		}
		httpRequest.SetBody(data);
		//回复客户端
		std::string responsestr = "";
		if (httpRequest.ParseToString(responsestr))
		{
			SendData(session, responsestr, params, netNode);
		}
		else
		{
			responsestr = "HTTP/1.1 200 OK \r\n\r\n error";
			SendData(session, responsestr, params,netNode);
		}
		SendData(session, responsestr, params,netNode);
	}
}
void HttpMgr::SendData(std::shared_ptr<NNTCPLinkNode> session, std::string data, 
	std::map<std::string, std::string> params, NNTCPNode& netNode)
{
	if (!netNode.nNNodeInfo.IsClient)
	{
		HttpResPonse httpResPonse;
		httpResPonse.SetStatus(200);
		httpResPonse.SetVesionMajor(1);
		httpResPonse.SetVesionMinor(1);
		httpResPonse.AddParam("Server", "MFWServer");
		httpResPonse.AddParam("Date", NetUtility::getCurrentSystemTimeGMT());
		httpResPonse.AddParam("Content-Length", std::to_string(data.size()));
		httpResPonse.AddParam("Content-Type", "text/html");

		for (auto itr = params.begin(); itr != params.end(); itr++)
		{
			httpResPonse.AddParam(itr->first, itr->second);
		}
		httpResPonse.SetBody(data);
		//回复客户端
		std::string responsestr = "";
		if (httpResPonse.ParseToString(responsestr))
		{
			netNode.SendData(session, responsestr);
			netNode.CloseSession(session);
		}
		else
		{
			responsestr = "HTTP/1.1 200 OK \r\nContent-Length:2\r\nContent-Type:text/html\r\n\r\n error";
			netNode.SendData(session, responsestr);
			netNode.CloseSession(session);
		}

	}
}
