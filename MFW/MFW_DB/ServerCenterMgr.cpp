#include "ServerCenterMgr.h"
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include "ServerGlobal.h"
#include "Net_Handler.h"
#include "Net_LogicHandler.h"
#include "Net_LoginHandler.h"
#include "Net_ManagerHandler.h"
using namespace zsummer::log4z;

//初始化服务器
void ServerCenterMgr::InitServer()
{
	//初始化
	//ServerGlobal::init("./servercfg.ini");
	ServerGlobal::GetInstance()->Init("./servercfg.ini");


	LOGD("全局初始化完成");

	//redis数据库处理handler
	redisHandlerEngine.connect(ServerCfg::GetInstance()->DB_RedisIp.c_str(),
		ServerCfg::GetInstance()->DB_RedisPort);
	//std::string cmd = "select 3";
	//redisHandlerEngine.excuteCommoned((char*)cmd.c_str());
	//数据库数据入库标准redis结构
	DBProduce::RedisHandler redisHandler(&redisHandlerEngine); //实例化redis处理handler
	//redisHandler.flashAll(); //清空redis数据库
	//配置与其他服务器通讯的消息队列
	mRedisQueueFLogin = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_login_db));
	mRedisQueueTLogin = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_db_login));
	mRedisQueueFLogic = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_logic_db));
	mRedisQueueTLogic = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_db_logic));
	mRedisQueueFManager = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_manager_db));
	mRedisQueueTManager = std::shared_ptr<RedisQueue>(new RedisQueue(
		&redisHandlerEngine, ServerCfg::GetInstance()->Queue_db_manager));
	 Que_LoginHandler::GetInstance()->Init(mRedisQueueTLogin,mRedisQueueFLogin);
	 Que_LogicHandler::GetInstance()->Init(mRedisQueueTLogic,mRedisQueueFLogic);
	 Que_ManagerHandler::GetInstance()->Init(mRedisQueueTManager,mRedisQueueFManager);

	LOGD("数据库配置初始化完成");

	DBProduce::DBReader::connect(ServerCfg::GetInstance()->DB_MysqlIp.c_str(),
		ServerCfg::GetInstance()->DB_MysqlPort,
		ServerCfg::GetInstance()->DB_MysqlUser.c_str(),
		ServerCfg::GetInstance()->DB_MysqlPwd.c_str(),
		ServerCfg::GetInstance()->DB_MysqlDb.c_str()); //连接数据库
	DBProduce::DBReader::SetDBHandler(&redisHandler); //设置数据库的处理handler为redishandler

	DBProduce::RedisAssistantHandler redisAssistanceHandler(&redisHandlerEngine);
	DBProduce::DBReader::SetDBHandler(&redisAssistanceHandler); //设置数据库的处理handler为redishandler
																//为辅助构造设置redis引擎
	AssistantMG::GetInstance()->SetRedisEngine(&redisHandlerEngine);
	LOGD("Redis数据库配置初始化完成");


	//为redisreader设置引擎
	DBProduce::RedisReader::setRedisEngine(&redisHandlerEngine);

	DBProduce::DBReader::DBtoHandler(); //处理数据库读出数据
	DBProduce::DBReader::Disconnect(); //断开数据库
	LOGD("数据读取完成");

	dBSQLEngine.connect(ServerCfg::GetInstance()->DB_MysqlIp.c_str(),
		ServerCfg::GetInstance()->DB_MysqlPort,
		ServerCfg::GetInstance()->DB_MysqlUser.c_str(),
		ServerCfg::GetInstance()->DB_MysqlPwd.c_str(), 
		ServerCfg::GetInstance()->DB_MysqlDb.c_str());
	
	LOGD("服务器配置初始化完成");
}


