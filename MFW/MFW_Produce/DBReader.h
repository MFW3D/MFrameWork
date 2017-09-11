#pragma once
#include <mysql.h>
#include <vector>
#include "DBHandler.h"
#include "DBTypes.h"
#include "DBIds.h"
#include <memory>

namespace DBProduce
{
	class DBReader
	{
		private:
			static MYSQL conn;
			static MYSQL_RES *res_ptr;
			static MYSQL_ROW sqlrow;
			static std::vector<DBHandler*> dbHandlers;
		public:
			static void connect(const char* host,int port, const char* user,
			        const char* password, const char* database);
			static void Disconnect();
			static void DBtoHandler();
			static void SetDBHandler(DBHandler* _Handler);
			static void DBAccounttoHandler();
			static void DBUserInfotoHandler();
	};

}
