#pragma once
#include "NNTCPServerMgr.h"
#include <queue>
#include <string>
#include <mutex>
#include <thread>
#include "Common_Base.pb.h"
#include <google/protobuf/stubs/common.h>
#include <unordered_map>
#include <functional>
#include "NetTransMsg.h"
typedef std::function<void(std::shared_ptr<NNTCPLinkNode> &, const int&, std::string&, NNTCPNode&)>  HandleBackFunction;

/*
对于所有TCP网络消息处理的父类
实现作为服务器或客户端的网络消息处理
实现跨线程的消息传递
*/


/*tcp网络消息处理父类*/
class Net_Handler
{
private:
	//网络待发送数据
	std::queue<NetTransMsg> SendNetTransferMsgs;
	std::mutex SendNetTransferMsgsMutex;
public:
	std::unordered_map<int, HandleBackFunction > HandleFunctions;
	void PushSendMsg(NetTransMsg& netTransferMsg);
	bool PopSendMsg(NetTransMsg& netTransferMsg);
	virtual void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	virtual void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode) = 0;
	virtual void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode) = 0;
	virtual void OnTimered(uv_timer_t* handle) = 0;
	void SendData(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cmd, google::protobuf::Message* msg);
	void SendData(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cmd, std::string& msg);
};

//作为客户端的消息处理
class NetClient_Handler :public Net_Handler
{
private:
	NNTCPNode* mServerNetNode;
	std::shared_ptr<NNTCPLinkNode> mServerSession;
public:
	virtual void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	virtual void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	virtual void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	virtual void OnTimered(uv_timer_t* handle);
};

//作为服务器的消息处理
class NetServer_Handler :public Net_Handler
{
private:
	NNTCPServer* mServerNetNode;
public:
	virtual void OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	virtual void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	virtual void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	virtual void OnTimered(uv_timer_t* handle);
};
