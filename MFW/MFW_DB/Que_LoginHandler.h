#pragma once
#include <memory>
#include "RedisQueue.h"
#include "Que_Handler.h"
#include "Singleton.h"

class Que_LoginHandler:public Que_Handler,public MFW::Singleton<Que_LoginHandler>
{
private:
public:
	virtual void Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque);
	virtual void Process();

	void OnUserCheck(std::string& Data);
};
