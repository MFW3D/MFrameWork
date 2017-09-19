#include "ThreadDBWriteBack.h"
#include <thread>
#include <mutex>
#include "SQLDBEngine.h"
#include "ServerGlobal.h"
#include "DBWriter.h"
#include "log4z.h"
#include "RedisDBEngine.h"
#include "RedisWriter.h"
//启动线程方法
void ThreadDBWriteBack::Procces()
{

}


void ThreadDBWriteBack::DBwriteBack()
{
	DBProduce::SQLDBEngine wiriteBackSQLEngine;
	wiriteBackSQLEngine.connect(ServerCfg::GetInstance()->DB_MysqlIp.c_str(),
		ServerCfg::GetInstance()->DB_MysqlPort,
		ServerCfg::GetInstance()->DB_MysqlUser.c_str(),
		ServerCfg::GetInstance()->DB_MysqlPwd.c_str(),
		ServerCfg::GetInstance()->DB_MysqlDb.c_str());
	//wiriteBackSQLEngine.connect("192.168.0.159", "root", "maomao", "cqssc");
	DBWriteBack::DBWriter dbWriter;
	dbWriter.SetSQLEngine(&wiriteBackSQLEngine);
	while (true)
	{
		
#if _WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
	}
	LOGW("主线程退出");

}
void ThreadDBWriteBack::RediswriteBack()
{
	//回写redis数据库处理
	DBProduce::RedisDBEngine redisWBEngine;
	redisWBEngine.connect(ServerCfg::GetInstance()->DB_RedisIp.c_str(), ServerCfg::GetInstance()->DB_RedisPort);
	//std::string cmd = "select 3";
	//redisWBEngine.excuteCommoned((char*)cmd.c_str());
	DBWriteBack::RedisWriter dbWriter(&redisWBEngine);
	while (true)
	{
		dbWriter.Process();
		while (true)
		{

#if _WIN32
			Sleep(10);
#else
			usleep(10000);
#endif
		}
	}
	LOGI("******" << "Redis回写线程退出完成" << "******");
	redisWBEngine.disConnect();
}