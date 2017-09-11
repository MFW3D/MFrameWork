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
	//�ӹ����л�ȡһ����Ҷ�����������Ѿ����ھͷ����Ѵ��ڵ���ң���������ڴ���
	bool GetPlayer(EChess_Type type, long long Uid, std::shared_ptr<Chess_Player_XZMJ>& playerptr);
	//����һ�����
	void DelPlayer(EChess_Type type, long long Uid);
	void DelPlayer(EChess_Type type, std::shared_ptr<Chess_Player_XZMJ> playerptr);


};