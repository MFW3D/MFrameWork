#include "stdafx.h"
#include "Scene_Mgr.h"

void Scene_Mgr::ResizeWindow(int width, int height)
{
	if (mWindow != nullptr)
	{
		mWindow->resize(width, height);
		mWindow->windowMovedOrResized();
		//windowResized(mWindow);
	}
}

