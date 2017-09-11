#pragma once

#ifndef _WIN32
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wspiapi.h>
#endif
#include <iostream>
#include <udt.h>
#include "cc.h"
#include <thread>
#include <functional>

#include "Singleton.h"
#include <map>
class UDTStartInfo
{
public:
	std::string mIp = "0.0.0.0";
	int mPort = 66666;
	bool mIsClient = false;
	std::function<void(void)> mOnConnected;
	std::function<void(void)> mOnDisConnected;
	std::function<void(void)> mOnRead;
};


class UDTServer
{
private:
	sockaddr_storage clientaddr;
	UDTSOCKET serv;
	UDTSOCKET recver;
	void* recvdata(void* usocket);
public:
	int Start(int port);
	void Stop();
};




//UDT网络管理器
class UDTServerMgr :public MFW::Singleton<UDTServerMgr>
{
private:
	std::map<int, std::shared_ptr<UDTServer>> mClients;
	std::map<int, std::shared_ptr<UDTServer>> mServers;
public:
	//启动UDT，在一个线程中运行
	void StartUdt(std::vector<UDTStartInfo>& startInfo);
};