#pragma once

#include "Singleton.h"
#include "NNTCPServerMgr.h"

namespace MFW3D
{
	namespace Net
	{
		class MFW3D_NetMgr :public MFW::Singleton<MFW3D_NetMgr>
		{
		private:
			NNTCPServerMgr mNNTCPServerMgr;
			std::shared_ptr<std::thread> mNetMDBThread;
		public:
			void StartNet();
		};
	}
}
