#include <iostream>
#include <string>
#include "log4z.h"
#include "ServerCenterMgr.h"
using namespace zsummer::log4z;

int main()
{
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./Log_Manager");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);

	LOGI("启动服务器... ...");
	ServerCenterMgr::GetInstance()->Init();
	LOGI("初始化配置完成... ...");
	ServerCenterMgr::GetInstance()->Start();
	return 0;
}