#pragma once
#include "NNTCPServerMgr.h"
#include "Singleton.h"
#include "Net_Handler.h"

/*
������Ϣ�ַ�������
���ڣ����������յ���Ϣ�ַ�����Ӧ�Ĵ�����

*/
class Net_DBHandler :public MFW::Singleton<Net_DBHandler>, public NetClient_Handler
{
private:

public:
	Net_DBHandler();
	virtual void OnRead(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode);
	virtual void OnConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode);
	virtual void OnDisConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode);
	virtual void OnTimered(uv_timer_t* handle);

};