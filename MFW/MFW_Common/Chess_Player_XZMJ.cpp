#include "Chess_Player_XZMJ.h"

Chess_Player_XZMJ::Chess_Player_XZMJ(std::shared_ptr<Player>& player)
{
	mPlayer = player;
}
void Chess_Player_XZMJ::Init()
{

}

std::shared_ptr<Player> Chess_Player_XZMJ::GetPlayer()
{
	return mPlayer;
}
