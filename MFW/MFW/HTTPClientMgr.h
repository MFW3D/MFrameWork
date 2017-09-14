#pragma once
#include "Singleton.h"
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "NNTCPServerMgr.h"
#include <string>
#include "HttpParser.h"
/*
作为http客户端连接管理器
*/


/*
作为一个webclient
1、loop一直执行着
2、定时器检查请求
3、执行请求
4、收到数据返回上一层
*/


class HTTPRequestInfo
{
public:
	std::function<void(HttpResPonse& httpResPonse, NNTCPNode& netNode)> OnReadClientPtr = nullptr;
	std::string ip = "";
	int port = 0;
	std::string url = "";
	std::map<std::string, std::string> params;
	std::string body;
};

class HTTPResposeInfo
{
	HTTPRequestInfo mHTTRequest;
	std::string Data;
};


class HTTPClientMgr:public MFW::Singleton<HTTPClientMgr>
{
private:
	//http客户端的队列
	std::queue<HTTPRequestInfo> mHTTRequests;
	std::mutex mHTTRequestsMutex;
	//消息恢复队列
	std::queue<HTTPResposeInfo> mHTTPResposes;
	std::mutex mHTTPResposesMutex;

	void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	void OnTimer(uv_timer_t* handle);
public:
	void start();
	//httpclient
	void pushHTTRequest(HTTPRequestInfo& hTTRequest);
	bool popHTTRequest(HTTPRequestInfo& hTTRequest);
	void pushHTTRequest(HTTPResposeInfo& hTTPResposeInfo);
	bool popHTTRequest(HTTPResposeInfo& hTTPResposeInfo);
};
