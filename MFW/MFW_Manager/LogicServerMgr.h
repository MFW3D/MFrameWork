#pragma once
#include "Singleton.h"
#include <memory>
#include <string>
#include <map>
#include <thread>
#include "MangerPlayerInfo.h"
#include "ManagerGlobal.h"
#include "NNTCPServerMgr.h"
/*
用途：逻辑服务器管理类
	1、保存当前逻辑服务器在线人数
	2、保存逻辑服务器在线状态
	3、保存逻辑服务器基本信息
	4、实现玩家分服分流
	5、玩家断线重连依据

*/

class LogicServerInfo
{
public:
	std::string serverKey="";	//逻辑服务器标识
	std::string Ip = "0.0.0.0";	
	int Port = 0;
	unsigned long long ServerId = 0;
	std::map<long long, std::shared_ptr<MangerPlayerInfo>> MangerPlayerInfos;//玩家状态
	std::shared_ptr<NNTCPLinkNode> session=nullptr;	//对应的网络服务器
	NNTCPNode* netNode;								//对应的网络连接
};


class LogicServerMgr :public MFW::Singleton<LogicServerMgr>
{
private:
	std::map<unsigned long long, std::shared_ptr<LogicServerInfo>> LogicServerInfos;//逻辑服务器
	void OnTimer(Timer timer);
public:
	void Init();
	bool AddLogicServer(std::shared_ptr<LogicServerInfo> server);//添加逻辑服务器
	bool RemoveLogicServer(unsigned long long serverId);//移除逻辑服务器
	bool CheckLogicServer(unsigned long long serverId);//查询服务器是否存在
	bool GetPlayerServer(long long uid, unsigned long long& serverID);//查询玩家是否在服务器中
	unsigned long long DistributePlayer(long long uid);//为玩家分配服务器
	//大循环
	void Process();
};