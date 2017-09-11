#include "RedisHandler.h"

namespace DBProduce
{
	RedisHandler::RedisHandler(DBProduce::RedisDBEngine* _redisDBEngine)
	{
		redisDBEngine = _redisDBEngine;
	}
	RedisHandler::~RedisHandler()
	{
		
	}
	void RedisHandler::flashAll()
	{
		std::string cmd = "flushall";
		redisDBEngine->excuteCommoned(cmd);
	}
	void RedisHandler::readDBAccount(std::shared_ptr <DBProduce::DBAccount> _DBAccount)
	{
        std::string cmd = "hmset  DBAccount:" + std::to_string((long long)_DBAccount->uid); 
        cmd.append( " acc  " + NetUtility::BinToHex(_DBAccount->acc)+" ");
        cmd.append( " pwd  " + NetUtility::BinToHex(_DBAccount->pwd)+" ");
        cmd.append( " tel  " + NetUtility::BinToHex(_DBAccount->tel)+" ");
        cmd.append( " wx  " + NetUtility::BinToHex(_DBAccount->wx)+" ");
        cmd.append( " qq  " + NetUtility::BinToHex(_DBAccount->qq)+" ");
        cmd.append( " lastlogin  " + std::to_string(_DBAccount->lastlogin)+" ");
        cmd.append( " createtime  " + std::to_string(_DBAccount->createtime)+" ");;
		redisDBEngine->excuteCommoned(cmd);
	}
	void RedisHandler::readDBUserInfo(std::shared_ptr <DBProduce::DBUserInfo> _DBUserInfo)
	{
        std::string cmd = "hmset  DBUserInfo:" + std::to_string((long long)_DBUserInfo->uid); 
        cmd.append( " nickname  " + NetUtility::BinToHex(_DBUserInfo->nickname)+" ");;
		redisDBEngine->excuteCommoned(cmd);
	}
}
