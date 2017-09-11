#pragma once
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>

#include "Chess_Global.h"
#include "Chess_Rule_XZMJ.h"
#include "Chess_Card_MJ.h"
#include "Chess_Table_XZMJ.h"

/*
血战麻将规则控制器，状态切换器
1、记录桌子的状态
2、记录玩家的状态
3、判断玩家是否可以出牌
4、判断玩家手牌
*/

class Chess_Table_XZMJ;
class Chess_Player_XZMJ;

class Chess_Rule_XZMJ
{
private:
	int jiangPai = 0;
	bool MayHu(std::vector<int>pai,int queZhang);
	bool remainPai(std::vector<int>pai);
	//胡牌牌型对应的番数
	std::map<EPaiXing_XZMJ, int> mEPaiXing_XZMJFans;
public:
	//原始牌
	std::vector<std::shared_ptr<Chess_Card_MJ>> mCards;
	std::vector<std::shared_ptr<Chess_Card_MJ>> mWalls;
	std::shared_ptr<Chess_Table_XZMJ> mChess_Table;

	virtual void init();
	//码城墙
	void BuildWall();
	//取牌
	bool GetCards(int count, std::vector<std::shared_ptr<Chess_Card_MJ>>& cards);
	bool GetCard(std::shared_ptr<Chess_Card_MJ>& card);
	//缺牌解析，根据花色检查玩家哪一门牌,如果已经缺了返回true，如果没缺返回还有哪些牌
	bool GetQue(EChess_Type type,std::vector<std::shared_ptr<Chess_Card_MJ>>& cards, 
		std::vector<std::shared_ptr<Chess_Card_MJ>>& queCards);
	//听牌解析，解析玩家可以听的牌以及对应的倍数
	void AnalysisTing(std::shared_ptr<Chess_Player_XZMJ> playerPtr);

	//检查碰,playerptr表示打出方
	void CheckPeng();
	//检查杠,isself为true表示自己
	void CheckGang(bool isself);
	//检查胡,isself为true表示自己
	void CheckHu(bool isself);
	//获取玩家牌型的最高得分
	
};
