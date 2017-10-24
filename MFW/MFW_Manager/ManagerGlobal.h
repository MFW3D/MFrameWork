#pragma once
#include "Timer.h"
#include "Singleton.h"
class ManagerGlobal:public MFW::Singleton<ManagerGlobal>
{
public:
	TimerMgr mMainTimerMgr;
};
