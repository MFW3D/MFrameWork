#include "PlayerMgr.h"

//��ȡ�����Ϣ
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
//������
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
//ɾ�����
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
//��ȡ���е����
std::unordered_map<long long, std::shared_ptr<Player>>& PlayerMgr::GetPlayerMap()
{
	return mPlayers;
}