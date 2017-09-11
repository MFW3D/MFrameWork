#pragma once
#include "DBHandler.h"
#include "DBDatas.h"
#include "NetUtility.h"
#include "DBTypes.h"

namespace DBProduce
{
	class MemHandler : public DBHandler
	{
		public:
			MemHandler();
			virtual ~MemHandler();

			//清空redis中所有的数据，慎用
			void readDBAccount(std::shared_ptr <DBProduce::DBAccount> _DBAccount);
			void readDBUserInfo(std::shared_ptr <DBProduce::DBUserInfo> _DBUserInfo);
	};

}
