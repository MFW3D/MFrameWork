#include "Chess_Rule_XZMJ.h"
#include "Chess_Card_MJ.h"
#include "NetUtility.h"

void Chess_Rule_XZMJ::init()
{
	//初始化总共的牌
	mCards.clear();
	std::shared_ptr<Chess_Card_MJ> Wan1(new Chess_Card_MJ(EMJ_Card::Wan_1));
	std::shared_ptr<Chess_Card_MJ> Wan2(new Chess_Card_MJ(EMJ_Card::Wan_2));
	std::shared_ptr<Chess_Card_MJ> Wan3(new Chess_Card_MJ(EMJ_Card::Wan_3));
	std::shared_ptr<Chess_Card_MJ> Wan4(new Chess_Card_MJ(EMJ_Card::Wan_4));
	std::shared_ptr<Chess_Card_MJ> Wan5(new Chess_Card_MJ(EMJ_Card::Wan_5));
	std::shared_ptr<Chess_Card_MJ> Wan6(new Chess_Card_MJ(EMJ_Card::Wan_6));
	std::shared_ptr<Chess_Card_MJ> Wan7(new Chess_Card_MJ(EMJ_Card::Wan_7));
	std::shared_ptr<Chess_Card_MJ> Wan8(new Chess_Card_MJ(EMJ_Card::Wan_8));
	std::shared_ptr<Chess_Card_MJ> Wan9(new Chess_Card_MJ(EMJ_Card::Wan_9));
	std::shared_ptr<Chess_Card_MJ> Tiao1(new Chess_Card_MJ(EMJ_Card::Tiao_1));
	std::shared_ptr<Chess_Card_MJ> Tiao2(new Chess_Card_MJ(EMJ_Card::Tiao_2));
	std::shared_ptr<Chess_Card_MJ> Tiao3(new Chess_Card_MJ(EMJ_Card::Tiao_3));
	std::shared_ptr<Chess_Card_MJ> Tiao4(new Chess_Card_MJ(EMJ_Card::Tiao_4));
	std::shared_ptr<Chess_Card_MJ> Tiao5(new Chess_Card_MJ(EMJ_Card::Tiao_5));
	std::shared_ptr<Chess_Card_MJ> Tiao6(new Chess_Card_MJ(EMJ_Card::Tiao_6));
	std::shared_ptr<Chess_Card_MJ> Tiao7(new Chess_Card_MJ(EMJ_Card::Tiao_7));
	std::shared_ptr<Chess_Card_MJ> Tiao8(new Chess_Card_MJ(EMJ_Card::Tiao_8));
	std::shared_ptr<Chess_Card_MJ> Tiao9(new Chess_Card_MJ(EMJ_Card::Bing_9));
	std::shared_ptr<Chess_Card_MJ> Bing1(new Chess_Card_MJ(EMJ_Card::Bing_1));
	std::shared_ptr<Chess_Card_MJ> Bing2(new Chess_Card_MJ(EMJ_Card::Bing_2));
	std::shared_ptr<Chess_Card_MJ> Bing3(new Chess_Card_MJ(EMJ_Card::Bing_3));
	std::shared_ptr<Chess_Card_MJ> Bing4(new Chess_Card_MJ(EMJ_Card::Bing_4));
	std::shared_ptr<Chess_Card_MJ> Bing5(new Chess_Card_MJ(EMJ_Card::Bing_5));
	std::shared_ptr<Chess_Card_MJ> Bing6(new Chess_Card_MJ(EMJ_Card::Bing_6));
	std::shared_ptr<Chess_Card_MJ> Bing7(new Chess_Card_MJ(EMJ_Card::Bing_7));
	std::shared_ptr<Chess_Card_MJ> Bing8(new Chess_Card_MJ(EMJ_Card::Bing_8));
	std::shared_ptr<Chess_Card_MJ> Bing9(new Chess_Card_MJ(EMJ_Card::Bing_9));
	//初始化所有的牌
	for (int i = 0; i < 4; i++)
	{
		mCards.push_back(Wan1);
		mCards.push_back(Wan2);
		mCards.push_back(Wan3);
		mCards.push_back(Wan4);
		mCards.push_back(Wan5);
		mCards.push_back(Wan6);
		mCards.push_back(Wan7);
		mCards.push_back(Wan8);
		mCards.push_back(Wan9);
		mCards.push_back(Tiao1);
		mCards.push_back(Tiao2);
		mCards.push_back(Tiao3);
		mCards.push_back(Tiao4);
		mCards.push_back(Tiao5);
		mCards.push_back(Tiao6);
		mCards.push_back(Tiao7);
		mCards.push_back(Tiao8);
		mCards.push_back(Tiao9);
		mCards.push_back(Bing1);
		mCards.push_back(Bing2);
		mCards.push_back(Bing3);
		mCards.push_back(Bing4);
		mCards.push_back(Bing5);
		mCards.push_back(Bing6);
		mCards.push_back(Bing7);
		mCards.push_back(Bing8);
		mCards.push_back(Bing9);
	}
	//初始化胡牌牌型和番数
	mEPaiXing_XZMJFans.clear();

}

