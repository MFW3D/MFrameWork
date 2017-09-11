#include "Player.h"
DBProduce::DBUserInfo Player::GetBaseInfo()
{
	return baseInfo;
}
void Player::ParseFrome(PCommon_Base::PUserInfo& pUserInfo)
{
	baseInfo.uid = pUserInfo.uid();
	baseInfo.nickname = pUserInfo.nickname();
}
std::string Player::SeriliseTo(PCommon_Base::PUserInfo& pUserInfo)
{
	pUserInfo.set_uid(baseInfo.uid);
	pUserInfo.set_nickname(baseInfo.nickname);
	return pUserInfo.SerializeAsString();
}
