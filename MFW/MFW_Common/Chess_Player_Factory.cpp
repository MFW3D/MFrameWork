#include "Chess_Player_Factory.h"


//从工厂中获取一个玩家对象，如果对象已经存在就返回已存在的玩家，如果不存在创建
bool  Chess_Player_Factory::GetPlayer(EChess_Type type, long long Uid, std::shared_ptr<Chess_Player_XZMJ>& playerptr)
{
	playerptr = nullptr;
	if (MAllPlayers.find(type) == MAllPlayers.end())
	{
		std::shared_ptr<Chess_PlayerBase>  base(new Chess_PlayerBase());
		base->MEChess_Type = type;
		MAllPlayers.insert(std::pair<EChess_Type, std::shared_ptr<Chess_PlayerBase>>(type, base));
	}
	if (MAllPlayers[type]->MPlayers.find(Uid) == MAllPlayers[type]->MPlayers.end())
	{
		//根据不同的类型生成不同的玩家
		switch (type)
		{
		case EChess_Type::XZMJ:
			//playerptr = std::shared_ptr<Chess_Player_XZMJ>(new Chess_Player_XZMJ());
			break;
		default:
			break;
		}
	}
	if (playerptr == nullptr)
		return false;
	else
		return true;
}
//销毁一个玩家
void Chess_Player_Factory::DelPlayer(EChess_Type type, long long Uid)
{

}
void Chess_Player_Factory::DelPlayer(EChess_Type type, std::shared_ptr<Chess_Player_XZMJ> playerptr)
{

}