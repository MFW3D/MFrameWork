#pragma once
#include "Timer.h"

//功能模块
#include "ThreadDBWriteBack.h"
#include "ServerGlobal.h"

#include "RedisHandler.h"
#include "DBReader.h"
#include "RedisReader.h"
#include "WriteBackMgr.h"
#include "DBWriter.h"
#include "RedisWriter.h"
#include "AssistantMG.h"
#include "RedisAssistantHandler.h"
#include "SimpleIni.h"
#include "Timer.h"
#include "log4z.h"
#include "Singleton.h"
#include "NNTCPServerMgr.h"
#include "RedisQueue.h"
#include "Que_LogicHandler.h"
#include "Que_LoginHandler.h"
#include "Que_ManagerHandler.h"

const uint32_t IP_MAX_SIZE = 18;
const uint32_t Other_MAX_SIZE = 128;

class ServerCenterMgr :public MFW::Singleton<ServerCenterMgr>
{
private:
	 DBProduce::SQLDBEngine dBSQLEngine;
	 DBProduce::RedisDBEngine redisHandlerEngine;
	 void InitPlans();
	 std::shared_ptr<std::thread> mNetThread;
	 NNTCPServerMgr mNNTCPServerMgr;

public:
	//与其他服务器通讯队列
	std::shared_ptr<RedisQueue> mRedisQueueFLogin;
	std::shared_ptr<RedisQueue> mRedisQueueTLogin;
	std::shared_ptr<RedisQueue> mRedisQueueFLogic;
	std::shared_ptr<RedisQueue> mRedisQueueTLogic;
	std::shared_ptr<RedisQueue> mRedisQueueFManager;
	std::shared_ptr<RedisQueue> mRedisQueueTManager;

	//初始化服务器
	 void InitServer();
	//启动服务器
	 bool StartServer();
	//关闭服务器
	 bool CloseServer();
	//启动异步业务
	 bool StartTask();

	 DBProduce::RedisDBEngine redisDBEngine;
	 ThreadDBWriteBack threadDBWriteBack;
};
