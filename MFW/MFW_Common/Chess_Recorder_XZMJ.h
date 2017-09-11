#pragma once
#include "Chess_Global.h"
/*
游戏过程中记录玩家的积分，如下雨，以及结算时候的番数
*/
class Chess_Recorder_XZMJ
{
public:
	//重置积分板
	void reset();
	//最终胡牌的牌型
	EPaiXing_XZMJ mEPaiXing_XZMJ= EPaiXing_XZMJ::None;
	int fans = 0;

};
