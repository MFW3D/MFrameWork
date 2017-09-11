#pragma once
#include "DBHandler.h"
#include "RedisDBEngine.h"
#include "NetUtility.h"
#include "DBTypes.h"

namespace DBProduce
{
	class RedisHandler: public DBHandler
	{
		private:
			DBProduce::RedisDBEngine* redisDBEngine;
		public:
			RedisHandler(DBProduce::RedisDBEngine* _redisDBEngine);
			virtual ~RedisHandler();

			//清空redis中所有的数据，慎用
			void flashAll();
			void readDBAccount(std::shared_ptr <DBProduce::DBAccount> _DBAccount);
			void readDBUserInfo(std::shared_ptr <DBProduce::DBUserInfo> _DBUserInfo);
	};

}
