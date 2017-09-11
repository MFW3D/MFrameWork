#pragma once

#include "Chess_Table_XZMJ.h"
#include "Chess_Player_XZMJ.h"
class Chess_Player_XZMJ;
class Chess_Rule_XZMJ;

class Chess_Table_XZMJ_INfo
{
public:
	int mPlayerCount = 10;//玩家总数
	int mPlayerGamingCount = 4;//游戏玩家总数
};
class Chess_Table_XZMJ
{
private:
	//庄家
	std::shared_ptr<Chess_Player_XZMJ> mChess_Player_XZMJZhuang;
public:
	//桌子基础信息
	Chess_Table_XZMJ_INfo mChess_Table_XZMJ_INfo;

	//正在游戏玩家
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayerGaming;	//正在进行的玩家
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayerWaiting;	//准备的玩家
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayerWatching;	//观察者
	std::shared_ptr<Chess_Player_XZMJ> mPlayerNow;

	//当前能碰杠胡的玩家索引
	std::vector<std::shared_ptr<Chess_Player_XZMJ>> mWaitPengs;
	std::vector<std::shared_ptr<Chess_Player_XZMJ>> mWaitGangs;
	std::vector<std::shared_ptr<Chess_Player_XZMJ>> mWaitHus;
	//当前出牌玩家，操作玩家
	std::shared_ptr<Chess_Player_XZMJ> mChess_Player_XZMJNow;
	std::shared_ptr<Chess_Player_XZMJ> mChess_Player_XZMJOp;

	//当前的牌
	std::shared_ptr<Chess_Card_MJ> mChess_Card_MJNow;
	//规则指针
	std::shared_ptr<Chess_Rule_XZMJ> mChess_Rule_XZMJ;

/************************************************************************/
/* 游戏状态判断                                                          */
/************************************************************************/
	//检查玩家是否都进入
	bool CheckPlayerEnterFinished();
	//检查玩家是否都准备
	bool CheckPlayerAllReady();
	//检查玩家是否都定缺完成
	bool CheckPlayerAllQue();
	//判断当前玩家是否胡牌
	bool CheckPlayerNowHu();
	//判断当前玩家是否可以杠
	bool CheckPlayerNowGang();
	//判断其他玩家是否可以胡牌
	bool CheckPlayerOtherHu();
	//判断其他玩家是否可以杠牌
	bool CheckPlayerOtherGang();
	//判断其他玩家是否可以碰牌
	bool CheckPlayerOtherPeng();
	//判断游戏是否结束
	bool CheckGameOver();

/************************************************************************/
/* 游戏流程控制                                                          */
/************************************************************************/
	//玩家加入游戏
	bool PlayerGetIn(std::shared_ptr<Chess_Player_XZMJ> playerPtr,EPlayer_Type type);
	//设置庄家
	void SetZhuang(long long Uid);
	//开始发牌
	void StartFaPai();
	//设置当前出牌玩家
	void SetPlayerNow(long long Uid);
	//设置当前操作玩家
	void SetPlayerOp(long long Uid);
};