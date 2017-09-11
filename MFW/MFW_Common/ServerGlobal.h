#pragma once
#include <string>
#include "Singleton.h"

class ServerCfg:public MFW::Singleton<ServerCfg>
{
public:
	//redis����
	std::string  DB_RedisIp = "127.0.0.1";
	int DB_RedisPort = 6379;
	//mysql����
	std::string  DB_MysqlIp = "192.168.210.58";
	int DB_MysqlPort = 3369;
	std::string  DB_MysqlUser = "root";
	std::string  DB_MysqlPwd = "root";
	std::string  DB_MysqlDb = "gameserver";
	//���ݷ���������
	std::string DB_IP = "0.0.0.0";
	int DB_Port2Login =5555 ;
	int DB_Port2Logic =5556 ;
	int DB_Port2Manager =5557 ;
	//�������������
	std::string Manager_IP = "0.0.0.0";
	int Manager_Port2Login = 6666;
	int Manager_Port2Logic = 6667;
	int Manager_Port2Client = 6668;
	//�߼�����������
	std::string Logic_IP = "0.0.0.0";
	int Logic_Port2Client = 7777;
	//��¼����������
	std::string Login_IP = "0.0.0.0";
	int Login_Port2Client =8888 ;

	std::string Web_IP = "0.0.0.0";
	int  Web_Port = 9999;

	//�ͻ�������
	std::string  Client_Vesion ="0.0.01" ;
	std::string  Client_UpdateUrl = "";
	std::string  Client_MainUrl = "";
	//����������Ϣ��������
	std::string Queue_db_login = "Queue_db_login";
	std::string Queue_login_db = "Queue_login_db";
	std::string Queue_db_logic = "Queue_db_logic";
	std::string Queue_logic_db = "Queue_logic_db";
	std::string Queue_db_manager = "Queue_db_manager";
	std::string Queue_manager_db = "Queue_manager_db";
	std::string Queue_manager_login = "Queue_manager_login";
	std::string Queue_login_manager = "Queue_login_manager";
	std::string Queue_manager_logic = "Queue_manager_logic";
	std::string Queue_logic_manager	= "Queue_logic_manager";
};



//��������������
class ServerGlobal:public MFW::Singleton<ServerGlobal>
{
public:
	bool Init(std::string path);
};