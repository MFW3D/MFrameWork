#pragma once
#include "../Base/MFW3D_Object.h"
#include "OgreRoot.h"
namespace MFW3D
{
	class MFW3D_Light:public MFW3D_Object
	{
	private:
		Ogre::Light* mLight;
		Ogre::SceneManager* mSceneManager;
	public:
		MFW3D_Light(Ogre::SceneManager* sceneManager);
		virtual ~MFW3D_Light();
		MFW3D_Colour mDiffuseColour;
		MFW3D_Colour mSpecularColour;


	};
}

