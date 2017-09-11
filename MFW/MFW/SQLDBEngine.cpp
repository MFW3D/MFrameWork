#include "SQLDBEngine.h"
#include "log4z.h"

namespace DBProduce
{
	//MYSQL SQLDBEngine::conn;
	//std::shared_ptr<MYSQL_RES>* SQLDBEngine::res_ptr;
	//MYSQL_ROW SQLDBEngine::sqlrow;
	
	SQLDBEngine::SQLDBEngine()
	{
		res_ptr = nullptr;
		sqlrow = NULL;
	}
	
	SQLDBEngine::~SQLDBEngine()
	{
	}
	
	void SQLDBEngine::HandData(DBProduce::DBMsg& dbmsg)
	{
		switch (dbmsg.dbCMD)
		{
			case DBCMD::dbinsert:
				insertData(dbmsg.tablename, dbmsg.keyName, dbmsg.keyValue,  dbmsg.data);
				break;
			case DBCMD::dbupdate:
				updateData(dbmsg.tablename, dbmsg.keyName, dbmsg.keyValue, dbmsg.
data);
				break;
			case DBCMD::dbdelete:
				deleteData(dbmsg.tablename,dbmsg.keyName, dbmsg.keyValue );
				break;
			case DBCMD::dbnone:
				break;
		}
	}
	
	void SQLDBEngine::connect(const char* host,int port, const char* user,
	        const char* password, const char* database)
	{
		sqlHost= host;
		sqlport = port;
		sqlUser= user;
		sqlPassword= password;
		sqlDatabase= database;
		mysql_init (&conn); // 注意取地址符&
		
		if (mysql_real_connect(&conn, host, user, password, database, port, NULL,
		        0))
		{
			mysql_query(&conn, "SET NAMES \'UTF8\'");
			//mysql_query(&conn, "SET NAMES GB2312");
			LOGI("mysql"<< host <<" 连接成功!");
		}
		else
		{
			LOGI("mysql" << host << "连接失败!");
			if (mysql_errno(&conn))
			{
				LOGI("数据库 "<< mysql_errno(&conn) <<": "<< mysql_error(&conn)<< "连接失败!");
			}

			exit (EXIT_FAILURE);
		}
	}
	void SQLDBEngine::ReConnect()
	{
		disConnect();
		connect(sqlHost.c_str(), sqlport, sqlUser.c_str(), sqlPassword.c_str(), sqlDatabase.c_str());
	}
	void SQLDBEngine::disConnect()
	{
		mysql_close (&conn);
	}
	void SQLDBEngine::CheckConnection()
	{
		if (conn.status!=mysql_status::MYSQL_STATUS_READY)
		{
			connect(sqlHost.data(),sqlport,sqlUser.data(),sqlPassword.data(),sqlDatabase.data());
		}
	}
	void SQLDBEngine::insertData(const std::string& tablename, std::string keyName, long long keyValue,
	       std::map<std::string, std::string>& vds)
	{

		if (keyValue == 0)
		{
			return;
		}
		std::string values = "";
		std::string cmd = "replace into " + tablename + "("+ keyName +"";
		for (auto &kv : vds)
		{
			cmd.append("," + kv.first);
			values.append(",'" + kv.second + "'");
		}
		
		cmd.append(") VALUES(" + std::to_string(keyValue));
		cmd.append(values);
		cmd.append(");");
		CheckConnection();
		int res = mysql_query(&conn, cmd.c_str());
		if (!res)
		{
		}
		else
		{
			LOGI("数据库 命令：" << cmd << "插入失败!");
		}

	}
	
	void SQLDBEngine::updateData(const std::string& tablename, std::string keyName, long long keyValue,
	        std::map<std::string, std::string>& vds)
	{
		if (keyValue == 0)
		{
			return;
		}
		std::string cmd = "update  " + tablename + " SET ";
		bool first = true;
		for (auto &kv : vds)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				cmd.append(",");
			}
			cmd.append(kv.first + " = '" + kv.second + "' ");
			
		}
		cmd.append("where "+ keyName +"= " + std::to_string(keyValue) + ";");
		//std::cout << cmd << std::endl;
		CheckConnection();
		int res = mysql_query(&conn, cmd.c_str());
		if (!res)
		{
		}
		else
		{
			LOGI("数据库 命令：" << cmd << "更新失败!");
		}

	}
	
	void SQLDBEngine::deleteData(const std::string& tablename, std::string keyName, long long keyValue )
	{
		if (keyValue == 0)
		{
			return;
		}
		std::string cmd = "DELETE from " + tablename + " WHERE "+ keyName +"="
		        + std::to_string(keyValue) + ";";
		CheckConnection();
		int res = mysql_query(&conn, cmd.c_str());
		if (!res)
		{
		}
		else
		{
			LOGI("数据库 命令：" << cmd << "删除失败!");
		}
	}
}
