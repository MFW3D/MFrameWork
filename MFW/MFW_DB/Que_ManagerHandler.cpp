#include "Que_ManagerHandler.h"

void Que_ManagerHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//注册消息分发

}
void Que_ManagerHandler::Process()
{
	::Que_Handler::Process();
}