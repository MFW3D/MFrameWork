#pragma once

enum class EChess_Type
{
	None = 0,
	XZMJ = 1,
};

//��Ϸ����ҵĽ�ɫ
enum class EPlayer_Type
{
	None = 0,		//δ�������
	Watch = 1,		//��ս
	Wait = 2,		//�ȴ�����
	Game = 3,		//������Ϸ

};
//Ѫս�齫����״̬δ��ʼ��
enum class ETable_XZMJ_State
{
	None = 0,
	Pre_off = 11,
	Pre_WaitPlayer = 12,
	Pre_WaitPreper = 13,

	Game_Start = 21,
	Game_WaitQue = 22,
	Game_WaitPlay = 23,
	Game_WaitOption = 24,

	OVER_Balance = 31,
	Over_ReNew = 32,
	Over_RePlay = 33,
};
//Ѫս�齫���״̬
enum class EPlayer_XZMJ_State {
	None = 0,
	Pre_EnterRoomed = 1,
	Pre_Prepered = 2,
	Pre_Qued = 3,
	Game_OnTurn = 11,	//�Լ��ĳ��ƽ׶�
	Game_OffTurn = 12,//�Լ��Ŀ��н׶�
	Game_WaitP = 13,//�ȴ��Լ����ܺ�
	Game_WaitG = 14,//�ȴ��Լ����ܺ�
	Game_WaitH = 15,//�ȴ��Լ����ܺ�
	Game_WaitOtherP = 16,//�ȴ��Լ����ܺ�
	Game_WaitOtherG = 17,//�ȴ��Լ����ܺ�
	Game_WaitOtherH = 18,//�ȴ��Լ����ܺ�
	Over_Hued = 19,
};
//Ѫվ�齫�ĺ�������
enum class EPaiXing_XZMJ
{
	None = 0,

};
