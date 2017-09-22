#include "NNTCPServerMgr.h"
#include <iostream>

#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h> 


#define MAC_SIZE    18  
#define IP_SIZE     16  


void NNTCPNode::SendData(std::shared_ptr<NNTCPLinkNode> session, std::string data)
{
	write_req_t* wr = (write_req_t*)malloc(sizeof *wr);
	uv_buf_t buf = uv_buf_init((char*)data.data(), data.size());
	wr->buf = uv_buf_init(buf.base, data.size());
	//session->session->data = (void*)&nNNodeInfo;
	uv_write(&wr->req, session->session, &wr->buf, 1, NNTCPServerMgr::WriteCb);
}
bool NNTCPNode::CloseSession(std::shared_ptr<NNTCPLinkNode> session)
{
	uv_close((uv_handle_t*)session->session, NNTCPServerMgr::CloseCb);
	return true;
}
void NNTCPNode::StopTimer()
{
	uv_timer_stop(&timerHandle);
}
void NNTCPNode::ReadCb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
}
void NNTCPNode::CloseCb(uv_handle_t* handle)
{

}
void NNTCPNode::ConnectCb(uv_loop_t* loop, uv_stream_t *server, int status)
{

}

void NNTCPNode::WriteCb(uv_write_t* req, int status)
{

}
void NNTCPNode::TimerCb(uv_timer_t* handle)
{
	if (timerCB != nullptr)
	{
		timerCB(handle);
	}
}

void NNTCPServer::ConnectCb(uv_loop_t* loop, uv_stream_t *server, int status)
{
	if (status < 0) {
		return;
	}
	uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);
	if (uv_accept(server, (uv_stream_t*)client) == 0) {
		client->data = server->data;
		uv_read_start((uv_stream_t*)client, NNTCPServerMgr::AllocBuffer, NNTCPServerMgr::ReadCb);

		//客户端连接进入
		unsigned long ip;
		int port;
		NetUtility::GetIpPort(client, ip, port);
		unsigned long long id = NetUtility::CombineInt32(ip, port);

		std::shared_ptr<NNTCPLinkNode > NNTCPClientNodePtr(new NNTCPLinkNode());
		if (Clients.find(id) != Clients.end())
		{
			NNTCPClientNodePtr->mId = id;
			NNTCPClientNodePtr->mIP = ip;
			NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
			NNTCPClientNodePtr->mPort = port;
			NNTCPClientNodePtr->session = (uv_stream_t*)client;
			Clients.insert(std::pair<unsigned long long, std::shared_ptr<NNTCPLinkNode>>(id, NNTCPClientNodePtr));
		}
		else
		{
			NNTCPClientNodePtr->mId = id;
			NNTCPClientNodePtr->mIP = ip;
			NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
			NNTCPClientNodePtr->mPort = port;
			NNTCPClientNodePtr->session = (uv_stream_t*)client;
			Clients[id] = NNTCPClientNodePtr;
		}
		if (OnConnected != nullptr)
		{
			OnConnected(NNTCPClientNodePtr, *this);
		}
	}
	else {
		uv_close((uv_handle_t*)client, NULL);
	}
}
void NNTCPServer::CloseCb(uv_handle_t* handle)
{
	unsigned long ip;
	int port;
	NetUtility::GetIpPort((uv_tcp_t*)handle, ip, port);
	unsigned long long id = NetUtility::CombineInt32(ip, port);
	std::shared_ptr<NNTCPLinkNode > NNTCPClientNodePtr(new NNTCPLinkNode());
	if (Clients.find(id) != Clients.end())
	{
		NNTCPClientNodePtr->mId = id;
		NNTCPClientNodePtr->mIP = ip;
		NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
		NNTCPClientNodePtr->mPort = port;
		NNTCPClientNodePtr->session = (uv_stream_t*)handle;
		//删除单元
		Clients.erase(id);
		if (OnDisConnected != nullptr)
		{
			OnDisConnected(NNTCPClientNodePtr, *this);
		}
	}

}
void NNTCPServer::ReadCb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	unsigned long ip;
	int port;
	NetUtility::GetIpPort((uv_tcp_t*)client, ip, port);
	unsigned long long id = NetUtility::CombineInt32(ip, port);
	if (nread == UV_EOF || nread == UV_ECONNRESET) {
		std::shared_ptr<NNTCPLinkNode > NNTCPClientNodePtr(new NNTCPLinkNode());
		if (Clients.find(id) != Clients.end())
		{
			NNTCPClientNodePtr->mId = id;
			NNTCPClientNodePtr->mIP = ip;
			NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
			NNTCPClientNodePtr->mPort = port;
			NNTCPClientNodePtr->session = (uv_stream_t*)client;
			//删除单元
			Clients.erase(id);
		}
		else
		{
			NNTCPClientNodePtr->mId = id;
			NNTCPClientNodePtr->mIP = ip;
			NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
			NNTCPClientNodePtr->mPort = port;
			NNTCPClientNodePtr->session = (uv_stream_t*)client;
		}
		if (OnDisConnected != nullptr)
		{
			OnDisConnected(NNTCPClientNodePtr, *this);
		}
		return;
	}
	buf->base[nread] = '\0';
	std::string recivedata(buf->base, nread);
	if (OnRead != nullptr)
	{
		std::shared_ptr<NNTCPLinkNode > NNTCPClientNodePtr(new NNTCPLinkNode());
		if (Clients.find(id) != Clients.end())
		{
			NNTCPClientNodePtr->mId = id;
			NNTCPClientNodePtr->mIP = ip;
			NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
			NNTCPClientNodePtr->mPort = port;
			NNTCPClientNodePtr->session = (uv_stream_t*)client;
			Clients.insert(std::pair<unsigned long long, std::shared_ptr<NNTCPLinkNode>>(id, NNTCPClientNodePtr));
		}
		else
		{
			NNTCPClientNodePtr->mId = id;
			NNTCPClientNodePtr->mIP = ip;
			NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
			NNTCPClientNodePtr->mPort = port;
			NNTCPClientNodePtr->session = (uv_stream_t*)client;
			Clients[id] = NNTCPClientNodePtr;
		}
		OnRead(NNTCPClientNodePtr, recivedata, *this);
	}
}

