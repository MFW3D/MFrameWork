#pragma once
#include <memory>
#include <functional>
#include "RedisDBEngine.h"
/*
ʹ��redis����ʵ����Ϣ���м仺��ͳ־û�
*/
class RedisQueue
{
private:
	//redis����
	DBProduce::RedisDBEngine* mRedisDBEngine;
	std::string mQueueName = "";
public:
	RedisQueue(DBProduce::RedisDBEngine* redisDBEngine,
		std::string queName);
	void PushData(std::string& data);
	bool PopData(std::string& data);
};


