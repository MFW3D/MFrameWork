#include "Que_LogicHandler.h"

void Que_LogicHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//ע����Ϣ�ַ�

}
void Que_LogicHandler::Process()
{
	::Que_Handler::Process();
}