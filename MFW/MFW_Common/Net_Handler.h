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
��������TCP������Ϣ����ĸ���
ʵ����Ϊ��������ͻ��˵�������Ϣ����
ʵ�ֿ��̵߳���Ϣ����
*/


/*tcp������Ϣ������*/
class Net_Handler
{
private:
	//�������������
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

//��Ϊ�ͻ��˵���Ϣ����
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

//��Ϊ����������Ϣ����
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
