//#pragma once
//#include "Singleton.h"
//#include "HttpMgr.h"
//#include "Net_Handler.h"
//#include <vector>
//class Net_ClientHandler :public Singleton<Net_ClientHandler>
//{
//private:
//	HttpMgr httpMgr;
//	void init();
//	bool isinit = false;
//	
//public:
//	void OnRead(std::shared_ptr<NNTCPLinkNode>  session, HttpRequest& httpRequest, NNTCPNode& netNode);
//	void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
//	void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
//	void OnTime();
//
//
//	void HandleLogin(std::shared_ptr<NNTCPLinkNode> & session, int& cmd, std::string& data, NNTCPNode& netNode);
//	void HandleRegister(std::shared_ptr<NNTCPLinkNode>&  session, int& cmd, std::string& data, NNTCPNode& netNode);
//};