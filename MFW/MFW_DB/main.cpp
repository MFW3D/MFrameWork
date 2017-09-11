#include "log4z.h"
#include "ServerCenterMgr.h"
using namespace std;
using namespace zsummer::log4z;
int main()
{
	//start log4z
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log2");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);

	//测试日志系统输出
	LOGT("stream input *** " << "LOGT LOGT LOGT LOGT" << " *** ");//trace
	LOGD("stream input *** " << "LOGD LOGD LOGD LOGD" << " *** ");//debug
	LOGI("stream input *** " << "LOGI LOGI LOGI LOGI" << " *** ");//Info
	LOGW("stream input *** " << "LOGW LOGW LOGW LOGW" << " *** ");//Warn
	LOGE("stream input *** " << "LOGE LOGE LOGE LOGE" << " *** ");//Error
	LOGA("stream input *** " << "LOGA LOGA LOGA LOGA" << " *** ");//Alarm
	LOGF("stream input *** " << "LOGF LOGF LOGF LOGF" << " *** ");//Fatal

	LOGI("******" << "初始化服务器" << "******");
	ServerCenterMgr::GetInstance()->InitServer();
	ServerCenterMgr::GetInstance()->StartServer();

	system("pause");
	return 0;
}
