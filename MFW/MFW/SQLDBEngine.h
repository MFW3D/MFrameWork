/************************************************************
* FileName: SQLDBEngine.h
* Author: 毛自豪
* Version : v0.1
* Date: 2015年08月31日 09:32:30
* Description: 负责mysql数据库的增删改
* Function List: connection连接数据库，insertData插入数据，updateData更新数据，deleteData删除数据
*
***********************************************************/
#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

#include <thread>

#include <queue>

#include <fstream>
#include <stdio.h>
#include <mysql.h>

#include "DBMsg.h"


namespace DBProduce
{

	class SQLDBEngine

	{

	private:
		std::string sqlHost;
		int sqlport;
		std::string sqlUser;
		std::string sqlPassword;
		std::string sqlDatabase;
		MYSQL conn;

		std::shared_ptr<MYSQL_RES> *res_ptr;

		MYSQL_ROW sqlrow;

	public:

		SQLDBEngine();

		virtual ~SQLDBEngine();

		//提供一dbmsg方式的处理

		void HandData(DBProduce::DBMsg& dbmsg);

		/*用于连接数据库
		* 参数：主机ip 用户名 密码 数据库名*/

		void connect(const char* host, int port, const char* user,const char* password, const char* database);

		void ReConnect();

		/*数据插入mysql*/

		void insertData(const std::string& tablename, std::string keyName , long long keyValue ,
			std::map<std::string, std::string>& vds);

		/*数据更新mysql*/

		void updateData(const std::string& tablename, std::string keyName, long long keyValue,
			std::map<std::string, std::string>& vds);

		/*删除mysql数据*/

		void deleteData(const std::string& tablename, std::string keyName, long long keyValue);

		void CheckConnection();
		void disConnect();


	};


}
