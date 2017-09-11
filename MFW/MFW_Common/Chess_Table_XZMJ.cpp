#include "Chess_Table_XZMJ.h"

//设置庄家
void Chess_Table_XZMJ::SetZhuang(long long Uid)
{
	if (MPlayerGaming.find(Uid) != MPlayerGaming.end())
	{
		mChess_Player_XZMJZhuang = MPlayerGaming[Uid];
	}
}
//开始发牌
void Chess_Table_XZMJ::StartFaPai()
{
	//先各自摸13张牌，然后庄家再摸一张
	for (auto playerItr = MPlayerGaming.begin(); playerItr != MPlayerGaming.end(); playerItr++)
	{
		std::vector<std::shared_ptr<Chess_Card_MJ>> cards;
		if (mChess_Rule_XZMJ->GetCards(13, cards))
		{
			for each(auto itr in cards)
			{
				if (playerItr->second->mCards.find(itr->MEMJ_Card) == playerItr->second->mCards.end())
				{
					playerItr->second->mCards.insert(std::pair<EMJ_Card, int>(
						itr->MEMJ_Card, 1));
				}
				else
				{
					playerItr->second->mCards[itr->MEMJ_Card] += 1;
				}
				mChess_Player_XZMJZhuang->mCardMJs.push_back(itr);
			}
		}
	}
	//给庄家多发一张牌
	std::shared_ptr<Chess_Card_MJ> card;
	if (mChess_Rule_XZMJ->GetCard(card))
	{
		if (mChess_Player_XZMJZhuang->mCards.find(card->MEMJ_Card) == mChess_Player_XZMJZhuang->mCards.end())
		{
			mChess_Player_XZMJZhuang->mCards.insert(std::pair<EMJ_Card, int>(
				card->MEMJ_Card, 1));
		}
		else
		{
			mChess_Player_XZMJZhuang->mCards[card->MEMJ_Card] += 1;
		}
		mChess_Player_XZMJZhuang->mCardMJs.push_back(card);
	}
}

//检查玩家是否都进入
bool Chess_Table_XZMJ::CheckPlayerEnterFinished()
{
	if (MPlayerGaming.size() == mChess_Table_XZMJ_INfo.mPlayerGamingCount)
		return true;
	else
		return false;
}
//检查玩家是否都准备
bool Chess_Table_XZMJ::CheckPlayerAllReady()
{
	for each(auto itr in MPlayerGaming)
	{
		if (itr.second->mEPlayer_XZMJ_State
			!= EPlayer_XZMJ_State::Pre_Prepered)
		{
			return false;
		}
	}
}
//检查玩家是否都定缺完成
bool Chess_Table_XZMJ::CheckPlayerAllQue()
{
	for each(auto itr in MPlayerGaming)
	{
		if (itr.second->mEPlayer_XZMJ_State
			!= EPlayer_XZMJ_State::Pre_Qued)
		{
			return false;
		}
	}
}
//判断当前玩家是否胡牌
bool Chess_Table_XZMJ::CheckPlayerNowHu()
{
	mChess_Rule_XZMJ->CheckHu(true);
	if (mWaitHus.size() > 0)
		return true;
	else
		return false;
}
//判断当前玩家是否可以杠
bool Chess_Table_XZMJ::CheckPlayerNowGang()
{
	mChess_Rule_XZMJ->CheckGang(true);
	if (mWaitHus.size() > 0)
		return true;
	else
		return false;
}
//判断其他玩家是否可以胡牌
bool Chess_Table_XZMJ::CheckPlayerOtherHu()
{
	mChess_Rule_XZMJ->CheckHu(false);
	if (mWaitHus.size() > 0)
		return true;
	else
		return false;
}
//判断其他玩家是否可以杠牌
bool Chess_Table_XZMJ::CheckPlayerOtherGang()
{
	mChess_Rule_XZMJ->CheckGang(true);
	if (mWaitHus.size() > 0)
		return true;
	else
		return false;
}
//判断其他玩家是否可以碰牌
bool Chess_Table_XZMJ::CheckPlayerOtherPeng()
{
	mChess_Rule_XZMJ->CheckPeng();
	if (mWaitHus.size() > 0)
		return true;
	else
		return false;
}
//判断游戏是否结束
bool Chess_Table_XZMJ::CheckGameOver()
{
	int count = 0;
	for (auto itr = MPlayerGaming.begin(); itr != MPlayerGaming.end(); itr++)
	{
		if (itr->second->mEPlayer_XZMJ_State == EPlayer_XZMJ_State::Over_Hued)
			count++;
	}
	if (count >= MPlayerGaming.size() - 1)
		return true;
	else
		return false;
}

//玩家进入游戏
bool Chess_Table_XZMJ::PlayerGetIn(
	std::shared_ptr<Chess_Player_XZMJ> playerPtr, EPlayer_Type type)
{
	if (MPlayerGaming.find(playerPtr->GetPlayer()->GetBaseInfo().uid) !=
		MPlayerGaming.end())
	{
		MPlayerGaming.erase(playerPtr->GetPlayer()->GetBaseInfo().uid);
	}
	if (MPlayerWaiting.find(playerPtr->GetPlayer()->GetBaseInfo().uid) !=
		MPlayerWaiting.end())
	{
		MPlayerWaiting.erase(playerPtr->GetPlayer()->GetBaseInfo().uid);
	}
	if (MPlayerWatching.find(playerPtr->GetPlayer()->GetBaseInfo().uid) !=
		MPlayerWatching.end())
	{
		MPlayerWatching.erase(playerPtr->GetPlayer()->GetBaseInfo().uid);
	}
	switch (type)
	{
	case EPlayer_Type::None:
		return false;
	case EPlayer_Type::Watch:
		MPlayerWatching.insert(std::pair<long long, std::shared_ptr<Chess_Player_XZMJ>>(
			playerPtr->GetPlayer()->GetBaseInfo().uid, playerPtr));
		break;
	case EPlayer_Type::Wait:
		MPlayerWaiting.insert(std::pair<long long, std::shared_ptr<Chess_Player_XZMJ>>(
			playerPtr->GetPlayer()->GetBaseInfo().uid, playerPtr));
		break;
	case EPlayer_Type::Game:
		MPlayerGaming.insert(std::pair<long long, std::shared_ptr<Chess_Player_XZMJ>>(
			playerPtr->GetPlayer()->GetBaseInfo().uid, playerPtr));
		break;
	default:
		return false;
	}
}

void Chess_Table_XZMJ::SetPlayerNow(long long Uid)
{
	if (MPlayerGaming.find(Uid) != MPlayerGaming.end())
	{
		mChess_Player_XZMJNow = MPlayerGaming[Uid];
	}
}
void Chess_Table_XZMJ::SetPlayerOp(long long Uid)
{
	if (MPlayerGaming.find(Uid) != MPlayerGaming.end())
	{
		mChess_Player_XZMJOp = MPlayerGaming[Uid];
	}
}
