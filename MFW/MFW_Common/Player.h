#pragma once
#include <string>
#include "DBTypes.h"
#include "Common_Base.pb.h"
/*
游戏中的玩家对象
设计尽可能考虑数据的打包
*/

class Player
{
private:
	//玩家的基础信息打包
	DBProduce::DBUserInfo baseInfo;
public:
	DBProduce::DBUserInfo GetBaseInfo();
	void ParseFrome(PCommon_Base::PUserInfo& pUserInfo);
	std::string SeriliseTo(PCommon_Base::PUserInfo& pUserInfo);

};