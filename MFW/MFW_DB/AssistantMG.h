/************************************************************
 * FileName: AssistantMG.h
 * Author: 毛自豪
 * Version : V0.1
 * Date: 2015年09月14日 09:48:00
 * Description: 数据库 相关的辅助数据结构构造和操作，重点需要考虑与数据库其它数据同步
 ***********************************************************/
#pragma once
#include  "RedisDBEngine.h"
#include "DBTypes.h"
#include "NetUtility.h"
#include "Singleton.h"
class AssistantMG:public MFW::Singleton<AssistantMG>
{
private:
	  DBProduce::RedisDBEngine* redisEngine;
public:
	  void SetRedisEngine(DBProduce::RedisDBEngine* _redisEngine);

	  bool GetUserId(long long & id, std::string acount);
	  bool Getvalue(std::string tablename, std::string& key, std::string& value);
	  bool Setvalue(std::string tablename, const std::string& key, const std::string& value);



};

