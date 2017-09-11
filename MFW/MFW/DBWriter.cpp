#include "DBWriter.h"
#if !_WIN32
#include <unistd.h>  
#endif // !_WIN32

namespace DBWriteBack
{
	DBProduce::SQLDBEngine* DBWriter::sqlEngine;
	std::queue<DBProduce::DBMsg> DBWriter::wbMsgs;
	std::mutex DBWriter::wbMsgsMutex;
	DBWriter::DBWriter()
	{
	}
	DBWriter::~DBWriter()
	{

	}
	void DBWriter::SetSQLEngine(DBProduce::SQLDBEngine* engine)
	{
		sqlEngine = engine;
	}
	void DBWriter::pushWBMsg(DBProduce::DBMsg& wbMsg)
	{
		std::lock_guard < std::mutex > lg(wbMsgsMutex);
		DBWriter::wbMsgs.push(wbMsg);
	}
	bool DBWriter::popWBMsg(DBProduce::DBMsg& wbMsg)
	{
		std::lock_guard < std::mutex > lg(wbMsgsMutex);
		if (DBWriter::wbMsgs.size() == 0)
			return false;
		wbMsg = DBWriter::wbMsgs.front();
		DBWriter::wbMsgs.pop();
		return true;
	}
	void DBWriter::Process()
	{
		while (true)
		{
			DBProduce::DBMsg  wbMsg;
			if (DBWriter::popWBMsg(wbMsg))
			{
				sqlEngine->HandData(wbMsg);
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
