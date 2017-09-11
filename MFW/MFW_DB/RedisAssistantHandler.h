#pragma once
#include "DBIds.h"
#include "DBTypes.h"
#include "ServerCenterMgr.h"
#include "RedisDBEngine.h"

namespace DBProduce
{
	class RedisAssistantHandler: public DBHandler
	{
		private:
			DBProduce::RedisDBEngine* redisDBEngine;
		public:
			RedisAssistantHandler(DBProduce::RedisDBEngine* _redisDBEngine);
			virtual void readDBAccount(std::shared_ptr <DBProduce::DBAccount> _DBAccount) ;
			virtual void readDBUserInfo(std::shared_ptr <DBProduce::DBUserInfo> _DBUserInfo);

	};

}
