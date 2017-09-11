#pragma once
#include <map>
#include <list>
#include <memory>
#include "Chess_Global.h"
#include "Chess_Player_XZMJ.h"

class Chess_PlayerBase
{
public:
	EChess_Type MEChess_Type;
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayers;
};

class Chess_Player_Factory
{
private:
	std::map<EChess_Type, std::shared_ptr<Chess_PlayerBase>> MAllPlayers;
public:
	//从工厂中获取一个玩家对象，如果对象已经存在就返回已存在的玩家，如果不存在创建
	bool GetPlayer(EChess_Type type, long long Uid, std::shared_ptr<Chess_Player_XZMJ>& playerptr);
	//销毁一个玩家
	void DelPlayer(EChess_Type type, long long Uid);
	void DelPlayer(EChess_Type type, std::shared_ptr<Chess_Player_XZMJ> playerptr);


};