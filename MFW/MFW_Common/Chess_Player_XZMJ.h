#pragma once
#include <vector>
#include <map>
#include "Chess_Card_MJ.h"
#include "Chess_Rule_XZMJ.h"
#include "Chess_Recorder_XZMJ.h"
#include "Player.h"
/*
Ѫս�齫�����
*/
class Chess_Rule_XZMJ;

class Chess_Player_XZMJ
{
private:
	std::shared_ptr<Player> mPlayer;
public:
	Chess_Player_XZMJ(std::shared_ptr<Player>& player);
	std::shared_ptr<Chess_Rule_XZMJ> MRule;		//���ƹ���
	//���ְ�
	Chess_Recorder_XZMJ mChess_Recorder_XZMJ;
	//��ҵ�״̬
	EPlayer_XZMJ_State mEPlayer_XZMJ_State = EPlayer_XZMJ_State::None;

	//������е���
	std::vector<std::shared_ptr<Chess_Card_MJ>> mCardMJs;
	//��ҽ����������
	std::map<EMJ_Card, int,std::less<EMJ_Card>> mCards;
	//������ܵ���
	std::map<EMJ_Card, int, std::less<EMJ_Card>> mCardPGs;
	//��ҿ����������Լ�����
	std::map<EMJ_Card, int, std::less<EMJ_Card>> mTings;
	//ȱ��
	EMJ_Type mQuePai = EMJ_Type::None;
	virtual void Init();

	//��ȡ��Ϸ��ҵĻ��������Ϣ
	std::shared_ptr<Player> GetPlayer();
};
