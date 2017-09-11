#pragma once

//麻将牌型
enum class EMJ_Type
{
	None = 0,		//空
	ZFB = 1,		//中，发，白
	FENG = 2,		//东南西北风
	HUA = 3,		//花
	WAN = 4,		//万
	TIAO = 5,		//条
	BING = 6,		//筒子
};
//麻将所有牌
enum class EMJ_Card
{
	None = 0,		//空
	Zhong = 11,		//中
	Fa = 12,			//发
	Bai = 13,			//白
	Dong = 21,		//东
	Nan = 22,		//南
	Xi = 23,			//西
	Bei = 24,			//北
	Hua_1 = 31,
	Hua_2 = 32,
	Hua_3 = 33,
	Hua_4 = 34,
	Wan_1 = 41,		//一万
	Wan_2 = 42,		//二万
	Wan_3 = 43,		//三万
	Wan_4 = 44,		//四万
	Wan_5 = 45,		//五万
	Wan_6 = 46,		//六万
	Wan_7 = 47,		//七万
	Wan_8 = 48,		//八万
	Wan_9 = 49,		//九万
	Tiao_1 = 51,		//一条
	Tiao_2 = 52,		//二条
	Tiao_3 = 53,		//三条
	Tiao_4 = 54,		//四条
	Tiao_5 = 55,		//五条
	Tiao_6 = 56,		//六条
	Tiao_7 = 57,		//七条
	Tiao_8 = 58,		//八条
	Tiao_9 = 59,		//九条
	Bing_1 = 61,		//一饼
	Bing_2 = 62,		//二饼
	Bing_3 = 63,		//三饼
	Bing_4 = 64,		//四饼
	Bing_5 = 65,		//五饼
	Bing_6 = 66,		//六饼
	Bing_7 = 67,		//七饼
	Bing_8 = 68,		//八饼
	Bing_9 = 69,		//九饼
};

class Chess_Card_MJ 
{
public:
	Chess_Card_MJ(EMJ_Card mj_Card);
	Chess_Card_MJ();
	EMJ_Card MEMJ_Card = EMJ_Card::None;//牌,类型/10，点数%10
};
