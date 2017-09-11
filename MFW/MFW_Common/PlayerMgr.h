#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "Singleton.h"
#include "Player.h"
#include <mutex>
#include <thread>
/*
管理服务器在线的玩家
*/
class PlayerMgr :public MFW::Singleton<PlayerMgr>
{
private:
	//服务器中的所有玩家
	std::mutex mPlayersMutex;
	std::unordered_map<long long, std::shared_ptr<Player>> mPlayers;
public:
	//获取玩家信息
	bool GetPlayer(long long id, std::shared_ptr<Player>& playerptr);
	//添加玩家
	bool AddPlayer(long long id, std::shared_ptr<Player>& playerptr);
	//删除玩家
	bool SubPlayer(long long);
	//获取所有的玩家
	std::unordered_map<long long, std::shared_ptr<Player>>& GetPlayerMap();
};

