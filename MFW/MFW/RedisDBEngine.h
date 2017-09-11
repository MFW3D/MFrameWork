/************************************************************
 * FileName: RedisDBEngine.h
 * Author: 毛自豪
 * Version : V0.1
 * Date: 2015年09月02日 17:12:28
 * Description: redis基本操作类，执行redis命令，依赖hiredis库
 *
 ***********************************************************/

#pragma once
#include "hiredis.h"
#if !_WIN32
#include <unistd.h>
#endif
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
#include "DBMsg.h"

#define CMDBUFSIZE 102400
namespace DBProduce
{
	class RedisDBEngine
	{
	private:
		std::string redisIp;
		short redisPort;

		redisContext* c;
		redisReply* r;
		char cmdBuf[CMDBUFSIZE]{ 0 };
		std::mutex locker;

	public:
		RedisDBEngine();
		virtual ~RedisDBEngine();
		bool connect(std::string ip, short port);
		bool excuteCommoned(std::string cmd, std::string& results);
		bool excuteCommoned(std::string& cmd);
		bool excuteCommoned(char* cmd);
		void disConnect();
		void HandData(DBMsg& wbMsg);
	};
}