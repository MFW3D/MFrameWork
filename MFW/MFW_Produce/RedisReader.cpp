#include "RedisReader.h"
namespace DBProduce
{
    DBProduce::RedisDBEngine* RedisReader::redisEngine = nullptr;
	void RedisReader::setRedisEngine(DBProduce::RedisDBEngine* _redisEngine)
	{
		redisEngine = _redisEngine;
	}
	bool RedisReader::GetDBAccount(std::shared_ptr<DBAccount> p, std::string uid)

    {
		if (p == nullptr)
		{
			return false;
		}
		std::string results = "";
		std::string cmd = "hmget DBAccount:" + uid
                + " acc  pwd  tel  wx  qq  lastlogin  createtime ";
		if (!redisEngine->excuteCommoned(cmd.c_str(), results))
		{
			return false;
		}
		std::vector < std::string > vec;
		DBCommon::split(results, vec, " ");
		if (vec.size() >= 7)
		{
            p->uid = atof(uid.c_str());
            p->acc = NetUtility::HexToBin(vec[0]);
            p->pwd = NetUtility::HexToBin(vec[1]);
            p->tel = NetUtility::HexToBin(vec[2]);
            p->wx = NetUtility::HexToBin(vec[3]);
            p->qq = NetUtility::HexToBin(vec[4]);
            p->lastlogin = atoll(vec[5].c_str());
            p->createtime = atoll(vec[6].c_str());
        }
		else
		{
			return false;
		}
		return true;
	}
	bool RedisReader::GetDBUserInfo(std::shared_ptr<DBUserInfo> p, std::string uid)

    {
		if (p == nullptr)
		{
			return false;
		}
		std::string results = "";
		std::string cmd = "hmget DBUserInfo:" + uid
                + " nickname ";
		if (!redisEngine->excuteCommoned(cmd.c_str(), results))
		{
			return false;
		}
		std::vector < std::string > vec;
		DBCommon::split(results, vec, " ");
		if (vec.size() >= 1)
		{
            p->uid = atof(uid.c_str());
            p->nickname = NetUtility::HexToBin(vec[0]);
        }
		else
		{
			return false;
		}
		return true;
	}
}
