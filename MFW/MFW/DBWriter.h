#pragma once
#include "SQLDBEngine.h"

namespace DBWriteBack
{
	class DBWriter
	{
	private:
		static  DBProduce::SQLDBEngine* sqlEngine;
		static  std::mutex wbMsgsMutex;
		static  std::queue<DBProduce::DBMsg> wbMsgs;
	public:
		DBWriter();
		virtual ~DBWriter();
		static  void SetSQLEngine(DBProduce::SQLDBEngine* engine);
		static void pushWBMsg(DBProduce::DBMsg& wbMsg);
		static  bool popWBMsg(DBProduce::DBMsg& wbMsg);
		void Process();
	};

}
