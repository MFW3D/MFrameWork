#include "RedisQueue.h"
#include "String2Hex.h"

RedisQueue::RedisQueue(DBProduce::RedisDBEngine*redisDBEngine,	std::string queName)
{
	mQueueName = queName;
	mRedisDBEngine = redisDBEngine;
}
void RedisQueue::PushData(std::string& data)
{
	//推入
	std::string cmd = "RPUSH " + mQueueName+" ";

	cmd.append(String2Hex::BinToHex(data));
	mRedisDBEngine->excuteCommoned(cmd);
}
bool RedisQueue::PopData(std::string& data)
{
	//取出
	std::string cmd = "LPOP " + mQueueName ;
	bool result=mRedisDBEngine->excuteCommoned(cmd, data);
	data= String2Hex::HexToBin(data);
	return result;
}