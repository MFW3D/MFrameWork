#pragma once
#include "HttpMgr.h"
#include "Singleton.h"
#include "Timer.h"
/*
管理服务器的服务器中心类
用于：初始化系统配置、启动系统网络、等待服务器连接、为客户端分配服务器、
服务器之间跳转等
特点：先于逻辑服务器和数据服务器启动
*/
class ServerCenterMgr :public Singleton<ServerCenterMgr>
{
private:
	NNTCPServerMgr mNNTCPServerMgr;
	HttpMgr httpMgr;
	//客户端处理线程
	std::shared_ptr<std::thread> mNetClientThread;

public:
	TimerMgr mMainTimerMgr;
	void Init();
	void Start();
};
