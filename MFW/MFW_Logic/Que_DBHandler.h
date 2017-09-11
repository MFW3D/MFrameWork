#pragma once
#include "Que_Handler.h"
#include "Singleton.h"

class Que_DBHandler:public Que_Handler,public MFW::Singleton<Que_DBHandler>
{
public:
	virtual void Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque) ;
	virtual void Process() ;

};
