#include "MFW3D_SceneMgr.h"
#include "Scene_Level1.h"
#include "Scene_Level2.h"
#include "Scene_Level3.h"
#include "NetUtility.h"

int main(int argc, char *argv[])
{
	Scene_Level1 ss;
	Scene_Level2 ss2;
	Scene_Level3 ss3;
	//cc.go(&ss);
	MFW3D::MFW3D_SceneMgr::GetInstance()->go(&ss2);
	return 0;
}