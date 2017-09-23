#pragma once
#include "Singleton.h"
#include "HttpMgr.h"
#include "Net_Handler.h"
#include "Json/json.h"
#include <vector>

enum class ETABLESTATE
{
	INVALID_TABLEHANDLE = 0,
	TABLESTATE_OK = 0,						//正确
	TABLESTATE_WAIT = -100,					//当前正在等待玩家操作
	TABLESTATE_END = -101,					//游戏局已经结束
	TABLESTATE_NOTENOUGHMEM = -102,         //调用申请的json字符串空间不足
	TABLESTATE_ERRSERIAL = -103,            //提交的Action序列号不匹配
	TABLESTATE_NOTWAITING = -104,           //提交Action时桌子并没有等待玩家操作
	TABLESTATE_ERRRESPONSE = -105,          //提交Action的内容错误
};

enum class EMethod {
	ECreateGameTable = 0,
	EDestroyGameTable = 1,
	EGameTableStartGame = 2,
	EGameTableGetState = 3,
	EGameTableSetAction = 4,
	EGameTableResetGame = 5,
};

class Net_ClientHandler :public MFW::Singleton<Net_ClientHandler>
{
private:
	HttpMgr httpMgr;
	void init();
	bool isinit = false;
	
public:
	void OnRead(std::shared_ptr<NNTCPLinkNode>  session, HttpRequest& httpRequest, NNTCPNode& netNode);
	void OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	void OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode);
	void OnTime();

	void HandleData(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode);
	void HandleMsgData(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid,Json::Value data);

	void CreateGameTable(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode,int cgsid, Json::Value data);
	void DestroyGameTable(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid, Json::Value data);
	void GameTableStartGame(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid, Json::Value data);
	void GameTableGetState(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid,  Json::Value data);
	void GameTableSetAction(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid,  Json::Value data);
	void GameTableResetGame(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode, int cgsid, Json::Value data);

};