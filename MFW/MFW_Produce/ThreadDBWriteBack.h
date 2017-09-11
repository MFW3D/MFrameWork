#pragma once
#include <thread>
#include <mutex>

class ThreadDBWriteBack 
{
public:
	//启动线程方法
	void Procces();
	void DBwriteBack();
	void RediswriteBack();
};
