#include "ServerCenterMgr.h"
#include "ServerGlobal.h"
#include "Timer.h"
#include "Net_LoginHandler.h"
#include "Net_LogicHandler.h"
#include "Net_DBHandler.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"
#include "log4z.h"

#if _WIN32
#else
#include <unistd.h>
#endif

void ServerCenterMgr::Init()
{
	//初始化全局变量
	ServerGlobal::GetInstance()->Init("./servercfg.ini");

	redisHandlerEngine.connect(ServerCfg::GetInstance()->DB_RedisIp.c_str(),
		ServerCfg::GetInstance()->DB_RedisPort);
	//配置与其他服务器通讯的消息队列
	mRedisQueueFLogin = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_login_manager));
	mRedisQueueTLogin = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_manager_login));
	mRedisQueueFLogic = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_logic_manager));
	mRedisQueueTLogic = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_manager_logic));
	mRedisQueueFDB = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_db_manager));
	mRedisQueueTDB = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_manager_db));
	Que_LoginHandler::GetInstance()->Init(mRedisQueueTLogin,mRedisQueueFLogin);
	Que_LogicHandler::GetInstance()->Init(mRedisQueueTLogic,mRedisQueueFLogic);
	Que_DBHandler::GetInstance()->Init(mRedisQueueTDB,mRedisQueueFDB);
}
void ServerCenterMgr::Start()
{
	//启动网络
	LOGI("启动网络");

	mNetThread = std::shared_ptr<std::thread>(new std::thread([&]() {
		std::vector<NNNodeInfo> NNNodeInfos;
		//NNNodeInfo NNNodeInfo_Login;
		NNNodeInfo NNNodeInfo_Logic;
		//NNNodeInfo NNNodeInfo_DB;
		NNNodeInfo NNNodeInfo_Client;
#if _WIN32
		//NNNodeInfo_Login.Ip = "127.0.0.1";
		NNNodeInfo_Logic.Ip = "127.0.0.1";
		NNNodeInfo_Client.Ip = "127.0.0.1";
#else
		NNNodeInfo_Login.Ip = "0.0.0.0";
		NNNodeInfo_Logic.Ip = "0.0.0.0";
		NNNodeInfo_Client.Ip = "0.0.0.0";

#endif
		//NNNodeInfo_DB.Ip = ServerCfg::GetInstance()->DB_IP;

		//NNNodeInfo_Login.Port = ServerCfg::GetInstance()->Manager_Port2Login;
		NNNodeInfo_Logic.Port = ServerCfg::GetInstance()->Manager_Port2Logic;
		//NNNodeInfo_DB.Port = ServerCfg::GetInstance()->DB_Port2Manager;
		NNNodeInfo_Client.Port = ServerCfg::GetInstance()->Manager_Port2Client;

		//NNNodeInfo_Login.IsClient = false;
		NNNodeInfo_Logic.IsClient = false;
		//NNNodeInfo_DB.IsClient = true;
		NNNodeInfo_Client.IsClient = false;

		//NNNodeInfo_Login.OnConnected = std::bind(&Net_LoginHandler::OnConnected, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Logic.OnConnected = std::bind(&Net_LogicHandler::OnConnected, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);
		//NNNodeInfo_DB.OnConnected = std::bind(&Net_DBHandler::OnConnected, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Client.OnConnected = std::bind(&Net_ClientHandler::OnConnected, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);

		//NNNodeInfo_Login.OnDisConnected = std::bind(&Net_LoginHandler::OnDisConnected, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Logic.OnDisConnected = std::bind(&Net_LogicHandler::OnDisConnected, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);
		//NNNodeInfo_DB.OnDisConnected = std::bind(&Net_DBHandler::OnDisConnected, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Client.OnDisConnected = std::bind(&Net_ClientHandler::OnDisConnected, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);

		//NNNodeInfo_Login.OnRead = std::bind(&Net_LoginHandler::OnRead, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		NNNodeInfo_Logic.OnRead = std::bind(&Net_LogicHandler::OnRead, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		//NNNodeInfo_DB.OnRead = std::bind(&Net_DBHandler::OnRead, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		NNNodeInfo_Client.OnRead = std::bind(&Net_ClientHandler::OnRead, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);


		//NNNodeInfo_Login.OnTimered = std::bind(&Net_LoginHandler::OnTimered, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1);
		NNNodeInfo_Logic.OnTimered = std::bind(&Net_LogicHandler::OnTimered, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1);
		//NNNodeInfo_DB.OnTimered = std::bind(&Net_DBHandler::OnTimered, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1);
		NNNodeInfo_Client.OnTimered = std::bind(&Net_ClientHandler::OnTimered, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1);

		//NNNodeInfos.push_back(NNNodeInfo_Login);
		NNNodeInfos.push_back(NNNodeInfo_Logic);
		//NNNodeInfos.push_back(NNNodeInfo_DB);
		NNNodeInfos.push_back(NNNodeInfo_Client);

		mNNTCPServerMgr.RunServer(NNNodeInfos);
	}));
	//启动定时管理器
	LOGI("启动网络完成");
	mMainTimerMgr.Run();
	while (true)
	{
		mMainTimerMgr.Process();
		//系统轮询处理
		Que_LoginHandler::GetInstance()->Process();
		Que_LogicHandler::GetInstance()->Process();
		Que_DBHandler::GetInstance()->Process();
#if _WIN32
		Sleep(1);
#else
		uSleep(1000);
#endif
	}
}