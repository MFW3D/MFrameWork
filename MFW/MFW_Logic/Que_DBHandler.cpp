#include "Que_DBHandler.h"

void Que_DBHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//注册消息分发
}

void Que_DBHandler::Process()
{
	::Que_Handler::Process();
}