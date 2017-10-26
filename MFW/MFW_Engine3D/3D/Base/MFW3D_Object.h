#pragma once
#include "MFW3D_Geometry.h"
#include "../../Utility/MFWCommon_Global.h"
#include "MFW3D_Drawing.h"
namespace MFW3D
{
	//3D场景对象基类
	class MFW3D_Object
	{
	public:
		MFW3D_Point3D mPosition;		//对象位置
		bool mIsVisible = true;			//是否可见
		Ogre::SceneNode* mNode;			// 位置节点
	};
}