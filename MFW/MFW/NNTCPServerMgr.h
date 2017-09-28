#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "uv.h"
#include <memory>
#include <thread>
#include <functional>
#include <map>
#include <mutex>
#include <vector>
#include <queue>

#include "NetUtility.h"

class NNMsg;
class NNNodeInfo;
class NNTCPNode;

#define DEFAULT_BACKLOG 1024

typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;


/*节点的客户端信息*/
class NNTCPLinkNode
{
public:
	//客户端的唯一ID,由连接地址和端口决定
	unsigned long long mId = 0;
	std::string mIPStr = "0.0.0.0";
	unsigned long mIP = 0;
	int mPort = 0;
	//TCP连接信息
	uv_stream_t * session;
};


/*服务器启动信息结构*/
class  NNNodeInfo
{
public:
	std::string Ip = "0.0.0.0";
	int Port = 0;
	bool IsClient = true;
	unsigned long long ClientId=0;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode)> OnRead;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)> OnConnected = nullptr;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)> OnDisConnected = nullptr;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)> OnFailConnected = nullptr;
	std::function<void(uv_timer_t* handle) > OnTimered = nullptr;
};
/*单个网络结构，保存开的服务器信息*/
class NNTCPNode
{
public:
	int CloseTick = 100;
	int port = 0;
	uv_tcp_t server;
	uv_timer_t timerHandle;
	NNNodeInfo nNNodeInfo;
	std::function<void(uv_timer_t* handle) > timerCB;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, std::string data, NNTCPNode& netNode)> OnRead;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)> OnConnected;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)> OnDisConnected;
	std::function<void(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)> OnFailConnected;
	void  SendData(std::shared_ptr<NNTCPLinkNode> session, std::string data);
	bool CloseSession(std::shared_ptr<NNTCPLinkNode> session);
	void StopTimer();
	virtual void ReadCb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
	virtual void CloseCb(uv_handle_t* handle);
	virtual void ConnectCb(uv_loop_t* loop, uv_stream_t *server, int status);
	void WriteCb(uv_write_t* req, int status);
	void TimerCb(uv_timer_t* handle);
};


class NNTCPServer:public NNTCPNode
{
public:
	std::map<unsigned long long,std::shared_ptr<NNTCPLinkNode>> Clients;
	virtual void CloseCb(uv_handle_t* handle);
	virtual void ConnectCb(uv_loop_t* loop, uv_stream_t *server, int status);
	virtual void ReadCb(uv_stream_t * client, ssize_t nread, const uv_buf_t *buf);
};

class NNTCPClient :public NNTCPNode
{
public:
	NNTCPClient();
	std::shared_ptr<NNTCPLinkNode> NNTCPClientNodePtr;
	std::string Ip = "0.0.0.0";
	uv_connect_t con;
	void ConnectCbClient(uv_loop_t* loop, uv_connect_t* conn_req, int status);
	virtual void CloseCb(uv_handle_t* handle);
	virtual void ReadCb(uv_stream_t * client, ssize_t nread, const uv_buf_t *buf);
};
/*网络启动管理器*/
class NNTCPServerMgr
{
private:
	static std::vector<uv_loop_t*> loops;
	static unsigned long long mClientId;

	//自己作为服务器的网络结构
	static std::map<int, std::shared_ptr<NNTCPServer>> mNetServers;
	//自己作为客户端的网络结构
	static std::map<unsigned long long, std::shared_ptr<NNTCPClient>> mNetClients;
public:
	static bool RunServer(std::vector<NNNodeInfo> NNServerInfos);
	static bool RunServer(NNNodeInfo nNServerInfo);
	static unsigned long long  AddServer(uv_loop_t* loop, NNNodeInfo nNServerInfo);

	static void AllocBuffer(uv_handle_t *h, size_t size, uv_buf_t *buf);
	static void ReadCb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
	static void CloseCb(uv_handle_t* handle);
	static void ConnectCb(uv_stream_t *server, int status);
	static void WriteCb(uv_write_t* client, int status);
	static void TimerCb(uv_timer_t* handle);
	static void ConnectCbClient(uv_connect_t* conn_req, int status);
};