bool Chess_Rule_XZMJ::MayHu(std::vector<int>pai, int queZhang)
{
	if (remainPai(pai))
	{
		jiangPai = 0;
		return true;
	}
	for (int i = 1; i < 30; i++)
	{

		if (pai[i] <= 0 || (i > queZhang && i < queZhang + 10)
			|| (i % 10 == 0))
		{
			continue;
		}
		if (pai[i] == 4)
		{
			pai[i] = 0;
			if (MayHu(pai, queZhang))
			{
				return true;
			}
			pai[i] = 4;
		}
		if (pai[i] >= 3)
		{
			pai[i] -= 3;
			if (MayHu(pai, queZhang))
			{
				return true;
			}
			pai[i] += 3;
		}
		if (jiangPai == 0 && pai[i] >= 2)
		{
			jiangPai = 1;
			pai[i] -= 2;
			if (MayHu(pai, queZhang))
			{
				return true;
			}
			jiangPai = 0;
			pai[i] += 2;
		}
		if (i % 10 != 8 && i % 10 != 9 && pai[i + 1] > 0 && pai[i + 2] > 0)
		{
			pai[i]--;
			pai[i + 1]--;
			pai[i + 2]--;
			if (MayHu(pai, queZhang))
			{
				return true;
			}
			pai[i]++;
			pai[i + 1]++;
			pai[i + 2]++;
		}

	}
	return false;
}
bool Chess_Rule_XZMJ::remainPai(std::vector<int> pai)
{
	int sum = 0;
	for (int i = 0; i < pai.size(); i++)
	{
		sum += pai[i];
	}
	if (sum == 0)
	{
		return true;
	}
	return false;
}
//码城墙
void Chess_Rule_XZMJ::BuildWall()
{
	mWalls = mCards;
	//随机数,随机出城墙
	std::mt19937 g(CHRONO_SYSTEM_NOW_MICRO());
	std::shuffle(mWalls.begin(), mWalls.end(), g);
}
bool Chess_Rule_XZMJ::GetCards(int count, std::vector<std::shared_ptr<Chess_Card_MJ>>& cards)
{
	if (mWalls.size() < count)
		return false;
	for (int i = 0; i < count; i++)
	{
		std::shared_ptr<Chess_Card_MJ> card = nullptr;
		if (GetCard(card))
		{
			cards.push_back(card);
		}
	}
	return true;
}

bool Chess_Rule_XZMJ::GetCard(std::shared_ptr<Chess_Card_MJ>& card)
{
	if (mWalls.size() == 0)
		return false;
	auto cd = mWalls.back();
	card.reset((Chess_Card_MJ*)cd.get());
	return true;
}

bool Chess_Rule_XZMJ::GetQue(EChess_Type type, std::vector<std::shared_ptr<Chess_Card_MJ>>& cards,
	std::vector<std::shared_ptr<Chess_Card_MJ>>& queCards)
{
	bool result = true;
	for each (auto card in cards)
	{
		if ((int)card->MEMJ_Card / 10 == (int)type)
		{
			queCards.push_back(card);
			result = false;
		}
	}
	return result;
}

