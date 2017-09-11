#pragma once
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>

#include "Chess_Global.h"
#include "Chess_Rule_XZMJ.h"
#include "Chess_Card_MJ.h"
#include "Chess_Table_XZMJ.h"

/*
Ѫս�齫�����������״̬�л���
1����¼���ӵ�״̬
2����¼��ҵ�״̬
3���ж�����Ƿ���Գ���
4���ж��������
*/

class Chess_Table_XZMJ;
class Chess_Player_XZMJ;

class Chess_Rule_XZMJ
{
private:
	int jiangPai = 0;
	bool MayHu(std::vector<int>pai,int queZhang);
	bool remainPai(std::vector<int>pai);
	//�������Ͷ�Ӧ�ķ���
	std::map<EPaiXing_XZMJ, int> mEPaiXing_XZMJFans;
public:
	//ԭʼ��
	std::vector<std::shared_ptr<Chess_Card_MJ>> mCards;
	std::vector<std::shared_ptr<Chess_Card_MJ>> mWalls;
	std::shared_ptr<Chess_Table_XZMJ> mChess_Table;

	virtual void init();
	//���ǽ
	void BuildWall();
	//ȡ��
	bool GetCards(int count, std::vector<std::shared_ptr<Chess_Card_MJ>>& cards);
	bool GetCard(std::shared_ptr<Chess_Card_MJ>& card);
	//ȱ�ƽ��������ݻ�ɫ��������һ����,����Ѿ�ȱ�˷���true�����ûȱ���ػ�����Щ��
	bool GetQue(EChess_Type type,std::vector<std::shared_ptr<Chess_Card_MJ>>& cards, 
		std::vector<std::shared_ptr<Chess_Card_MJ>>& queCards);
	//���ƽ�����������ҿ����������Լ���Ӧ�ı���
	void AnalysisTing(std::shared_ptr<Chess_Player_XZMJ> playerPtr);

	//�����,playerptr��ʾ�����
	void CheckPeng();
	//����,isselfΪtrue��ʾ�Լ�
	void CheckGang(bool isself);
	//����,isselfΪtrue��ʾ�Լ�
	void CheckHu(bool isself);
	//��ȡ������͵���ߵ÷�
	
};
