#pragma once
#include "Singleton.h"
#include "NNTCPServerMgr.h"
#include "Net_Handler.h"
#include "Login_Client.pb.h"

/*
网络消息分发处理类
用于：服务器接收的消息分发至对应的处理类

*/
class MFW3D_NetHandler :public MFW::Singleton<MFW3D_NetHandler>, public NetServer_Handler
{
private:
public:
	MFW3D_NetHandler();
	virtual void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	virtual void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	virtual void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	virtual void OnTimered(uv_timer_t* handle);

	void HandleLogin(std::shared_ptr<NNTCPLinkNode> & session, const int& cmd, std::string& data, NNTCPNode& netNode);
	void HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, const int& cmd, std::string& data, NNTCPNode& netNode);

};