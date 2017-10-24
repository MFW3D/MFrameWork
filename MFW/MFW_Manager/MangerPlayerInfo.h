#pragma once

class MangerPlayerInfo
{
public:
	long long Uid = 0;					//玩家UID
	bool IsOnline = false;				//玩家是否在线
	long long LoginTime = 0;			//玩家登陆时间
	long long OffLienTime = 0;			//玩家断线时间
	unsigned long long ServerId = 0;	//玩家所在服务器ID

};
