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
��;���߼�������������
	1�����浱ǰ�߼���������������
	2�������߼�����������״̬
	3�������߼�������������Ϣ
	4��ʵ����ҷַ�����
	5����Ҷ�����������

*/

class LogicServerInfo
{
public:
	std::string serverKey="";	//�߼���������ʶ
	std::string Ip = "0.0.0.0";	
	int Port = 0;
	unsigned long long ServerId = 0;
	std::map<long long, std::shared_ptr<MangerPlayerInfo>> MangerPlayerInfos;//���״̬
	std::shared_ptr<NNTCPLinkNode> session=nullptr;	//��Ӧ�����������
	NNTCPNode* netNode;								//��Ӧ����������
};


class LogicServerMgr :public MFW::Singleton<LogicServerMgr>
{
private:
	std::map<unsigned long long, std::shared_ptr<LogicServerInfo>> LogicServerInfos;//�߼�������
	void OnTimer(Timer timer);
public:
	void Init();
	bool AddLogicServer(std::shared_ptr<LogicServerInfo> server);//����߼�������
	bool RemoveLogicServer(unsigned long long serverId);//�Ƴ��߼�������
	bool CheckLogicServer(unsigned long long serverId);//��ѯ�������Ƿ����
	bool GetPlayerServer(long long uid, unsigned long long& serverID);//��ѯ����Ƿ��ڷ�������
	unsigned long long DistributePlayer(long long uid);//Ϊ��ҷ��������
	//��ѭ��
	void Process();
};