#include "MFW3D_Light.h"
namespace MFW3D
{
	MFW3D_Light::MFW3D_Light(Ogre::SceneManager* sceneManager)
	{
		mSceneManager = sceneManager;
		if (sceneManager == nullptr)
		{
			LOGI("sceneManager is nullptr");
			return;
		}
		mLight= mSceneManager->createLight("Light" + Ogre::StringConverter::toString(i));
	}
	MFW3D_Light::~MFW3D_Light()
	{

	}

}