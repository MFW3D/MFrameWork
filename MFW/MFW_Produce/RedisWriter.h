/************************************************************
 * FileName: DBWriteBack.h
 * Author: 毛自豪
 * Version : V0.1
 * Date: 2015年09月02日 17:12:28
 * Description: 数据回写部分的redis数据回写
 *
 ***********************************************************/
#pragma once
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include "DBMsg.h"
#include "RedisDBEngine.h"
namespace DBWriteBack
{
	
	class RedisWriter
	{
		private:
			static std::mutex wbMsgsMutex;
			static std::queue<DBProduce::DBMsg> wbMsgs;
			DBProduce::RedisDBEngine* redisEngine;
		public:
			/*初始化传入Redis引擎处理*/
			RedisWriter(DBProduce::RedisDBEngine* _redisEngine);
			virtual ~RedisWriter();
			/*将数据压入redis处理队列*/
			static void pushWBMsg(DBProduce::DBMsg wbMsg);
			/*取队列中的数据库操作进行处理*/
			 static bool popWBMsg(DBProduce::DBMsg& wbMsg);
			/*执行函数，执行队列中缓存的消息*/
			void Process();
	};

}
