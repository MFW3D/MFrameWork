#pragma once
#include "Singleton.h"
#include "Common_Base.pb.h"
#include <functional>


/*
解决tcp消息的黏包，拆包，组包问题
*/
class NetTcpMsgBuilder:public MFW::Singleton<NetTcpMsgBuilder>
{
public:



	//每次收到数据传入
	//void HandleTcpData();



};