NNTCPClient::NNTCPClient()
{
	NNTCPClientNodePtr = std::shared_ptr<NNTCPLinkNode>(new NNTCPLinkNode());
}
void NNTCPClient::ConnectCbClient(uv_loop_t* loop, uv_connect_t* conn_req, int status)
{
	unsigned long ip;
	int port;
	NetUtility::GetIpPort(&server, ip, port);
	unsigned long long id = NetUtility::CombineInt32(ip, port);
	NNTCPClientNodePtr->mId = id;
	NNTCPClientNodePtr->mIP = ip;
	NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
	NNTCPClientNodePtr->mPort = port;
	NNTCPClientNodePtr->session = (uv_stream_t*)&server;
	if (status < 0) {
		if (OnFailConnected != nullptr)
			OnFailConnected(NNTCPClientNodePtr, *this);
		return;
	}
	int r = uv_read_start((uv_stream_t*)&server, NNTCPServerMgr::AllocBuffer, NNTCPServerMgr::ReadCb);
	
	if (OnConnected != nullptr)
		OnConnected(NNTCPClientNodePtr, *this);
}
void NNTCPClient::CloseCb(uv_handle_t* handle)
{
	unsigned long ip;
	int port;
	NetUtility::GetIpPort((uv_tcp_t*)handle, ip, port);
	unsigned long long id = NetUtility::CombineInt32(ip, port);
	NNTCPClientNodePtr->mId = id;
	NNTCPClientNodePtr->mIP = ip;
	NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
	NNTCPClientNodePtr->mPort = port;
	NNTCPClientNodePtr->session = (uv_stream_t*)handle;
	if (OnDisConnected != nullptr)
	{
		OnDisConnected(NNTCPClientNodePtr, *this);
	}
}
void NNTCPClient::ReadCb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
	unsigned long ip;
	int port;
	NetUtility::GetIpPort((uv_tcp_t*)client, ip, port);
	unsigned long long id = NetUtility::CombineInt32(ip, port);
	NNTCPClientNodePtr->mId = id;
	NNTCPClientNodePtr->mIP = ip;
	NNTCPClientNodePtr->mIPStr = NetUtility::inttoip(ip);
	NNTCPClientNodePtr->mPort = port;
	NNTCPClientNodePtr->session = (uv_stream_t*)client;
	if (nread == UV_EOF || nread == UV_ECONNRESET) {
		if (OnDisConnected != nullptr)
		{
			OnDisConnected(NNTCPClientNodePtr, *this);
		}
		uv_close((uv_handle_t*)client, NNTCPServerMgr::CloseCb);
		return;
	}
	buf->base[nread] = '\0';
	std::string recivedata(buf->base, nread);
	if (OnRead != nullptr)
	{
		OnRead(NNTCPClientNodePtr, recivedata, *this);
	}
}

