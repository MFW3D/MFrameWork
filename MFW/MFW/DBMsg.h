/************************************************************
 * FileName: DBMsg.h
 * Author: 毛自豪
 * Version : V0.1
 * Date: 2015年09月02日 17:12:28
 * Description: 数据库操作统一接口消息类结构，统一mysql和redis数据操作结构
 *
 ***********************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include <queue>
#include <memory>
#include <random>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
namespace DBProduce
{
	//数据库命令操作枚举
	enum DBCMD
	{
		dbnone = 0, dbinsert = 1, dbupdate = 2, dbdelete = 3
	};

	struct DBMsg
	{
		DBMsg();
		DBMsg(std::string _tablename, DBCMD _dbCMD,std::map<std::string, std::string>  _data);
		std::string tablename = "";
		std::string keyName = "";
		long long keyValue = 0;
		DBCMD dbCMD = DBCMD::dbnone;
		std::map<std::string, std::string> data;
	};

}
