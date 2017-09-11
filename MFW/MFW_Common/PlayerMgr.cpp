#include "PlayerMgr.h"

//获取玩家信息
bool PlayerMgr::GetPlayer(long long id, std::shared_ptr<Player>& playerptr)
{
	std::lock_guard<std::mutex> lg(mPlayersMutex);
	if (mPlayers.find(id) != mPlayers.end())
	{
		playerptr = mPlayers[id];
		return true;
	}
	return false;
}
//添加玩家
bool PlayerMgr::AddPlayer(long long id, std::shared_ptr<Player>& playerptr)
{
	std::lock_guard<std::mutex> lg(mPlayersMutex);
	if (mPlayers.find(id) != mPlayers.end())
	{
		return false;
	}
	else
	{
		mPlayers.insert(std::pair<long long, std::shared_ptr<Player>>(id,playerptr));
		return true;
	}
}
//删除玩家
bool PlayerMgr::SubPlayer(long long id)
{
	std::lock_guard<std::mutex> lg(mPlayersMutex);
	if (mPlayers.find(id)!= mPlayers.end())
	{
		mPlayers.erase(id);
		return true;
	}
	return false;
}
//获取所有的玩家
std::unordered_map<long long, std::shared_ptr<Player>>& PlayerMgr::GetPlayerMap()
{
	return mPlayers;
}