#include "Timer.h"
#include <chrono>
#if _WIN32
#include <windows.h>
#else
#include "unistd.h"
#endif
void Timer::OnTimerCB()
{
	if (OnTimerPtr != nullptr)
	{
		OnTimerPtr(*this);
	}
}

void TimerMgr::TimerRun()
{
	while (true)
	{
		
		long long sys_now = std::chrono::time_point_cast<std::chrono::milliseconds>(
			std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
		mTimerMutex.lock();
		for (auto itr = mTickTimers.begin(); itr != mTickTimers.end(); )
		{
			if (itr->second->mTick <= sys_now)
			{
				Timer timer = *itr->second;
				PushTimer(timer);
				mIDTimers.erase(timer.mId);
				mTickTimers.erase(itr++);
			}
			else
			{
				break;
			}
		}
		mTimerMutex.unlock();
#if _WIN32
		Sleep(10);
#else
		usleep(10000);
#endif
	}

}

void TimerMgr::Run()
{
	mThreadPtr = std::shared_ptr<std::thread>(new std::thread(std::bind(&TimerMgr::TimerRun, this)));
}

void TimerMgr::PushTimer(Timer& timer)
{
	mFinishedTimerMutex.lock();
	mFinishedTimers.push(timer);
	mFinishedTimerMutex.unlock();
}

bool TimerMgr::PopTimer(Timer& timer)
{
	mFinishedTimerMutex.lock();
	if (mFinishedTimers.size() == 0) {
		mFinishedTimerMutex.unlock();
		return false;
	}
	timer = mFinishedTimers.front();
	mFinishedTimers.pop();
	mFinishedTimerMutex.unlock();
	return true;
}

void TimerMgr::Process()
{
	int count = 100;
	Timer timer;
	while (PopTimer(timer))
	{
		timer.OnTimerCB();
		count--;
		if (count < 0)
			return;
	}
}


long long  TimerMgr::StartTimer(long long& NextTick, std::function<void(Timer)> timerCB, void* data)
{
	std::shared_ptr<Timer> timer(new Timer());
	timer->mId = mTimerId++;
	timer->mTick = NextTick;
	timer->OnTimerPtr = timerCB;
	timer->data = data;
	timer->mStartTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	mTimerMutex.lock();
	mIDTimers.insert(std::pair<long long, std::shared_ptr<Timer>>(timer->mId, timer));
	mTickTimers.insert(std::pair<long long, std::shared_ptr<Timer>>(NextTick, timer));
	mTimerMutex.unlock();
	return timer->mId;
}

long long  TimerMgr::StartTimerMill(long long& ticks, std::function<void(Timer)> timerCB, void* data)
{
	std::shared_ptr<Timer> timer(new Timer());
	timer->mId = mTimerId++;
	timer->mStartTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	timer->mTick = timer->mStartTime+ticks;
	timer->OnTimerPtr = timerCB;
	timer->data = data;
	mTimerMutex.lock();
	mIDTimers.insert(std::pair<long long, std::shared_ptr<Timer>>(timer->mId, timer));
	mTickTimers.insert(std::pair<long long, std::shared_ptr<Timer>>(timer->mTick, timer));
	mTimerMutex.unlock();
	return timer->mId;
}

long long  TimerMgr::StartTimerSecond(long long& ticks, std::function<void(Timer)> timerCB, void* data)
{
	std::shared_ptr<Timer> timer(new Timer());
	timer->mId = mTimerId++;
	timer->mStartTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	timer->mTick = timer->mStartTime + ticks*1000;
	timer->OnTimerPtr = timerCB;
	timer->data = data;
	mTimerMutex.lock();
	mIDTimers.insert(std::pair<long long, std::shared_ptr<Timer>>(timer->mId, timer));
	mTickTimers.insert(std::pair<long long, std::shared_ptr<Timer>>(timer->mTick, timer));
	mTimerMutex.unlock();
	return timer->mId;
}

bool TimerMgr::ResetTimer(long long& timerId, long long& NextTick)
{
	//重置定时器
	long long startTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	mTimerMutex.lock();
	if (mIDTimers.find(timerId) != mIDTimers.end())
	{
		auto itr = mTickTimers.find(mIDTimers[timerId]->mTick);
		for (; itr != mTickTimers.end(); itr++)
		{
			if (itr->second->mId == timerId)
			{
				//重置定时器
				itr->second->mTick= NextTick;
				itr->second->mStartTime = startTime;
				mTickTimers.erase(itr);
				mTickTimers.insert(std::pair<long long, std::shared_ptr<Timer>>
					(mIDTimers[timerId]->mTick, mIDTimers[timerId]));
				mTimerMutex.unlock();
				return true;
			}
			if (itr->second->mTick != mIDTimers[timerId]->mTick)
			{
				mTimerMutex.unlock();
				return false;
			}
		}
	}
	mTimerMutex.unlock();
	return false;
}
bool TimerMgr::ResetTimerMill(long long& timerId, long long& ticks)
{
	//重置定时器
	long long startTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	mTimerMutex.lock();
	if (mIDTimers.find(timerId) != mIDTimers.end())
	{
		auto itr = mTickTimers.find(mIDTimers[timerId]->mTick);
		for (; itr != mTickTimers.end(); itr++)
		{
			if (itr->second->mId == timerId)
			{
				//重置定时器
				itr->second->mStartTime = startTime;
				itr->second->mTick = itr->second->mStartTime+ticks;
				mTickTimers.erase(itr);
				mTickTimers.insert(std::pair<long long, std::shared_ptr<Timer>>
					(mIDTimers[timerId]->mTick, mIDTimers[timerId]));
				mTimerMutex.unlock();
				return true;
			}
			if (itr->second->mTick != mIDTimers[timerId]->mTick)
			{
				mTimerMutex.unlock();
				return false;
			}
		}
	}
	mTimerMutex.unlock();
	return false;
}
bool TimerMgr::ResetTimerSecond(long long& timerId, long long& ticks)
{
	//重置定时器
	long long startTime = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::time_point<std::chrono::system_clock>::clock::now()).time_since_epoch().count();
	mTimerMutex.lock();
	if (mIDTimers.find(timerId) != mIDTimers.end())
	{
		auto itr = mTickTimers.find(mIDTimers[timerId]->mTick);
		for (; itr != mTickTimers.end(); itr++)
		{
			if (itr->second->mId == timerId)
			{
				//重置定时器
				itr->second->mStartTime = startTime;
				itr->second->mTick = itr->second->mStartTime+ticks*1000;
				mTickTimers.erase(itr);
				mTickTimers.insert(std::pair<long long, std::shared_ptr<Timer>>
					(mIDTimers[timerId]->mTick, mIDTimers[timerId]));
				mTimerMutex.unlock();
				return true;
			}
			if (itr->second->mTick != mIDTimers[timerId]->mTick)
			{
				mTimerMutex.unlock();
				return false;
			}
		}
	}
	mTimerMutex.unlock();
	return false;
}

bool TimerMgr::CancelTimer(long long& timerId)
{
	mTimerMutex.lock();
	if (mIDTimers.find(timerId) != mIDTimers.end())
	{
		auto itr = mTickTimers.find(mIDTimers[timerId]->mTick);
		for (; itr != mTickTimers.end(); itr++)
		{
			if (itr->second->mId == timerId)
			{
				mTickTimers.erase(itr);
				break;
			}
			if (itr->second->mTick != mIDTimers[timerId]->mTick)
			{
				mTimerMutex.unlock();
				return false;
			}
		}
		mIDTimers.erase(timerId);
		mTimerMutex.unlock();
		return true;
	}
	return false;
}