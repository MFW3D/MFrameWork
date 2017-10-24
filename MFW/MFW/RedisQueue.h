#pragma once
#include <memory>
#include <functional>
#include "RedisDBEngine.h"
/*
使用redis队列实现消息的中间缓存和持久化
*/
class RedisQueue
{
private:
	//redis引擎
	DBProduce::RedisDBEngine* mRedisDBEngine;
	std::string mQueueName = "";
public:
	RedisQueue(DBProduce::RedisDBEngine* redisDBEngine,
		std::string queName);
	void PushData(std::string& data);
	bool PopData(std::string& data);
};


