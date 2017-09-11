#pragma once

enum class EChess_Type
{
	None = 0,
	XZMJ = 1,
};

//游戏中玩家的角色
enum class EPlayer_Type
{
	None = 0,		//未参与玩家
	Watch = 1,		//观战
	Wait = 2,		//等待加入
	Game = 3,		//正在游戏

};
//血战麻将桌子状态未开始，
enum class ETable_XZMJ_State
{
	None = 0,
	Pre_off = 11,
	Pre_WaitPlayer = 12,
	Pre_WaitPreper = 13,

	Game_Start = 21,
	Game_WaitQue = 22,
	Game_WaitPlay = 23,
	Game_WaitOption = 24,

	OVER_Balance = 31,
	Over_ReNew = 32,
	Over_RePlay = 33,
};
//血战麻将玩家状态
enum class EPlayer_XZMJ_State {
	None = 0,
	Pre_EnterRoomed = 1,
	Pre_Prepered = 2,
	Pre_Qued = 3,
	Game_OnTurn = 11,	//自己的出牌阶段
	Game_OffTurn = 12,//自己的空闲阶段
	Game_WaitP = 13,//等待自己碰杠胡
	Game_WaitG = 14,//等待自己碰杠胡
	Game_WaitH = 15,//等待自己碰杠胡
	Game_WaitOtherP = 16,//等待自己碰杠胡
	Game_WaitOtherG = 17,//等待自己碰杠胡
	Game_WaitOtherH = 18,//等待自己碰杠胡
	Over_Hued = 19,
};
//血站麻将的胡牌牌型
enum class EPaiXing_XZMJ
{
	None = 0,

};
