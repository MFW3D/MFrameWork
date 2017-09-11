#include "RedisAssistantHandler.h"

namespace DBProduce
{
	RedisAssistantHandler::RedisAssistantHandler(
		DBProduce::RedisDBEngine* _redisDBEngine)
	{
		redisDBEngine = _redisDBEngine;
	}
	void RedisAssistantHandler::readDBAccount(std::shared_ptr <DBProduce::DBAccount> _DBAccount)
	{
		//缓存账户-uid的数据
		std::string cmd = "set  DBAccount_accid:" +_DBAccount->acc;
		cmd.append(" " + std::to_string(_DBAccount->uid));
		redisDBEngine->excuteCommoned(cmd);
	}
	void RedisAssistantHandler::readDBUserInfo(std::shared_ptr <DBProduce::DBUserInfo> _DBUserInfo)
	{

	}
}
