#include "WriteBackMgr.h"
#include "RedisWriter.h"
#include "DBWriter.h"

namespace DBProduce
{
	
	WriteBackMgr::WriteBackMgr()
	{
	}
	
	WriteBackMgr::~WriteBackMgr()
	{
	}
	void WriteBackMgr::WriteBack(DBProduce::DBMsg& dbMsg)
	{
		DBWriteBack::RedisWriter::pushWBMsg(dbMsg);
		DBWriteBack::DBWriter::pushWBMsg(dbMsg);
	}

}
