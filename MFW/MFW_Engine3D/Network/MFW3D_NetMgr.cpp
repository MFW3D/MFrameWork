#include "MFW3D_NetMgr.h"
#include "ServerGlobal.h"
#include "MFW3D_NetHandler.h"
namespace MFW3D
{
	namespace Net
	{
		void MFW3D_NetMgr::StartNet()
		{
			mNetMDBThread = std::shared_ptr<std::thread>(new std::thread([&]() {
				std::vector<NNNodeInfo> NNNodeInfos;
				NNNodeInfo NNNodeInfo_Login;
#if _WIN32
				NNNodeInfo_Login.Ip = ServerCfg::GetInstance()->Logic_Port2Client;
#else
				NNNodeInfo_Client.Ip = ServerCfg::GetInstance()->Logic_Port2Client;
#endif
				NNNodeInfo_Login.Port = ServerCfg::GetInstance()->Login_Port2Client;
				NNNodeInfo_Login.IsClient = false;
				NNNodeInfo_Login.OnConnected = std::bind(&MFW3D_NetHandler::OnConnected, MFW3D_NetHandler::GetInstance(),
					std::placeholders::_1, std::placeholders::_2);
				NNNodeInfo_Login.OnDisConnected = std::bind(&MFW3D_NetHandler::OnDisConnected, MFW3D_NetHandler::GetInstance(),
					std::placeholders::_1, std::placeholders::_2);
				NNNodeInfo_Login.OnRead = std::bind(&MFW3D_NetHandler::OnRead, MFW3D_NetHandler::GetInstance(),
					std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
				NNNodeInfo_Login.OnTimered = std::bind(&MFW3D_NetHandler::OnTimered, MFW3D_NetHandler::GetInstance(),
					std::placeholders::_1);
				NNNodeInfos.push_back(NNNodeInfo_Login);
				mNNTCPServerMgr.RunServer(NNNodeInfos);
			}));
		}
	}
}