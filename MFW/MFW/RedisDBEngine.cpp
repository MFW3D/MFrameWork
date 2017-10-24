#include "RedisDBEngine.h"
#include <string>
#include <string.h>
#include "NetUtility.h"
#if _MSC_VER
#define strcasecmp _stricmp  //strcasecmp 找不到标识符
//#pragma comment(lib,"..\\lib\\Win32_Interop.lib") 
#endif
using namespace std;
namespace DBProduce
{
	RedisDBEngine::RedisDBEngine()
	{
		std::lock_guard<std::mutex> lg(locker);
		c = nullptr;
		r = nullptr;
	}

	RedisDBEngine::~RedisDBEngine()
	{
		freeReplyObject(r);
		redisFree(c);
	}
	void RedisDBEngine::HandData(DBMsg& wbMsg)
	{
		switch (wbMsg.dbCMD)
		{
		case DBCMD::dbdelete:
		{
			std::string cmd = "del '" + wbMsg.tablename + ":"
				+ std::to_string(wbMsg.keyValue) + "'";
			if (!excuteCommoned(cmd))
			{
				std::cout << cmd + "' fail";
			}
		}
		break;
		case DBCMD::dbinsert:
		case DBCMD::dbupdate:
		{
			std::string cmd = "hmset " + wbMsg.tablename + ":"
				+ std::to_string(wbMsg.keyValue) + " ";

			for (auto &kv : (wbMsg.data))
			{
				if (kv.second == "")
				{
					cmd.append(kv.first + " " + NetUtility::replace(kv.second, " ", "$$") + " ");
				}
				else
				{
					cmd.append(kv.first + " " + NetUtility::replace(kv.second, " ", "$$") + " ");
				}
			}

			if (!excuteCommoned(cmd))
			{
				std::cout << cmd + " fail";
			}
		}
		break;
		case DBCMD::dbnone:
			break;
		}
	}
	bool RedisDBEngine::connect(std::string ip, short port)
	{
		std::lock_guard<std::mutex> lg(locker);

		redisIp = ip;
		redisPort = port;
		c = redisConnect(ip.c_str(), port);
		if (c->err)
		{
			redisFree(c);
			printf("Connect to redisServer faile\n");
			return false;
		}
		printf("Connect to redisServer Success\n");
		return true;
	}
	void RedisDBEngine::disConnect()
	{

	}
	bool RedisDBEngine::excuteCommoned(std::string cmd, std::string& results)
	{
		locker.lock();
		if (c == nullptr)
		{
			if (!connect(redisIp, redisPort))
			{
				locker.unlock();
				return excuteCommoned(cmd, results);
			}
		}
		r = (redisReply*)redisCommand(c, cmd.c_str());
		if (nullptr == r)
		{
			results = "Execut command1 failure\n";
			locker.unlock();
			return false;
		}
		if (!r->type == REDIS_REPLY_NIL && r->type == REDIS_REPLY_ERROR)
		{
			results = "Execut command1 failure\n";
			locker.unlock();
			return false;
		}
		else if (r->type == REDIS_REPLY_ARRAY)
		{
			for (unsigned int j = 0; j < r->elements; j++)
			{
				if (j == 0)
				{
					if (r->element[j]->str != nullptr)
						results.append(r->element[j]->str);
				}
				else
				{
					results.append(" ");
					if (r->element[j]->str != nullptr)
						results.append(r->element[j]->str);
				}
			}
		}
		else if (r->type == REDIS_REPLY_INTEGER)
		{
			results.append(std::to_string(r->integer));
		}
		else if (r->type == REDIS_REPLY_NIL)
		{
			locker.unlock();

			return false;
		}
		else
		{
			if (r->str != nullptr)
			{
				results.append(r->str);
			}
		}
		locker.unlock();

		return true;
	}
	bool RedisDBEngine::excuteCommoned(std::string& cmd)
	{
		locker.lock();

		if (c == nullptr)
		{
			if (!connect(redisIp, redisPort))
			{
				locker.unlock();
				return excuteCommoned(cmd);
			}
		}
		r = (redisReply*)redisCommand(c, cmd.data());
		if (NULL == r)
		{
			locker.unlock();
			return false;
		}
		locker.unlock();
		return true;
	}
	bool RedisDBEngine::excuteCommoned(char* cmd)
	{
		locker.lock();
		if (c == nullptr)
		{
			if (!connect(redisIp, redisPort))
			{
				locker.unlock();
				return excuteCommoned(cmd);
			}
		}
		r = (redisReply*)redisCommand(c, cmd);

		if (NULL == r)
		{
			locker.unlock();
			return false;
		}
		locker.unlock();
		return true;
	}

}