// 根据域名获取ip  
std::string  get_ip_by_domain(const char *domain)
{
	hostent *phst = gethostbyname(domain);
	in_addr * iddr = (in_addr*)phst->h_addr;
	unsigned long IPUL = iddr->s_addr;
	return std::string( inet_ntoa(*iddr));
}

std::map<int, std::shared_ptr<NNTCPServer>> NNTCPServerMgr::mNetServers;
std::map<unsigned long long, std::shared_ptr<NNTCPClient>> NNTCPServerMgr::mNetClients;
std::vector<uv_loop_t*> NNTCPServerMgr::loops;
unsigned long long NNTCPServerMgr::mClientId=1;
void NNTCPServerMgr::AllocBuffer(uv_handle_t *h, size_t size, uv_buf_t *buf) {
	size = DEFAULT_BACKLOG;
	buf->base = (char*)malloc(size);
	buf->len = size;
}
void NNTCPServerMgr::ReadCb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
	NNNodeInfo node = *(NNNodeInfo*)client->data;
	if (!node.IsClient)
	{
		std::shared_ptr<NNTCPServer> netNodePtr;
		if (mNetServers.find(node.Port) != mNetServers.end())
		{
			netNodePtr = mNetServers[node.Port];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->ReadCb(client, nread, buf);
	}
	else
	{
		std::shared_ptr<NNTCPClient> netNodePtr;
		if (mNetClients.find(node.ClientId) != mNetClients.end())
		{
			netNodePtr = mNetClients[node.ClientId];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->ReadCb(client, nread, buf);
	}
}
void NNTCPServerMgr::CloseCb(uv_handle_t* handle)
{
	NNNodeInfo node = *(NNNodeInfo*)handle->data;
	if (!node.IsClient)
	{
		std::shared_ptr<NNTCPServer> netNodePtr;
		if (mNetServers.find(node.Port) != mNetServers.end())
		{
			netNodePtr = mNetServers[node.Port];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->CloseCb(handle);
	}
	else
	{
		std::shared_ptr<NNTCPClient> netNodePtr;
		if (mNetClients.find(node.ClientId) != mNetClients.end())
		{
			netNodePtr = mNetClients[node.ClientId];
			mNetClients.erase(node.ClientId);
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->CloseCb(handle);
	}
}
void NNTCPServerMgr::TimerCb(uv_timer_t* handle) {
	NNNodeInfo node = *(NNNodeInfo*)handle->data;
	if (!node.IsClient)
	{
		std::shared_ptr<NNTCPServer> netNodePtr;
		if (mNetServers.find(node.Port) != mNetServers.end())
		{
			netNodePtr = mNetServers[node.Port];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->TimerCb(handle);
	}
	else
	{
		std::shared_ptr<NNTCPClient> netNodePtr;
		if (mNetClients.find(node.ClientId) != mNetClients.end())
		{
			netNodePtr = mNetClients[node.ClientId];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->TimerCb(handle);
	}

}
void NNTCPServerMgr::ConnectCb(uv_stream_t *server, int status) {
	std::shared_ptr<NNTCPServer> netNodePtr;
	NNNodeInfo node = *(NNNodeInfo*)server->data;
	if (!node.IsClient)
	{
		if (mNetServers.find(node.Port) != mNetServers.end())
		{
			netNodePtr = mNetServers[node.Port];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->ConnectCb(server->loop, server, status);
	}
}
void NNTCPServerMgr::ConnectCbClient(uv_connect_t* conn_req, int status) {
	NNNodeInfo node = *(NNNodeInfo*)conn_req->data;
	if (node.IsClient)
	{
		std::shared_ptr<NNTCPClient> netNodePtr;
		if (mNetClients.find(node.ClientId) != mNetClients.end())
		{
			netNodePtr = mNetClients[node.ClientId];
		}
		if (netNodePtr == nullptr)
			return;
		netNodePtr->ConnectCbClient(conn_req->handle->loop, conn_req, status);
	}
}
void NNTCPServerMgr::WriteCb(uv_write_t* client, int status) {
	NNNodeInfo node = *(NNNodeInfo*)client->handle->data;
	std::shared_ptr<NNTCPServer> netNodePtr;
	if (mNetServers.find(node.Port) != mNetServers.end())
	{
		netNodePtr = mNetServers[node.Port];
	}
	if (netNodePtr == nullptr)
		return;
	netNodePtr->WriteCb(client, status);
}
bool NNTCPServerMgr::RunServer(std::vector<NNNodeInfo>NNServerInfos)
{
	uv_loop_t* loop;
	loops.push_back(loop);
	loop = uv_loop_new();
	int r;
	for (int i = 0; i < NNServerInfos.size(); i++)
	{
		if (!NNServerInfos[i].IsClient)
		{
			std::shared_ptr<NNTCPServer> NetSessionPtr(new NNTCPServer());
			NetSessionPtr->OnConnected = NNServerInfos[i].OnConnected;
			NetSessionPtr->OnDisConnected = NNServerInfos[i].OnDisConnected;
			NetSessionPtr->OnFailConnected = NNServerInfos[i].OnFailConnected;
			NetSessionPtr->OnRead = NNServerInfos[i].OnRead;
			NetSessionPtr->nNNodeInfo = NNServerInfos[i];
			if (mNetServers.find(NNServerInfos[i].Port) != mNetServers.end())
			{
				continue;
			}
			struct sockaddr_in addr;

			assert(0 == uv_ip4_addr(NNServerInfos[i].Ip.c_str(), NNServerInfos[i].Port, &addr));
			r = uv_tcp_init(loop, &NetSessionPtr->server);
			assert(r == 0);

			r = uv_tcp_bind(&NetSessionPtr->server, (const struct sockaddr*)&addr, 0);

			assert(r == 0);
			r = uv_listen((uv_stream_t*)&NetSessionPtr->server, DEFAULT_BACKLOG, NNTCPServerMgr::ConnectCb);
			if (r) {
				return 1;
			}
			NetSessionPtr->server.data = (void*)&NetSessionPtr->nNNodeInfo;
			NetSessionPtr->port = NNServerInfos[i].Port;
			NetSessionPtr->timerHandle.data = (void*)&NNServerInfos[i];
			r = uv_timer_init(loop, &NetSessionPtr->timerHandle);
			if (NNServerInfos[i].OnTimered != nullptr) {
				NetSessionPtr->timerCB = NNServerInfos[i].OnTimered;
			}
			r = uv_timer_start(&NetSessionPtr->timerHandle, NNTCPServerMgr::TimerCb, 1, 1);
			mNetServers.insert(std::pair<int, std::shared_ptr<NNTCPServer>>(NNServerInfos[i].Port, NetSessionPtr));
		}
		else
		{
			std::shared_ptr<NNTCPClient> NetSessionPtr(new NNTCPClient());
			NetSessionPtr->OnConnected = NNServerInfos[i].OnConnected;
			NetSessionPtr->OnDisConnected = NNServerInfos[i].OnDisConnected;
			NetSessionPtr->OnFailConnected = NNServerInfos[i].OnFailConnected;
			NetSessionPtr->OnRead = NNServerInfos[i].OnRead;
			NetSessionPtr->nNNodeInfo = NNServerInfos[i];
			if (mNetClients.find(NNServerInfos[i].ClientId) != mNetClients.end())
			{
				continue;
			}
			struct sockaddr_in addr;

			assert(0 == uv_ip4_addr(NNServerInfos[i].Ip.c_str(), NNServerInfos[i].Port, &addr));
			r = uv_tcp_init(loop, &NetSessionPtr->server);
			assert(r == 0);

			r = uv_tcp_connect(&NetSessionPtr->con, &NetSessionPtr->server,
				(const struct sockaddr*)&addr, NNTCPServerMgr::ConnectCbClient);
			assert(r == 0);

			NetSessionPtr->server.data = (void*)&NetSessionPtr->nNNodeInfo;
			NetSessionPtr->con.data = (void*)&NetSessionPtr->nNNodeInfo;
			NetSessionPtr->port = NNServerInfos[i].Port;

			r = uv_timer_init(loop, &NetSessionPtr->timerHandle);
			NetSessionPtr->timerHandle.data = (void*)&NNServerInfos[i];
			if (NNServerInfos[i].OnTimered != nullptr) {
				NetSessionPtr->timerCB = NNServerInfos[i].OnTimered;
			}
			r = uv_timer_start(&NetSessionPtr->timerHandle, NNTCPServerMgr::TimerCb, 1, 1);

			mNetClients.insert(std::pair<unsigned long long,
				std::shared_ptr<NNTCPClient>>(NNServerInfos[i].ClientId, NetSessionPtr));

		}
	}

	return uv_run(loop, UV_RUN_DEFAULT);
}
bool NNTCPServerMgr::RunServer(NNNodeInfo nNServerInfo)
{
	uv_loop_t* loop;
	loops.push_back(loop);
	loop = uv_loop_new();
	int r;
	std::shared_ptr<NNTCPClient> NetSessionPtr(new NNTCPClient());
	NetSessionPtr->nNNodeInfo = nNServerInfo;
	r = uv_timer_init(loop, &NetSessionPtr->timerHandle);
	NetSessionPtr->timerHandle.data = (void*)&nNServerInfo;
	if (nNServerInfo.OnTimered != nullptr) {
		NetSessionPtr->timerCB = nNServerInfo.OnTimered;
	}
	r = uv_timer_start(&NetSessionPtr->timerHandle, NNTCPServerMgr::TimerCb, 1, 1);
	mNetClients.insert(std::pair<unsigned long long, std::shared_ptr<NNTCPClient>>(nNServerInfo.ClientId, NetSessionPtr));
	return uv_run(loop, UV_RUN_DEFAULT);
}
unsigned long long  NNTCPServerMgr::AddServer(uv_loop_t* loop, NNNodeInfo nNServerInfo)
{
	nNServerInfo.ClientId = mClientId++;
	int r;
	std::shared_ptr<NNTCPClient> NetSessionPtr(new NNTCPClient());
	NetSessionPtr->OnConnected = nNServerInfo.OnConnected;
	NetSessionPtr->OnDisConnected = nNServerInfo.OnDisConnected;
	NetSessionPtr->OnFailConnected = nNServerInfo.OnFailConnected;
	NetSessionPtr->OnRead = nNServerInfo.OnRead;
	NetSessionPtr->nNNodeInfo = nNServerInfo;
	if (mNetClients.find(nNServerInfo.ClientId) != mNetClients.end())
	{
		return -1;
	}
	struct sockaddr_in addr;
	if (0 != uv_ip4_addr(get_ip_by_domain(nNServerInfo.Ip.c_str()).c_str(), nNServerInfo.Port, &addr))
		return -1;
	r = uv_tcp_init(loop, &NetSessionPtr->server);
	if (r != 0)
		return -1;
	r = uv_tcp_connect(&NetSessionPtr->con, &NetSessionPtr->server, 
		(const struct sockaddr*)&addr, NNTCPServerMgr::ConnectCbClient);
	if (r != 0)
		return -1;
	NetSessionPtr->server.data = (void*)&NetSessionPtr->nNNodeInfo;
	NetSessionPtr->con.data = (void*)&NetSessionPtr->nNNodeInfo;
	NetSessionPtr->port = nNServerInfo.Port;

	mNetClients.insert(std::pair<unsigned long long, std::shared_ptr<NNTCPClient>>(nNServerInfo.ClientId, NetSessionPtr));
	return nNServerInfo.ClientId;
}


