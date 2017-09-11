#pragma once
#include "HttpMgr.h"
#include "Singleton.h"
#include "Timer.h"
/*
����������ķ�����������
���ڣ���ʼ��ϵͳ���á�����ϵͳ���硢�ȴ����������ӡ�Ϊ�ͻ��˷����������
������֮����ת��
�ص㣺�����߼������������ݷ���������
*/
class ServerCenterMgr :public Singleton<ServerCenterMgr>
{
private:
	NNTCPServerMgr mNNTCPServerMgr;
	HttpMgr httpMgr;
	//�ͻ��˴����߳�
	std::shared_ptr<std::thread> mNetClientThread;

public:
	TimerMgr mMainTimerMgr;
	void Init();
	void Start();
};
