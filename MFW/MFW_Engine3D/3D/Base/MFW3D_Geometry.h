#pragma once
#include <List>
#include "OgreRoot.h"

namespace MFW3D
{
	class MFW3D_Point3D
	{
	public:
		Ogre::Vector3 Value;
	};

	class MFW3D_Line3D
	{
	public:
		std::list<MFW3D_Point3D> Points;
		double GetLength();
	};
}
