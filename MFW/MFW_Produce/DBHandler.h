#pragma once
#include <memory>
#include "DBTypes.h"
namespace DBProduce
{
	class DBHandler
	{
		public:
			DBHandler();
			virtual ~DBHandler();
			virtual void readDBAccount(std::shared_ptr <DBProduce::DBAccount> _DBAccount)=0;
			virtual void readDBUserInfo(std::shared_ptr <DBProduce::DBUserInfo> _DBUserInfo)=0;
	};

}
