#include "Scene_Mgr.h"
#include "Scene_Level1.h"
#include "Scene_Level2.h"
#include "Scene_Level3.h"

int main(int argc, char *argv[])
{
	Scene_Level1 ss;
	Scene_Mgr cc;
	Scene_Level2 ss2;
	Scene_Level3 ss3;
	//cc.go(&ss);
	cc.go(&ss2);
	return 0;
}