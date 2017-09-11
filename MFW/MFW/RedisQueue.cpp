#include "RedisQueue.h"
#include "String2Hex.h"

RedisQueue::RedisQueue(DBProduce::RedisDBEngine*redisDBEngine,	std::string queName)
{
	mQueueName = queName;
	mRedisDBEngine = redisDBEngine;
}
void RedisQueue::PushData(std::string& data)
{
	//����
	std::string cmd = "LPUSH " + mQueueName+" ";

	cmd.append(String2Hex::BinToHex(data));
	mRedisDBEngine->excuteCommoned(cmd);
}
bool RedisQueue::PopData(std::string& data)
{
	//ȡ��
	std::string cmd = "LPOP " + mQueueName ;
	bool result=mRedisDBEngine->excuteCommoned(cmd, data);
	data= String2Hex::HexToBin(data);
	return result;
}