#pragma once
#include "NNTCPServerMgr.h"
#include "Singleton.h"
#include "Timer.h"
#include "RedisQueue.h"
#include "Que_DBHandler.h"
#include "Que_LogicHandler.h"
#include "Que_LoginHandler.h"
/*
����������ķ�����������
���ڣ���ʼ��ϵͳ���á�����ϵͳ���硢�ȴ����������ӡ�Ϊ�ͻ��˷����������
	������֮����ת��
�ص㣺�����߼������������ݷ���������
*/
class ServerCenterMgr:public MFW::Singleton<ServerCenterMgr>
{
private:
	NNTCPServerMgr mNNTCPServerMgr;
	std::shared_ptr<std::thread> mNetThread;
public:
	DBProduce::RedisDBEngine redisHandlerEngine;
	//������������ͨѶ����
	std::shared_ptr<RedisQueue> mRedisQueueFDB;
	std::shared_ptr<RedisQueue> mRedisQueueTDB;
	std::shared_ptr<RedisQueue> mRedisQueueFLogin;
	std::shared_ptr<RedisQueue> mRedisQueueTLogin;
	std::shared_ptr<RedisQueue> mRedisQueueFLogic;
	std::shared_ptr<RedisQueue> mRedisQueueTLogic;

	TimerMgr mMainTimerMgr;

	void Init();
	void Start();
};
