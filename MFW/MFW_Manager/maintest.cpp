//#include "HttpMgr.h"
//#if _WIN32
//#include <windows.h>
//#else
//#include "unistd.h"
//#endif
//HttpMgr httpMgr;
//#include <map>
//#include <vector>
//
//void OnRead(std::shared_ptr<NNTCPLinkNode> session, HttpResPonse& data, NNTCPNode& netNode)
//{
//	std::cout << "recieved :" << data.GetStatus() << std::endl;
//	std::cout << "recieved :" << data.GetBody() << std::endl;
//}
//void OnConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
//{
//	std::cout << "Client Connected " << std::endl;
//	std::map<std::string, std::string> params;
//	httpMgr.SendDataClient(session, "dasdasdas", netNode, params, "/dsadasda/dasdasd");
//}
//void OnDisConnected(std::shared_ptr<NNTCPLinkNode> session, NNTCPNode& netNode)
//{
//	std::cout << "Client DisConnected " << std::endl;
//}
//
//std::vector<std::shared_ptr<std::thread>> threads;
//int main()
//{
//
//	threads.push_back(std::shared_ptr<std::thread>(new std::thread([&]() {
//		std::vector<HttpStartInfo> ports;
//		HttpStartInfo httpStartInfo;
//		httpStartInfo.mIp = "127.0.0.1";
//		httpStartInfo.mIsClient = true;
//		httpStartInfo.mPort = 5555;
//		ports.push_back(httpStartInfo);
//		httpMgr.OnConnectedPtr = OnConnected;
//		httpMgr.OnDisConnectedPtr = OnDisConnected;
//		httpMgr.OnReadClientPtr = OnRead;
//		httpMgr.Start(ports);
//	})));
//
//	while (true)
//	{
//#if _WIN32
//		Sleep(10);
//#else
//		usleep(10000);
//#endif
//	}
//	return 0;
//	}
