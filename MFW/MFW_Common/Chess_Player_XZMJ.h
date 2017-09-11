#pragma once
#include <vector>
#include <map>
#include "Chess_Card_MJ.h"
#include "Chess_Rule_XZMJ.h"
#include "Chess_Recorder_XZMJ.h"
#include "Player.h"
/*
血战麻将的玩家
*/
class Chess_Rule_XZMJ;

class Chess_Player_XZMJ
{
private:
	std::shared_ptr<Player> mPlayer;
public:
	Chess_Player_XZMJ(std::shared_ptr<Player>& player);
	std::shared_ptr<Chess_Rule_XZMJ> MRule;		//棋牌规则
	//积分板
	Chess_Recorder_XZMJ mChess_Recorder_XZMJ;
	//玩家的状态
	EPlayer_XZMJ_State mEPlayer_XZMJ_State = EPlayer_XZMJ_State::None;

	//玩家所有的牌
	std::vector<std::shared_ptr<Chess_Card_MJ>> mCardMJs;
	//玩家解析后的手牌
	std::map<EMJ_Card, int,std::less<EMJ_Card>> mCards;
	//玩家碰杠的牌
	std::map<EMJ_Card, int, std::less<EMJ_Card>> mCardPGs;
	//玩家可以听的牌以及番数
	std::map<EMJ_Card, int, std::less<EMJ_Card>> mTings;
	//缺牌
	EMJ_Type mQuePai = EMJ_Type::None;
	virtual void Init();

	//获取游戏玩家的基本玩家信息
	std::shared_ptr<Player> GetPlayer();
};
