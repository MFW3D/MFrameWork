#include "ServerCenterMgr.h"
#include "ServerGlobal.h"
#include "Timer.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"
#include "Net_ClientHandler.h"
#include "Net_ManagerHandler.h"
#include "Net_DBHandler.h"
void ServerCenterMgr::Init()
{
	//初始化全局变量
	ServerGlobal::GetInstance()->Init("E:\\MFW\\trunk\\Server\\MFW\\x64\\Debug\\servercfg.ini");
	redisHandlerEngine.connect(ServerCfg::GetInstance()->DB_RedisIp.c_str(),
		ServerCfg::GetInstance()->DB_RedisPort);

	mRedisQueueFDB = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_db_logic));
	mRedisQueueTDB = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_logic_db));
	mRedisQueueFManager = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_manager_logic));
	mRedisQueueTManager = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_logic_manager));
	Que_DBHandler::GetInstance()->Init(mRedisQueueTDB,mRedisQueueFDB);
	Que_ManagerHandler::GetInstance()->Init(mRedisQueueTManager,mRedisQueueFManager);
}
void ServerCenterMgr::Start()
{
	//对client的tcp连接
	mNetMDBThread = std::shared_ptr<std::thread>(new std::thread([&]() {
		std::vector<NNNodeInfo> NNNodeInfos;
		//NNNodeInfo NNNodeInfo_Manager;
		//NNNodeInfo NNNodeInfo_DB;
		NNNodeInfo NNNodeInfo_Client;
		//NNNodeInfo_Manager.Ip = ServerCfg::GetInstance()->Manager_IP;
		//NNNodeInfo_DB.Ip = ServerCfg::GetInstance()->DB_IP;
#if _WIN32
		NNNodeInfo_Client.Ip = "127.0.0.1";
#else
		NNNodeInfo_Client.Ip = "0.0.0.0";
#endif
		//NNNodeInfo_Manager.Port = ServerCfg::GetInstance()->Manager_Port2Logic;
		//NNNodeInfo_DB.Port = ServerCfg::GetInstance()->DB_Port2Logic;
		NNNodeInfo_Client.Port = ServerCfg::GetInstance()->Logic_Port2Client;

		//NNNodeInfo_Manager.isClient = true;
		//NNNodeInfo_DB.isClient = true;
		NNNodeInfo_Client.isClient = false;

		//NNNodeInfo_Manager.OnConnected = std::bind(&Net_ManagerHandler::OnConnected, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		//NNNodeInfo_DB.OnConnected = std::bind(&Net_DBHandler::OnConnected, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Client.OnConnected = std::bind(&Net_ClientHandler::OnConnected, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);

		//NNNodeInfo_Manager.OnDisConnected = std::bind(&Net_ManagerHandler::OnDisConnected, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		//NNNodeInfo_DB.OnDisConnected = std::bind(&Net_DBHandler::OnDisConnected, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Client.OnDisConnected = std::bind(&Net_ClientHandler::OnDisConnected, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);

		//NNNodeInfo_Manager.OnRead = std::bind(&Net_ManagerHandler::OnRead, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		//NNNodeInfo_DB.OnRead = std::bind(&Net_DBHandler::OnRead, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		NNNodeInfo_Client.OnRead = std::bind(&Net_ClientHandler::OnRead, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

		//NNNodeInfo_Manager.OnTimered = std::bind(&Net_ManagerHandler::OnTimered, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1);
		//NNNodeInfo_DB.OnTimered = std::bind(&Net_DBHandler::OnTimered, Net_DBHandler::GetInstance().get(),
		//	std::placeholders::_1);
		NNNodeInfo_Client.OnTimered = std::bind(&Net_ClientHandler::OnTimered, Net_ClientHandler::GetInstance().get(),
			std::placeholders::_1);

		//NNNodeInfos.push_back(NNNodeInfo_Manager);
		//NNNodeInfos.push_back(NNNodeInfo_DB);
		NNNodeInfos.push_back(NNNodeInfo_Client);

		mNNTCPServerMgr.RunServer(NNNodeInfos);
	}));


	//启动定时管理器
	mMainTimerMgr.Run();
	while (true)
	{
		mMainTimerMgr.Process();
		//系统轮询处理
		Que_ManagerHandler::GetInstance()->Process();
		Que_DBHandler::GetInstance()->Process();
#if _WIN32
		Sleep(1);
#else
		uSleep(1000);
#endif
	}
}