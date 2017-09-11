#pragma once
#include "NNTCPServerMgr.h"
#include "Singleton.h"
#include "Timer.h"
#include "RedisQueue.h"
#include "Que_DBHandler.h"
#include "Que_LogicHandler.h"
#include "Que_LoginHandler.h"
/*
管理服务器的服务器中心类
用于：初始化系统配置、启动系统网络、等待服务器连接、为客户端分配服务器、
	服务器之间跳转等
特点：先于逻辑服务器和数据服务器启动
*/
class ServerCenterMgr:public MFW::Singleton<ServerCenterMgr>
{
private:
	NNTCPServerMgr mNNTCPServerMgr;
	std::shared_ptr<std::thread> mNetThread;
public:
	DBProduce::RedisDBEngine redisHandlerEngine;
	//与其他服务器通讯队列
	std::shared_ptr<RedisQueue> mRedisQueueFDB;
	std::shared_ptr<RedisQueue> mRedisQueueTDB;
	std::shared_ptr<RedisQueue> mRedisQueueFLogin;
	std::shared_ptr<RedisQueue> mRedisQueueTLogin;
	std::shared_ptr<RedisQueue> mRedisQueueFLogic;
	std::shared_ptr<RedisQueue> mRedisQueueTLogic;

	TimerMgr mMainTimerMgr;

	void Init();
	void Start();
};
