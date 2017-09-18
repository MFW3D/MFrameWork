#include "ServerCenterMgr.h"
#include "ServerGlobal.h"
#include "Timer.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"
#include "HTTPClientMgr.h"
void ServerCenterMgr::Init()
{
	//初始化全局变量
	ServerGlobal::GetInstance()->Init("E:\\MFW\\trunk\\Server\\MFW\\x64\\Debug\\servercfg.ini");
}
void ServerCenterMgr::Start()
{
	//启动网络
	mNetClientThread = std::shared_ptr<std::thread>(new std::thread([&]() {
		//		std::vector<HttpStartInfo> ports;
		//		HttpStartInfo httpStartInfo;
		//		
		//#if _WIN32
		//		httpStartInfo.mIp = "127.0.0.1";
		//#else
		//		httpStartInfo.mIp = "0.0.0.0";
		//#endif
		//		httpStartInfo.mIsClient = false;
		//		httpStartInfo.mPort = ServerCfg::GetInstance()->Web_Port;
		//		ports.push_back(httpStartInfo);
		//
		//		httpMgr.OnConnectedPtr = std::bind(&Net_ClientHandler::OnConnected, 
		//			Net_ClientHandler::GetInstance().get(),std::placeholders::_1,  std::placeholders::_2);
		//		httpMgr.OnDisConnectedPtr = std::bind(&Net_ClientHandler::OnDisConnected,
		//			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2);
		//		httpMgr.OnReadServerPtr = std::bind(&Net_ClientHandler::OnRead,
		//			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		//		httpMgr.Start(ports);

		HTTPClientMgr::GetInstance()->start();
	}));
	for (int i = 0; i < 10000; i++)
	{
		HTTPRequestInfo info;
		info.ip = "67.218.141.114";
		info.port = 8080;
		info.url = "/index.html";
		info.mEHttpMethod = EHttpMethod::GET;
		info.flag = i;
		info.body = "";
		info.params.insert(std::pair<std::string, std::string>("Upgrade - Insecure - Requests", "1"));
		info.params.insert(std::pair<std::string, std::string>("User - Agent", "Mozilla / 5.0 (Windows NT 6.1; WOW64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 60.0.3112.90 Safari / 537.36"));
		info.params.insert(std::pair<std::string, std::string>("Accept", "text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, image / apng, */*;q=0.8"));
		info.params.insert(std::pair<std::string, std::string>("Accept-Encoding", "gzip, deflate"));
		info.params.insert(std::pair<std::string, std::string>("Accept-Language", "zh-CN,zh;q=0.8"));
		HTTPClientMgr::GetInstance()->pushHTTPRequest(info);
	}
	//启动定时管理器
	mMainTimerMgr.Run();
	int i = 0;
	while (true)
	{
		mMainTimerMgr.Process();
		//处理http响应回复
		HTTPResposeInfo info;
		while (HTTPClientMgr::GetInstance()->popHTTPRespose(info))
		{
			//std::cout << info.Data << std::endl;
			++i;
			std::cout << i << std::endl;
			/*if (i == 10000)
			{
				return;
			}*/
		}
		//系统轮询处理
#if _WIN32
		Sleep(1);
#else
		uSleep(1000);
#endif
	}
}