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
	long long mId;	//ʱ��id
	long long mTick;	//��ʱ��
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
	std::map<long long, std::shared_ptr<Timer>> mIDTimers;//id��Ӧ
	std::multimap<long long, std::shared_ptr<Timer>,std::less<long long>> mTickTimers;//ʱ���Ӧ
	std::mutex mTimerMutex;

	void PushTimer(Timer& timer);
	bool PopTimer(Timer& timer);
public:
	void Run();
	void Process();
	long long  StartTimer(long long& NextTick, std::function<void(Timer)> timerCB, void* data);
	long long  StartTimerMill(long long& ticks, std::function<void(Timer)> timerCB, void* data);
	//������ʱ����ʱ��������
	long long  StartTimerSecond(long long& ticks, std::function<void(Timer)> timerCB, void* data);
	bool ResetTimer(long long& timerId, long long& NextTick);
	bool ResetTimerMill(long long& timerId, long long& ticks);
	bool ResetTimerSecond(long long& timerId, long long& ticks);
	bool CancelTimer(long long& timerId);
};