//启动服务器
bool ServerCenterMgr::StartServer()
{
	//启动数据回写线程
	std::thread threadDBWB(std::bind(&ThreadDBWriteBack::DBwriteBack, &threadDBWriteBack));
	std::thread threadRedisWB(std::bind(&ThreadDBWriteBack::RediswriteBack, &threadDBWriteBack));
	
	//启动网络服务器
	//启动网络
	mNetThread = std::shared_ptr<std::thread>(new std::thread([&]() {
		std::vector<NNNodeInfo> NNNodeInfos;
		//NNNodeInfo NNNodeInfo_Login;
		NNNodeInfo NNNodeInfo_Logic;
		//NNNodeInfo NNNodeInfo_Manager;
#if _WIN32
		//NNNodeInfo_Login.Ip = "127.0.0.1";
		NNNodeInfo_Logic.Ip = "127.0.0.1";
		//NNNodeInfo_Manager.Ip = "127.0.0.1";
#else
		//NNNodeInfo_Login.Ip = "0.0.0.0";
		NNNodeInfo_Logic.Ip = "0.0.0.0";
		//NNNodeInfo_Manager.Ip = "0.0.0.0";

#endif
		//NNNodeInfo_Login.Port = ServerCfg::GetInstance()->DB_Port2Login;
		NNNodeInfo_Logic.Port = ServerCfg::GetInstance()->DB_Port2Logic;
		//NNNodeInfo_Manager.Port = ServerCfg::GetInstance()->DB_Port2Manager;

		//NNNodeInfo_Login.IsClient = false;
		NNNodeInfo_Logic.IsClient = false;
		//NNNodeInfo_Manager.IsClient = false;

		//NNNodeInfo_Login.OnConnected = std::bind(&Net_LoginHandler::OnConnected, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Logic.OnConnected = std::bind(&Net_LogicHandler::OnConnected, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);
		//NNNodeInfo_Manager.OnConnected = std::bind(&Net_ManagerHandler::OnConnected, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
	

		//NNNodeInfo_Login.OnDisConnected = std::bind(&Net_LoginHandler::OnDisConnected, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
		NNNodeInfo_Logic.OnDisConnected = std::bind(&Net_LogicHandler::OnDisConnected, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2);
		//NNNodeInfo_Manager.OnDisConnected = std::bind(&Net_ManagerHandler::OnDisConnected, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2);
	

		//NNNodeInfo_Login.OnRead = std::bind(&Net_LoginHandler::OnRead, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		NNNodeInfo_Logic.OnRead = std::bind(&Net_LogicHandler::OnRead, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		//NNNodeInfo_Manager.OnRead = std::bind(&Net_ManagerHandler::OnRead, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);



		//NNNodeInfo_Login.OnTimered = std::bind(&Net_LoginHandler::OnTimered, Net_LoginHandler::GetInstance().get(),
		//	std::placeholders::_1);
		NNNodeInfo_Logic.OnTimered = std::bind(&Net_LogicHandler::OnTimered, Net_LogicHandler::GetInstance().get(),
			std::placeholders::_1);
		//NNNodeInfo_Manager.OnTimered = std::bind(&Net_ManagerHandler::OnTimered, Net_ManagerHandler::GetInstance().get(),
		//	std::placeholders::_1);
	

		//NNNodeInfos.push_back(NNNodeInfo_Login);
		NNNodeInfos.push_back(NNNodeInfo_Logic);
		//NNNodeInfos.push_back(NNNodeInfo_Manager);

		mNNTCPServerMgr.RunServer(NNNodeInfos);
	}));



	LOGD("外部线程启动完成");
	while (true)
	{
		//主线程更新
		try
		{
			//取队列
			Que_LoginHandler::GetInstance()->Process();
			Que_LogicHandler::GetInstance()->Process();
			Que_ManagerHandler::GetInstance()->Process();
		}
		catch (std::exception& e)
		{
			LOGE("网络数据处理发生错误");
		}
#if _WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
		}
	LOGW("主线程退出");

	return true;
	}

//关闭服务器
bool ServerCenterMgr::CloseServer()
{
	return true;
}

//启动异步业务
bool ServerCenterMgr::StartTask()
{

	return true;
}

//初始化计划信息
void ServerCenterMgr::InitPlans()
{


}