#include "ServerCenterMgr.h"
#include "ServerGlobal.h"
#include "Timer.h"
#include "Net_ClientHandler.h"
#include "ServerGlobal.h"
#include "HTTPClientMgr.h"
void ServerCenterMgr::Init()
{
	//��ʼ��ȫ�ֱ���
	ServerGlobal::GetInstance()->Init("./servercfg.ini");
}
void ServerCenterMgr::Start()
{
	//��������
	mNetClientThread = std::shared_ptr<std::thread>(new std::thread([&]() {
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
			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2);
		httpMgr.OnDisConnectedPtr = std::bind(&Net_ClientHandler::OnDisConnected,
			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2);
		httpMgr.OnReadServerPtr = std::bind(&Net_ClientHandler::OnRead,
			Net_ClientHandler::GetInstance().get(), std::placeholders::_1, std::placeholders::_2, 
			std::placeholders::_3);
		httpMgr.OnTimerPtr = std::bind(&Net_ClientHandler::OnTime,Net_ClientHandler::GetInstance().get());
		httpMgr.Start(ports);
	}));

	//������ʱ������
	//mMainTimerMgr.Run();
	//ע�᷽��
	int i = 0;
	while (true)
	{
		//mMainTimerMgr.Process();
		//����http��Ӧ�ظ�
#if _WIN32
		Sleep(1);
#else
		uSleep(1000);
#endif
	}
}