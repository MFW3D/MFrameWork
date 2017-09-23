#pragma once
#include "Singleton.h"
#include "HttpMgr.h"
#include "Net_Handler.h"
#include "Json/json.h"
#include <vector>

enum class ETABLESTATE
{
	INVALID_TABLEHANDLE = 0,
	TABLESTATE_OK = 0,						//��ȷ
	TABLESTATE_WAIT = -100,					//��ǰ���ڵȴ���Ҳ���
	TABLESTATE_END = -101,					//��Ϸ���Ѿ�����
	TABLESTATE_NOTENOUGHMEM = -102,         //���������json�ַ����ռ䲻��
	TABLESTATE_ERRSERIAL = -103,            //�ύ��Action���кŲ�ƥ��
	TABLESTATE_NOTWAITING = -104,           //�ύActionʱ���Ӳ�û�еȴ���Ҳ���
	TABLESTATE_ERRRESPONSE = -105,          //�ύAction�����ݴ���
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