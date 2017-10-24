#include "LogicServerMgr.h"


void LogicServerMgr::Init()
{
	long long tick = 5;
	ManagerGlobal::GetInstance()->mMainTimerMgr.StartTimerSecond(tick,
		std::bind(&LogicServerMgr::OnTimer, this, std::placeholders::_1), nullptr);
}
bool LogicServerMgr::AddLogicServer(std::shared_ptr<LogicServerInfo> server)
{

	if (LogicServerInfos.find(server->ServerId) != LogicServerInfos.end())
		return false;
	LogicServerInfos.insert(std::pair<unsigned long long,
		std::shared_ptr<LogicServerInfo>>(server->ServerId, server));
	return true;
}
bool LogicServerMgr::RemoveLogicServer(unsigned long long serverId)
{
	if (LogicServerInfos.find(serverId) != LogicServerInfos.end())
	{
		LogicServerInfos.erase(serverId);
		return true;
	}
	return false;
}
bool LogicServerMgr::CheckLogicServer(unsigned long long serverId)
{
	if (LogicServerInfos.find(serverId) != LogicServerInfos.end())
	{
		return true;
	}
	return false;
}
bool LogicServerMgr::GetPlayerServer(long long uid, unsigned long long& serverID)
{
	for (auto server = LogicServerInfos.begin(); server != LogicServerInfos.end(); server++)
	{
		if (server->second->MangerPlayerInfos.find(uid) != server->second->MangerPlayerInfos.end())
		{
			serverID = server->second->ServerId;
			return true;
		}
	}
	return false;
}
unsigned long long LogicServerMgr::DistributePlayer(long long uid)
{
	unsigned long long serverId = -1;
	int miniCount = 1000000000;
	for (auto server = LogicServerInfos.begin(); server != LogicServerInfos.end(); server++)
	{
		if (miniCount > server->second->MangerPlayerInfos.size())
		{
			serverId = server->second->ServerId;
			miniCount = server->second->MangerPlayerInfos.size();
		}
	}
	return serverId;
}
//大循环
void LogicServerMgr::Process()
{
}
void LogicServerMgr::OnTimer(Timer timer)
{
	//进行清理工作





	long long tick = 5;
	ManagerGlobal::GetInstance()->mMainTimerMgr.StartTimerSecond(tick,
		std::bind(&LogicServerMgr::OnTimer, this, std::placeholders::_1), nullptr);
}