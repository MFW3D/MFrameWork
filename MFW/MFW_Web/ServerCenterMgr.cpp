#include "ServerCenterMgr.h"
#include "ServerGlobal.h"
#include "Timer.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"
void ServerCenterMgr::Init()
{
	//��ʼ��ȫ�ֱ���
	ServerGlobal::GetInstance()->Init("E:\\MFW\\trunk\\Server\\MFW\\x64\\Debug\\servercfg.ini");
}
void ServerCenterMgr::Start()
{
	//��������
	mNetClientThread=std::shared_ptr<std::thread>(new std::thread ([&]() {
		std::vector<HttpStartInfo> ports;
		HttpStartInfo httpStartInfo;
		
#if _WIN32
		httpStartInfo.mIp = "127.0.0.1";
#else
		httpStartInfo.mIp = "0.0.0.0";
#endif
		httpStartInfo.mIsClient = false;
		httpStartInfo.mPort = ServerCfg::GetInstance()->Web_Port;
		ports.push_back(httpStartInfo);

		httpMgr.OnConnectedPtr = std::bind(&Net_ClientHandler::OnConnected, 
			Net_ClientHandler::GetInstance().get(),std::placeholders::_1,  std::placeholders::_2);
		httpMgr.OnDisConnectedPtr = std::bind(&Net_ClientHandler::OnDisConnected,
			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2);
		httpMgr.OnReadServerPtr = std::bind(&Net_ClientHandler::OnRead,
			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		httpMgr.Start(ports);
	}));

	//������ʱ������
	mMainTimerMgr.Run();
	while (true)
	{
		mMainTimerMgr.Process();
		//ϵͳ��ѯ����
#if _WIN32
		Sleep(1);
#else
		uSleep(1000);
#endif
	}
}