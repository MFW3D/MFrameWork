#include "Que_LogicHandler.h"

void Que_LogicHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//注册消息分发

}
void Que_LogicHandler::Process()
{
	::Que_Handler::Process();
}