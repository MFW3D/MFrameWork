#include "ServerCenterMgr.h"
//#include "ServerGlobal.h"
#include "Timer.h"
//#include "Net_ClientHandler.h"
//#include "ServerGlobal.h"
#include "HTTPClientMgr.h"
#include "CGSHelper.h"
#include "CGSTest.h"
#ifndef _WIN32
#include <unistd.h>
#endif
void ServerCenterMgr::Init()
{
}
void ServerCenterMgr::Start()
{
	
	mMainTimerMgr.Run();
	CGSHelper::GetInstance()->Start("192.168.3.30", 8080, "/8844?calldata=");

	std::vector<CGSTest> CGSTests;
	const int count = 100;
	//创建房间开始比赛

	CGSTest cGSTests[count];
	for (int i = 0; i < count; i++)
	{
		cGSTests[i].Start();
	}
	//注册方法
	int i = 0;
	while (true)
	{
		CGSHelper::GetInstance()->Process();
		mMainTimerMgr.Process();
		for (int i = 0; i < count; i++)
		{
			cGSTests[i].Process();
		}
		//处理http响应回复
		//HTTPResposeInfo info;
		//while (HTTPClientMgr::GetInstance()->popHTTPRespose(info))
		//{
		//	std::cout << info.Data << std::endl;
		//	++i;
		//	std::cout << i << std::endl;
		//	/*if (i == 10000)
		//	{
		//		return;
		//	}*/
		//}
		//系统轮询处理
#if _WIN32
		Sleep(1);
#else
		usleep(1000);
#endif
	}
}