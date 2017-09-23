#pragma once
#include "Singleton.h"
#include "openvr.h"

namespace MFW3D
{
	namespace VR
	{
		class MFW3D_ViveVR:public MFW::Singleton<MFW3D_ViveVR>
		{
		public:
			void init();

		};
	}
}
