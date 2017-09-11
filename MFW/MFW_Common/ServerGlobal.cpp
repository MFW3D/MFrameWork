#include "ServerGlobal.h"
#include "SimpleIni.h"
#include "log4z.h"

bool ServerGlobal::Init(std::string path)
{
	if (path == "")
	{
#if _WIN32
		path = "./ServerCfg.ini";
#else
		path = "./ServerCfg.ini";
#endif
	}
	CSimpleIniA ini(true, true, true);
	SI_Error rc = ini.LoadFile(path.c_str());
	if (rc < 0)
	{
		LOGE("¶ÁÈ¡ÅäÖÃÊ§°Ü");
		return false;
	}

	bool bHasMultipleValues = false;
	ServerCfg::GetInstance()->DB_RedisIp = ini.GetValue("DB", "DB_RedisIp", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_RedisPort = ini.GetLongValue("DB", "DB_RedisPort", 6379, &bHasMultipleValues);

	ServerCfg::GetInstance()->DB_MysqlIp = ini.GetValue("DB", "DB_MysqlIp", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_MysqlPort = ini.GetLongValue("DB", "DB_MysqlPort", 3369, &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_MysqlUser = ini.GetValue("DB", "DB_MysqlUser", "root", &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_MysqlPwd = ini.GetValue("DB", "DB_MysqlPwd", "root", &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_MysqlDb = ini.GetValue("DB", "DB_MysqlDb", "db", &bHasMultipleValues);

	ServerCfg::GetInstance()->DB_IP = ini.GetValue("DB", "DB_IP", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_Port2Login = ini.GetLongValue("DB", "DB_Port2Login", 5555, &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_Port2Logic = ini.GetLongValue("DB", "DB_Port2Logic", 5556, &bHasMultipleValues);
	ServerCfg::GetInstance()->DB_Port2Manager = ini.GetLongValue("DB", "DB_Port2Manager", 5557, &bHasMultipleValues);

	ServerCfg::GetInstance()->Manager_IP = ini.GetValue("Manager", "Manager_IP", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->Manager_Port2Login = ini.GetLongValue("Manager", "Manager_Port2Login", 6666, &bHasMultipleValues);
	ServerCfg::GetInstance()->Manager_Port2Logic = ini.GetLongValue("Manager", "Manager_Port2Logic", 6667, &bHasMultipleValues);
	ServerCfg::GetInstance()->Manager_Port2Client = ini.GetLongValue("Manager", "Manager_Port2Client", 6668, &bHasMultipleValues);

	ServerCfg::GetInstance()->Logic_IP = ini.GetValue("Logic", "Logic_IP", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->Logic_Port2Client = ini.GetLongValue("Logic", "Logic_Port2Client", 7777, &bHasMultipleValues);

	ServerCfg::GetInstance()->Login_IP = ini.GetValue("Login", "Login_IP", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->Login_Port2Client = ini.GetLongValue("Login", "Login_Port2Client", 8888, &bHasMultipleValues);

	ServerCfg::GetInstance()->Web_IP = ini.GetValue("Web", "Web_IP", "0.0.0.0", &bHasMultipleValues);
	ServerCfg::GetInstance()->Web_Port = ini.GetLongValue("Web", "Web_Port", 9999, &bHasMultipleValues);

	ServerCfg::GetInstance()->Client_Vesion = ini.GetValue("Client", "Client_Vesion", "0.0.01", &bHasMultipleValues);
	ServerCfg::GetInstance()->Client_UpdateUrl = ini.GetValue("Client", "Client_UpdateUrl", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Client_MainUrl = ini.GetValue("Client", "Client_MainUrl", "", &bHasMultipleValues);

	ServerCfg::GetInstance()->Queue_db_login = ini.GetValue("Msgque", "DB_Login", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_login_db = ini.GetValue("Msgque", "login_db", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_db_logic = ini.GetValue("Msgque", "DB_Logic", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_logic_db = ini.GetValue("Msgque", "Logic_DB", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_db_manager = ini.GetValue("Msgque", "DB_Manager", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_manager_db = ini.GetValue("Msgque", "Manager_DB", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_manager_login = ini.GetValue("Msgque", "Manager_Login", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_login_manager = ini.GetValue("Msgque", "Login_Manager", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_manager_logic = ini.GetValue("Msgque", "Manager_Logic", "", &bHasMultipleValues);
	ServerCfg::GetInstance()->Queue_logic_manager = ini.GetValue("Msgque", "Logic_Manager", "", &bHasMultipleValues);



	return true;
}