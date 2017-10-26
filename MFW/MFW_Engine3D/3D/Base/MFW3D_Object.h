#pragma once
#include "MFW3D_Geometry.h"
#include "../../Utility/MFWCommon_Global.h"
#include "MFW3D_Drawing.h"
namespace MFW3D
{
	//3D�����������
	class MFW3D_Object
	{
	public:
		MFW3D_Point3D mPosition;		//����λ��
		bool mIsVisible = true;			//�Ƿ�ɼ�
		Ogre::SceneNode* mNode;			// λ�ýڵ�
	};
}