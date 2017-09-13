#pragma once

#include "MFW3D_SceneMgr.h"


class Scene_Mgr :public MFW3D::MFW3D_SceneMgr
{
public: 
	void ResizeWindow(int width, int height);
};
