#pragma once
#include "DBMsg.h"
#include "RedisWriter.h"
#include "DBWriter.h"
namespace DBProduce
{
	
	class WriteBackMgr
	{
		private:
			WriteBackMgr();
			virtual ~WriteBackMgr();
		public:
			static void WriteBack(DBProduce::DBMsg& dbMsg);
	};

}
