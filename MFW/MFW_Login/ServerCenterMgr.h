#pragma once
#include "HttpMgr.h"
#include "Singleton.h"
#include "Timer.h"
#include "RedisQueue.h"
#include "Que_DBHandler.h"
#include "Que_ManagerHandler.h"
/*
����������ķ�����������
���ڣ���ʼ��ϵͳ���á�����ϵͳ���硢�ȴ����������ӡ�Ϊ�ͻ��˷����������
������֮����ת��
�ص㣺�����߼������������ݷ���������
*/
class ServerCenterMgr :public MFW::Singleton<ServerCenterMgr>
{
private:
	NNTCPServerMgr mNNTCPServerMgr;
	HttpMgr httpMgr;
	//�ͻ��˴����߳�
	//std::shared_ptr<std::thread> mNetClientThread;
	//���ӹ�������������ݷ������Ĵ����߳�
	std::shared_ptr<std::thread> mNetMDBThread;
public:
	DBProduce::RedisDBEngine redisHandlerEngine;
	//�����ݷ������͹��������ͨѶ����
	std::shared_ptr<RedisQueue> mRedisQueueFDB;
	std::shared_ptr<RedisQueue> mRedisQueueTDB;
	std::shared_ptr<RedisQueue> mRedisQueueFManager;
	std::shared_ptr<RedisQueue> mRedisQueueTManager;

	TimerMgr mMainTimerMgr;
	void Init();
	void Start();
};
