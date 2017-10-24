#pragma once
#include <map>
#include <thread>
#include <stack>
#include <functional>
#include <queue>
#include <mutex>
#include <unordered_map>
class Timer
{
public:
	long long mId;	//时间id
	long long mTick;	//定时点
	long long mStartTime;	
	void OnTimerCB();
	std::function<void(Timer)> OnTimerPtr;
	void* data;
};

class TimerMgr
{
private:
	std::mutex mFinishedTimerMutex;
	std::queue<Timer> mFinishedTimers;
	long long mTimerId = 0;
	std::shared_ptr<std::thread> mThreadPtr;
	void TimerRun();
	std::map<long long, std::shared_ptr<Timer>> mIDTimers;//id对应
	std::multimap<long long, std::shared_ptr<Timer>,std::less<long long>> mTickTimers;//时间对应
	std::mutex mTimerMutex;

	void PushTimer(Timer& timer);
	bool PopTimer(Timer& timer);
public:
	void Run();
	void Process();
	long long  StartTimer(long long& NextTick, std::function<void(Timer)> timerCB, void* data);
	long long  StartTimerMill(long long& ticks, std::function<void(Timer)> timerCB, void* data);
	//启动定时器，时间间隔秒秒
	long long  StartTimerSecond(long long& ticks, std::function<void(Timer)> timerCB, void* data);
	bool ResetTimer(long long& timerId, long long& NextTick);
	bool ResetTimerMill(long long& timerId, long long& ticks);
	bool ResetTimerSecond(long long& timerId, long long& ticks);
	bool CancelTimer(long long& timerId);
};