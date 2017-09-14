#pragma once
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "NNTCPServerMgr.h"
#include <string>
#include "HttpParser.h"
class HttpStartInfo
{
public:
	std::string mIp="0.0.0.0";
	int mPort = 5555;
	bool mIsClient = false;
};

class HttpMgr {
private:
	//读取连接数据
	void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	//连接进入
	void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	//连接断开
	void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	//定时器返回
	void OnTimer(uv_timer_t* handle);
public:
	std::function<void(std::shared_ptr<NNTCPLinkNode>  session, HttpRequest& httpRequest, NNTCPNode& netNode)> OnReadServerPtr = nullptr;
	std::function<void(std::shared_ptr<NNTCPLinkNode>  session, HttpResPonse& httpResPonse, NNTCPNode& netNode)> OnReadClientPtr = nullptr;
	std::function<void(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)> OnConnectedPtr = nullptr;
	std::function<void(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)> OnDisConnectedPtr = nullptr;
	std::function<void(uv_timer_t* handle)> OnTimerPtr = nullptr;
	//启动
	void Start(std::vector<HttpStartInfo> startInfos);
	//发送数据，并关闭连接
	void SendDataClient(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode, std::map<std::string, std::string> params, std::string Url);
	void SendData(std::shared_ptr<NNTCPLinkNode> session, std::string data, std::map<std::string, std::string> params, NNTCPNode& netNode);


};

