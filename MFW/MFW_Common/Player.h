#pragma once
#include <string>
#include "DBTypes.h"
#include "Common_Base.pb.h"
/*
��Ϸ�е���Ҷ���
��ƾ����ܿ������ݵĴ��
*/

class Player
{
private:
	//��ҵĻ�����Ϣ���
	DBProduce::DBUserInfo baseInfo;
public:
	DBProduce::DBUserInfo GetBaseInfo();
	void ParseFrome(PCommon_Base::PUserInfo& pUserInfo);
	std::string SeriliseTo(PCommon_Base::PUserInfo& pUserInfo);

};