//听牌解析，解析玩家可以听的牌以及对应的倍数
void Chess_Rule_XZMJ::AnalysisTing(std::shared_ptr<Chess_Player_XZMJ> playerPtr)
{
	playerPtr->mTings.clear();
	//判断金钩掉
	if (playerPtr->mCards.size() == 1)
	{
		playerPtr->mTings.insert(std::pair<EMJ_Card, int>(playerPtr->mCards.begin()->first, 1));
		return;
	}
	//判断小小七对
	int countdui = 0;
	EMJ_Card ting = EMJ_Card::None;
	for each(auto dui in playerPtr->mCards)
	{
		if (dui.second == 2)
			countdui++;
		else
			ting = dui.first;
	}
	if (countdui == 6)
	{
		playerPtr->mTings.insert(std::pair<EMJ_Card, int>(ting, 1));
		return;
	}

	std::vector<int> midList = { 0,
		0,0,0,0,0,0,0,0,0,				//        1万～9万的个数      
		0,
		0,0,0,0,0,0,0,0,0,				//         1条～9条的个数      
		0,
		0,0,0,0,0,0,0,0,0				//        1筒～9筒的个数                                         
	};
	for (auto itr = playerPtr->mCards.begin(); itr != playerPtr->mCards.end(); itr++)
	{
		midList[(((int)itr->first / 10) - 4) + ((int)itr->first % 10)] = itr->second;
	}
	int que = (int)playerPtr->mQuePai - 4;

	//判断听牌
	for (int i = 0; i < 30; i++)
	{
		if (i >= que&&i <= que + 10)
			continue;
		std::vector<int> checklist = midList;
		checklist[i] += 1;
		if (MayHu(midList, que))
		{
			playerPtr->mTings.insert(std::pair<EMJ_Card, int>((EMJ_Card)(((i / 10) + 4) * 10 + i % 10), 1));
		}
	}
}

//检查碰
void Chess_Rule_XZMJ::CheckPeng()
{
	mChess_Table->mWaitPengs.clear();
	for each (auto playerPtr in mChess_Table->MPlayerGaming)
	{
		if (playerPtr.second == mChess_Table->mChess_Player_XZMJNow)
			continue;
		auto itr = playerPtr.second->mCards.find(mChess_Table->mChess_Card_MJNow->MEMJ_Card);
		if (itr != playerPtr.second->mCards.end())
		{
			if (itr->second >= 2)
				mChess_Table->mWaitPengs.push_back(playerPtr.second);

		}
	}
}
//检查杠
void Chess_Rule_XZMJ::CheckGang(bool isself)
{
	mChess_Table->mWaitGangs.clear();
	for each (auto playerPtr in mChess_Table->MPlayerGaming)
	{
		if (isself)
		{
			if (playerPtr.second != mChess_Table->mChess_Player_XZMJNow)
				continue;
		}
		else
		{
			if (playerPtr.second == mChess_Table->mChess_Player_XZMJNow)
				continue;
		}
		auto itr = playerPtr.second->mCards.find(mChess_Table->mChess_Card_MJNow->MEMJ_Card);
		if (itr != playerPtr.second->mCards.end())
		{
			if (itr->second >= 3)
				mChess_Table->mWaitPengs.push_back(playerPtr.second);
		}
	}
}
//检查胡
void Chess_Rule_XZMJ::CheckHu(bool isself)
{
	mChess_Table->mWaitHus.clear();
	for each(auto playerPtr in mChess_Table->MPlayerGaming)
	{
		if (isself)
		{
			if (playerPtr.second != mChess_Table->mChess_Player_XZMJNow)
				continue;
		}
		else
		{
			if (playerPtr.second == mChess_Table->mChess_Player_XZMJNow)
				continue;
		}
		std::vector<int> midList = { 0,
			0,0,0,0,0,0,0,0,0,				//        1万～9万的个数      
			0,
			0,0,0,0,0,0,0,0,0,				//         1条～9条的个数      
			0,
			0,0,0,0,0,0,0,0,0				//        1筒～9筒的个数                                         
		};
		for (auto itr = playerPtr.second->mCards.begin(); itr != playerPtr.second->mCards.end(); itr++)
		{
			midList[(((int)itr->first / 10) - 4) + ((int)itr->first % 10)] = itr->second;
		}
		int que = (int)playerPtr.second->mQuePai - 4;
		int pai = ((int)mChess_Table->mChess_Card_MJNow->MEMJ_Card / 10 - 4) * 10 + (int)mChess_Table->mChess_Card_MJNow->MEMJ_Card % 10;
		if (pai >= que&&pai <= que + 10)
			continue;
		std::vector<int> checklist = midList;
		checklist[pai] += 1;
		if (MayHu(midList, que))
		{
			mChess_Table->mWaitHus.push_back(playerPtr.second);
		}
	}
}