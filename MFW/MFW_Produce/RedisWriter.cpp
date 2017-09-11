#include "RedisWriter.h"
#if _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace DBWriteBack
{
	std::queue<DBProduce::DBMsg> RedisWriter::wbMsgs;
	std::mutex RedisWriter::wbMsgsMutex;
	RedisWriter::RedisWriter(DBProduce::RedisDBEngine* _redisEngine)
	{
		redisEngine = _redisEngine;
	}

	RedisWriter::~RedisWriter()
	{
	}
	void RedisWriter::pushWBMsg(DBProduce::DBMsg wbMsg)
	{
		std::lock_guard < std::mutex > lg(wbMsgsMutex);
		RedisWriter::wbMsgs.push(wbMsg);
	}
	bool RedisWriter::popWBMsg(DBProduce::DBMsg& wbMsg)
	{
		std::lock_guard < std::mutex > lg(wbMsgsMutex);
		if (RedisWriter::wbMsgs.size() == 0)
			return false;
		wbMsg=RedisWriter::wbMsgs.front();
		RedisWriter::wbMsgs.pop();
		return true;
	}
	void RedisWriter::Process()
	{
		while (true)
		{
			DBProduce::DBMsg  wbMsg;
			if (RedisWriter::popWBMsg(wbMsg))
			{
				redisEngine->HandData(wbMsg);
#if _WIN32
				Sleep(100);
#else
				sleep(1);
#endif
			}
			else
			{
				break;
			}
		}
	}

}
