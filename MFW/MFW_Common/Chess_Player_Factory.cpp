#include "Chess_Player_Factory.h"


//�ӹ����л�ȡһ����Ҷ�����������Ѿ����ھͷ����Ѵ��ڵ���ң���������ڴ���
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
		//���ݲ�ͬ���������ɲ�ͬ�����
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
//����һ�����
void Chess_Player_Factory::DelPlayer(EChess_Type type, long long Uid)
{

}
void Chess_Player_Factory::DelPlayer(EChess_Type type, std::shared_ptr<Chess_Player_XZMJ> playerptr)
{

}