#include "HttpMgr.h"
#include "Timer.h"
#include <string>

#include "ServerCenterMgr.h"
#if _WIN32
#include <windows.h>
#else
#include "unistd.h"
#endif
TimerMgr timerMgr;
#include "log4z.h"
using namespace zsummer::log4z;


int timerindex = 0;
void OnTimerCB(Timer timer)
{
	//std::cout << timer.mTick << std::endl; 
	long long sys_now = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	long long*  plauerid = (long long*)timer.data;
	LOGI("timr" << timerindex++ << ":" << sys_now- timer.mStartTime);//Info
}
int main()
{
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./Log_Login");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	ServerCenterMgr::GetInstance()->Init();
	ServerCenterMgr::GetInstance()->Start();
	return 0;
}
