#pragma once

//�齫����
enum class EMJ_Type
{
	None = 0,		//��
	ZFB = 1,		//�У�������
	FENG = 2,		//����������
	HUA = 3,		//��
	WAN = 4,		//��
	TIAO = 5,		//��
	BING = 6,		//Ͳ��
};
//�齫������
enum class EMJ_Card
{
	None = 0,		//��
	Zhong = 11,		//��
	Fa = 12,			//��
	Bai = 13,			//��
	Dong = 21,		//��
	Nan = 22,		//��
	Xi = 23,			//��
	Bei = 24,			//��
	Hua_1 = 31,
	Hua_2 = 32,
	Hua_3 = 33,
	Hua_4 = 34,
	Wan_1 = 41,		//һ��
	Wan_2 = 42,		//����
	Wan_3 = 43,		//����
	Wan_4 = 44,		//����
	Wan_5 = 45,		//����
	Wan_6 = 46,		//����
	Wan_7 = 47,		//����
	Wan_8 = 48,		//����
	Wan_9 = 49,		//����
	Tiao_1 = 51,		//һ��
	Tiao_2 = 52,		//����
	Tiao_3 = 53,		//����
	Tiao_4 = 54,		//����
	Tiao_5 = 55,		//����
	Tiao_6 = 56,		//����
	Tiao_7 = 57,		//����
	Tiao_8 = 58,		//����
	Tiao_9 = 59,		//����
	Bing_1 = 61,		//һ��
	Bing_2 = 62,		//����
	Bing_3 = 63,		//����
	Bing_4 = 64,		//�ı�
	Bing_5 = 65,		//���
	Bing_6 = 66,		//����
	Bing_7 = 67,		//�߱�
	Bing_8 = 68,		//�˱�
	Bing_9 = 69,		//�ű�
};

class Chess_Card_MJ 
{
public:
	Chess_Card_MJ(EMJ_Card mj_Card);
	Chess_Card_MJ();
	EMJ_Card MEMJ_Card = EMJ_Card::None;//��,����/10������%10
};
