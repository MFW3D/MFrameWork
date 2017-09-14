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


class HTTRequestInfo
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
	HTTRequestInfo mHTTRequest;
	std::string Data;
};


class HTTPClientMgr:public MFW::Singleton<HTTPClientMgr>
{
private:
	//http客户端的队列
	std::queue<HTTRequestInfo> mHTTRequests;
	std::mutex mHTTRequestsMutex;
	//消息恢复队列
	std::queue<HTTPResposeInfo> mHTTPResposes;
	std::mutex mHTTPResposesMutex;

	//读取连接数据
	void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	//连接进入
	void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	//连接断开
	void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	//定时器返回
	void OnTimer(uv_timer_t* handle);
	//httpclient
	void pushHTTRequest(HTTRequestInfo& hTTRequest);
	bool popHTTRequest(HTTRequestInfo& hTTRequest);
public:
	void pushHTTRequest(HTTPResposeInfo& hTTPResposeInfo);
	bool popHTTRequest(HTTPResposeInfo& hTTPResposeInfo);

	//启动http连接客户端管理器
	void Start();
	//发起一个http请求
	void AddRequest(HTTRequestInfo& hTTRequest);
};
