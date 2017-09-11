#include "AssistantMG.h"

void AssistantMG::SetRedisEngine(DBProduce::RedisDBEngine* _redisEngine)
{
	redisEngine = _redisEngine;
}

bool AssistantMG::GetUserId(long long & id, std::string acount)
{
	std::string results = "";
	std::string cmd = "get DBAccount_accid:" + acount ;
	if (!redisEngine->excuteCommoned(cmd, results))
	{
		return false;
	}
	std::vector < std::string > vec;
	NetUtility::split(results, vec, " ");
	if (vec.size() >= 1)
	{
		id = atoll(vec[0].c_str());
	}
	else
	{
		return false;
	}
	return true;


}
bool AssistantMG::Getvalue(std::string tablename, std::string& key, std::string& value)
{
	std::string results = "";
	std::string cmd = "get "+ tablename +":" + key;
	if (!redisEngine->excuteCommoned(cmd, results))
	{
		return false;
	}
	std::vector < std::string > vec;
	NetUtility::split(results, vec, " ");
	if (vec.size() >= 1)
	{
		value = vec[0].c_str();
	}
	else
	{
		return false;
	}
	return true;
}
bool AssistantMG::Setvalue(std::string tablename,const std::string& key, const std::string& value)
{
	std::string results = "";
	std::string cmd = "set " + tablename + ":" + key+" "+value;
	if (!redisEngine->excuteCommoned(cmd, results))
	{
		return false;
	}
	std::vector < std::string > vec;
	NetUtility::split(results, vec, " ");
	if (vec.size() >= 1)
	{
		//value = vec[0].c_str();
	}
	else
	{
		return false;
	}
	return true;
}

