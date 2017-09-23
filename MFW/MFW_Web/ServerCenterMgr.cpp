#include "ServerCenterMgr.h"
#include "ServerGlobal.h"
#include "Timer.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"
#include "HTTPClientMgr.h"
#include "CGSHelper.h"
#include "CGSTest.h"
void ServerCenterMgr::Init()
{
	//初始化全局变量
	//ServerGlobal::GetInstance()->Init("./servercfg.ini");
}
void ServerCenterMgr::Start()
{
	//启动网络
	//mNetClientThread = std::shared_ptr<std::thread>(new std::thread([&]() {
	//	//		std::vector<HttpStartInfo> ports;
	//	//		HttpStartInfo httpStartInfo;
	//	//		
	//	//#if _WIN32
	//	//		httpStartInfo.mIp = "127.0.0.1";
	//	//#else
	//	//		httpStartInfo.mIp = "0.0.0.0";
	//	//#endif
	//	//		httpStartInfo.mIsClient = false;
	//	//		httpStartInfo.mPort = ServerCfg::GetInstance()->Web_Port;
	//	//		ports.push_back(httpStartInfo);
	//	//
	//	//		httpMgr.OnConnectedPtr = std::bind(&Net_ClientHandler::OnConnected, 
	//	//			Net_ClientHandler::GetInstance().get(),std::placeholders::_1,  std::placeholders::_2);
	//	//		httpMgr.OnDisConnectedPtr = std::bind(&Net_ClientHandler::OnDisConnected,
	//	//			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2);
	//	//		httpMgr.OnReadServerPtr = std::bind(&Net_ClientHandler::OnRead,
	//	//			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	//	//		httpMgr.Start(ports);
	//	HTTPClientMgr::GetInstance()->start();
	//}));
	//for (int i = 0; i < 1; i++)
	//{
	//	HTTPRequestInfo info;
	//	info.ip = "www.baidu.com";
	//	//info.ip = "mfw3d.com";
	//	//info.ip = "67.218.141.114";
	//	info.port = 80;
	//	info.url = "/login/check.html";
	//	//info.url = "/index.html";
	//	info.mEHttpMethod = EHttpMethod::GET;
	//	info.flag = i;
	//	info.body = "";
	//	info.params.insert(std::pair<std::string, std::string>("Upgrade - Insecure - Requests", "1"));
	//	info.params.insert(std::pair<std::string, std::string>("User - Agent", "Mozilla / 5.0 (Windows NT 6.1; WOW64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 60.0.3112.90 Safari / 537.36"));
	//	info.params.insert(std::pair<std::string, std::string>("Accept", "text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, image / apng, */*;q=0.8"));
	//	info.params.insert(std::pair<std::string, std::string>("Accept-Encoding", "gzip, deflate"));
	//	info.params.insert(std::pair<std::string, std::string>("Accept-Language", "zh-CN,zh;q=0.8"));
	//	HTTPClientMgr::GetInstance()->pushHTTPRequest(info);
	//}
	//启动定时管理器
	mMainTimerMgr.Run();
	CGSHelper::GetInstance()->Start("127.0.0.1", 8080, "/8844?calldata=");
	//CGSHelper::GetInstance()->Start("sync.1sdk.cn", 80, "/login/check.html");

	//创建房间开始比赛
	CGSTest cGSTest;
	cGSTest.Start();
	
	//注册方法
	int i = 0;
	while (true)
	{
		CGSHelper::GetInstance()->Process();
		mMainTimerMgr.Process();
		cGSTest.Process();
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
		uSleep(1000);
#endif
	}
}