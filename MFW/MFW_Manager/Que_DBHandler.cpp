#include "Que_DBHandler.h"

void Que_DBHandler::Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque)
{
	::Que_Handler::Init(tque,fque);
	//ע����Ϣ�ַ�
}

void Que_DBHandler::Process()
{
	::Que_Handler::Process();
}