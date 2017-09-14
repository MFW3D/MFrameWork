#pragma once
#include "Singleton.h"
#include <iostream>
#include <stdlib.h>
#include <memory>
#include "NNTCPServerMgr.h"
#include <string>
#include "HttpParser.h"
/*
��Ϊhttp�ͻ������ӹ�����
*/


/*
��Ϊһ��webclient
1��loopһֱִ����
2����ʱ���������
3��ִ������
4���յ����ݷ�����һ��
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
	//http�ͻ��˵Ķ���
	std::queue<HTTPRequestInfo> mHTTRequests;
	std::mutex mHTTRequestsMutex;
	//��Ϣ�ָ�����
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
