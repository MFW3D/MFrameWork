#pragma once
#include "DBTypes.h"
#include "RedisDBEngine.h"
#include "DBCommon.h"
#include "NetUtility.h"
namespace DBProduce
{
	class RedisReader
	{
		private:
			static DBProduce::RedisDBEngine* redisEngine;
		public:
			static void setRedisEngine(DBProduce::RedisDBEngine* _redisEngine);
			static bool GetDBAccount(std::shared_ptr<DBAccount> p, std::string  uid);
			static bool GetDBUserInfo(std::shared_ptr<DBUserInfo> p, std::string  uid);
	};

}
