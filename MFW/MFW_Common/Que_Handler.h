#pragma once
#include <memory>
#include <mutex>
#include <Thread>
#include <unordered_map>
#include "Common_Base.pb.h"
#include "RedisQueue.h"
#include "NetTransMsg.h"

typedef std::function<void(std::string&)>  QueFunction;

class Que_Handler
{
private:
	std::string mData="";
	void OnRead(std::string data);
	std::queue<NetTransMsg> SendNetTransferMsgs;
public:
	std::unordered_map<int, QueFunction > HandleFunctions;
	std::shared_ptr<RedisQueue> mTQue;
	std::shared_ptr<RedisQueue> mFQue;

	virtual void Init(std::shared_ptr<RedisQueue>& tque, std::shared_ptr<RedisQueue>& fque);
	virtual void Process();
	//同意消息发送
	void SendData(int cmd, google::protobuf::Message* msg);
	void SendData(int cmd, std::string& msg);
};
