#pragma once
#include "MFW3D_SceneBase.h"


class Scene_Level1 :public MFW3D::MFW3D_SceneBase
{
public:
	Ogre::SceneNode* mPivot;
	Scene_Level1();
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void setupContent();
};

