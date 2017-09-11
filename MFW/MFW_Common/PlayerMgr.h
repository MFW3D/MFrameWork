#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "Singleton.h"
#include "Player.h"
#include <mutex>
#include <thread>
/*
������������ߵ����
*/
class PlayerMgr :public MFW::Singleton<PlayerMgr>
{
private:
	//�������е��������
	std::mutex mPlayersMutex;
	std::unordered_map<long long, std::shared_ptr<Player>> mPlayers;
public:
	//��ȡ�����Ϣ
	bool GetPlayer(long long id, std::shared_ptr<Player>& playerptr);
	//������
	bool AddPlayer(long long id, std::shared_ptr<Player>& playerptr);
	//ɾ�����
	bool SubPlayer(long long);
	//��ȡ���е����
	std::unordered_map<long long, std::shared_ptr<Player>>& GetPlayerMap();
};

