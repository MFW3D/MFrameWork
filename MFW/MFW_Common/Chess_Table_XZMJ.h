#pragma once

#include "Chess_Table_XZMJ.h"
#include "Chess_Player_XZMJ.h"
class Chess_Player_XZMJ;
class Chess_Rule_XZMJ;

class Chess_Table_XZMJ_INfo
{
public:
	int mPlayerCount = 10;//�������
	int mPlayerGamingCount = 4;//��Ϸ�������
};
class Chess_Table_XZMJ
{
private:
	//ׯ��
	std::shared_ptr<Chess_Player_XZMJ> mChess_Player_XZMJZhuang;
public:
	//���ӻ�����Ϣ
	Chess_Table_XZMJ_INfo mChess_Table_XZMJ_INfo;

	//������Ϸ���
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayerGaming;	//���ڽ��е����
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayerWaiting;	//׼�������
	std::map<long long, std::shared_ptr<Chess_Player_XZMJ>> MPlayerWatching;	//�۲���
	std::shared_ptr<Chess_Player_XZMJ> mPlayerNow;

	//��ǰ�����ܺ����������
	std::vector<std::shared_ptr<Chess_Player_XZMJ>> mWaitPengs;
	std::vector<std::shared_ptr<Chess_Player_XZMJ>> mWaitGangs;
	std::vector<std::shared_ptr<Chess_Player_XZMJ>> mWaitHus;
	//��ǰ������ң��������
	std::shared_ptr<Chess_Player_XZMJ> mChess_Player_XZMJNow;
	std::shared_ptr<Chess_Player_XZMJ> mChess_Player_XZMJOp;

	//��ǰ����
	std::shared_ptr<Chess_Card_MJ> mChess_Card_MJNow;
	//����ָ��
	std::shared_ptr<Chess_Rule_XZMJ> mChess_Rule_XZMJ;

/************************************************************************/
/* ��Ϸ״̬�ж�                                                          */
/************************************************************************/
	//�������Ƿ񶼽���
	bool CheckPlayerEnterFinished();
	//�������Ƿ�׼��
	bool CheckPlayerAllReady();
	//�������Ƿ񶼶�ȱ���
	bool CheckPlayerAllQue();
	//�жϵ�ǰ����Ƿ����
	bool CheckPlayerNowHu();
	//�жϵ�ǰ����Ƿ���Ը�
	bool CheckPlayerNowGang();
	//�ж���������Ƿ���Ժ���
	bool CheckPlayerOtherHu();
	//�ж���������Ƿ���Ը���
	bool CheckPlayerOtherGang();
	//�ж���������Ƿ��������
	bool CheckPlayerOtherPeng();
	//�ж���Ϸ�Ƿ����
	bool CheckGameOver();

/************************************************************************/
/* ��Ϸ���̿���                                                          */
/************************************************************************/
	//��Ҽ�����Ϸ
	bool PlayerGetIn(std::shared_ptr<Chess_Player_XZMJ> playerPtr,EPlayer_Type type);
	//����ׯ��
	void SetZhuang(long long Uid);
	//��ʼ����
	void StartFaPai();
	//���õ�ǰ�������
	void SetPlayerNow(long long Uid);
	//���õ�ǰ�������
	void SetPlayerOp(long long Uid);
};