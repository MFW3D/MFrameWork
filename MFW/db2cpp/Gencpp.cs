using MFWTools.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MFWTools
{
    public static class Gencpp
    {
        static String vesion = "V0.1";
        static StringBuilder sb = new StringBuilder();

        //架构性代码和协议生成
        public static void GenStructs()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBTypes.h", vesion, "生成所有的数据表结构类，一张表对应一个类。");
            sb.Append(@"#pragma once
#include <string>
namespace DBProduce
{
");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"	struct " + table.Key + @"
	{");
                foreach (DBField field in table.Value)
                {
                    sb.Append(@"
		" + TypesChange.dbtocpp(field.type) + @" " + field.name + @";");
                }
                sb.Append(@"
	};
");
            }
            sb.Append(@"}");
            OutPut.Out(GlobalData.SavePath + "\\DBTypes.h", sb.ToString());
        }

        public static void GenIds()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBIds.h", vesion, "用于管理对应数据表的最大id，每次插入id+1。");

            sb.Append(@"#pragma once
namespace DBProduce
{
	class DBIds
    {
    public:");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {

                sb.Append(@"
        static int " + table.Key + @";");
            }
            sb.Append(@"
    };
}");
            OutPut.Out(GlobalData.SavePath + "\\DBIds.h", sb.ToString());
            //cpp文件------------------------------------------------------------------------------

            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBIds.cpp", vesion, "用于管理对应数据表的最大id，每次插入id+1。");

            sb.Append(@"#include ""DBIds.h""
namespace DBProduce
{
");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
    int DBIds::" + table.Key + @"=0;");
            }
            sb.Append(@"
}");
            OutPut.Out(GlobalData.SavePath + "\\DBIds.cpp", sb.ToString());
        }

        public static void GenDBHandler()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBHandler.h", vesion, "数据库处理接口，任何调用车可以继承这个接口实现数据库的处理方法实现。");

            sb.Append(@"#pragma once
#include <memory>
#include ""DBTypes.h""
namespace DBProduce
{
	class DBHandler
	{
		public:
			DBHandler();
			virtual ~DBHandler();");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
			virtual void read" + table.Key + @"(std::shared_ptr <DBProduce::" + table.Key + @"> _" + table.Key + @")=0;");
            }
            sb.Append(@"
	};

}
");
            OutPut.Out(GlobalData.SavePath + "\\DBHandler.h", sb.ToString());
            //cpp文件------------------------------------------------------------
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBHandler.cpp", vesion, "数据库处理接口，任何调用车可以继承这个接口实现数据库的处理方法实现。");
            sb.Append(@"#include ""DBHandler.h""

namespace DBProduce
{
	DBHandler::DBHandler()
	{

	}
	DBHandler::~DBHandler()
	{

	}");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
	void DBHandler::read" + table.Key + @"(std::shared_ptr <DBProduce::" + table.Key + @"> _" + table.Key + @")
	{
		
	}
");
            }
            sb.Append(@"
}
");
            OutPut.Out(GlobalData.SavePath + "\\DBHandler.cpp", sb.ToString());
        }

        public static void GenDBReader()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBReader.h", vesion, "数据库统一读取实现，读取数据库所有的数据，并调用设置的处理接口进行处理。");

            sb.Append(@"#pragma once
#include <mysql.h>
#include <vector>
#include ""DBHandler.h""
#include ""DBTypes.h""
#include ""DBIds.h""
#include <memory>

namespace DBProduce
{
	class DBReader
	{
		private:
			static MYSQL conn;
			static MYSQL_RES *res_ptr;
			static MYSQL_ROW sqlrow;
			static std::vector<DBHandler*> dbHandlers;
		public:
			static void connect(const char* host,int port, const char* user,
			        const char* password, const char* database);
			static void Disconnect();
			static void DBtoHandler();
			static void SetDBHandler(DBHandler* _Handler);");

            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
			static void " + table.Key + @"toHandler();");
            }
            sb.Append(@"
	};

}
");
            OutPut.Out(GlobalData.SavePath + "\\DBReader.h", sb.ToString());
            //cpp-------------------------------------------------------------------
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DBReader.cpp", vesion, "数据库统一读取实现，读取数据库所有的数据，并调用设置的处理接口进行处理。");

            sb.Append(@"#include ""DBReader.h""

namespace DBProduce
{
	MYSQL DBReader::conn;
	MYSQL_RES* DBReader::res_ptr = nullptr;
	MYSQL_ROW DBReader::sqlrow;
	std::vector<DBHandler*> DBReader::dbHandlers;
	void DBReader::connect(const char* host,int port, const char* user,
	        const char* password, const char* database)
	{
		mysql_init (&conn);
		
		if (mysql_real_connect(&conn, host, user, password, database, port, NULL,
		        0))
		{
            mysql_query(&conn, ""SET NAMES UTF8"");
			printf(""mysql %s Connection success!\n"", host);
		}
		else
		{
			fprintf(stderr, ""Connection failed!\n"");
			if (mysql_errno(&conn))
			{
				fprintf(stderr, ""Connection error %d: %s\n"", mysql_errno(&conn),
				        mysql_error(&conn));
			}
			exit (EXIT_FAILURE);
		}
	}
	void DBReader::Disconnect()
	{
        mysql_close (&conn);
	}
	void DBReader::DBtoHandler()
	{");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
        " + table.Key + @"toHandler();");
            }
            sb.Append(@"
	}
	void DBReader::SetDBHandler(DBHandler* _Handler)
	{
		dbHandlers.push_back(_Handler);
	}");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
    void DBReader::" + table.Key + @"toHandler()
	{
		int res = mysql_query(&conn, ""SELECT * from " + table.Key + @""");
		if (res)
		{
			fprintf(stderr, ""SELECT error: %s\n"", mysql_error(&conn));
		}
		else
		{
			res_ptr = mysql_use_result(&conn);
			if (res_ptr)
			{
				while ((sqlrow = mysql_fetch_row(res_ptr)))
				{
					mysql_field_count (&conn);
					std::shared_ptr < " + table.Key + @"> p (new " + table.Key + @"());");

                for (int i = 0; i < table.Value.Count; i++)
                {
                    sb.Append(@"
					p->" + table.Value[i].name + "= ");
                    if (table.Value[i].type == "float" || table.Value[i].type == "double"
                        || table.Value[i].type == "decimal")
                    {
                        sb.Append("atof(sqlrow[" + i + "]);");
                    }
                    else if (table.Value[i].type == "short"
                            || table.Value[i].type == "int")
                    {
                        sb.Append("atoi(sqlrow[" + i + "]);");
                    }
                    else if (table.Value[i].type == "long")
                    {
                        sb.Append("atol(sqlrow[" + i + "]);");
                    }
                    else if (table.Value[i].type == "bigint")
                    {
                        sb.Append("atoll(sqlrow[" + i + "]);");
                    }
                    else
                    {
                        sb.Append("sqlrow[" + i + "];");
                    }
                }
                sb.Append(@"

                    if(p->" + table.Value[0].name + @">DBIds::" + table.Key + @")
                    {
                        DBIds::" + table.Key + @"=p->" + table.Value[0].name + @";
                    }
					for (auto handler : dbHandlers)
					{
						if (handler != nullptr)
                        {     
					        handler->read" + table.Key + @"(p);
                        }
					}
				}
				if (mysql_errno (&conn))
				{
					fprintf(stderr, ""Retrive error: %s\n"", mysql_error(&conn));
				}
				mysql_free_result (res_ptr);
			}
		}
    }");
            }
            sb.Append(@"
}
");
            OutPut.Out(GlobalData.SavePath + "\\DBReader.cpp", sb.ToString());
        }

        public static void GenRedisHandler()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "RedisHandler.h", vesion, "继承自DBHandler，以redis数据入库的方式来处理数据读出的数据。");
            sb.Append(@"#pragma once
#include ""DBHandler.h""
#include ""RedisDBEngine.h""
#include ""NetUtility.h""
#include ""DBTypes.h""

namespace DBProduce
{
	class RedisHandler: public DBHandler
	{
		private:
			DBProduce::RedisDBEngine* redisDBEngine;
		public:
			RedisHandler(DBProduce::RedisDBEngine* _redisDBEngine);
			virtual ~RedisHandler();

			//清空redis中所有的数据，慎用
			void flashAll();");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
			void read" + table.Key + @"(std::shared_ptr <DBProduce::" + table.Key + @"> _" + table.Key + @");");
            }
            sb.Append(@"
	};

}
");
            OutPut.Out(GlobalData.SavePath + "\\RedisHandler.h", sb.ToString());
            //CPP文件---------------------------------------------------------------------------
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "RedisHandler.cpp", vesion, "继承自DBHandler，以redis数据入库的方式来处理数据读出的数据。");

            sb.Append(@"#include ""RedisHandler.h""

namespace DBProduce
{
	RedisHandler::RedisHandler(DBProduce::RedisDBEngine* _redisDBEngine)
	{
		redisDBEngine = _redisDBEngine;
	}
	RedisHandler::~RedisHandler()
	{
		
	}
	void RedisHandler::flashAll()
	{
		std::string cmd = ""flushall"";
		redisDBEngine->excuteCommoned(cmd);
	}");

            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
	void RedisHandler::read" + table.Key + @"(std::shared_ptr <DBProduce::" + table.Key + @"> _" + table.Key + @")
	{");
                sb.Append(@"
        std::string cmd = ""hmset  " + table.Key + @":"" + std::to_string((long long)_" + table.Key + @"->" + table.Value[0].name + @"); ");
                for (int i = 1; i < table.Value.Count; i++)
                {
                    if (TypesChange.dbtocpp(table.Value[i].type) == "std::string")
                    {
                        sb.Append(@"
        cmd.append( "" " + table.Value[i].name + @"  "" + NetUtility::BinToHex(_" + table.Key + @"->" + table.Value[i].name + @")+"" "");");
                    }
                    else
                    {
                        sb.Append(@"
        cmd.append( "" " + table.Value[i].name + @"  "" + std::to_string(_" + table.Key + @"->" + table.Value[i].name + @")+"" "");");
                    }
                }
                sb.Append(@";
		redisDBEngine->excuteCommoned(cmd);
	}");
            }

            sb.Append(@"
}
");
            OutPut.Out(GlobalData.SavePath + "\\RedisHandler.cpp", sb.ToString());
        }

        public static void GenRedisReader()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "RedisReader.h", vesion, "RedisReader是用作功用查询redis数据库的读取器，调用其中方法读出相应的结构。");
            sb.Append(@"#pragma once
#include ""DBTypes.h""
#include ""RedisDBEngine.h""
#include ""DBCommon.h""
#include ""NetUtility.h""
namespace DBProduce
{
	class RedisReader
	{
		private:
			static DBProduce::RedisDBEngine* redisEngine;
		public:
			static void setRedisEngine(DBProduce::RedisDBEngine* _redisEngine);");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
			static bool Get" + table.Key + @"(std::shared_ptr<" + table.Key + @"> p, std::string  " + table.Value[0].name + @");");
            }
            sb.Append(@"
	};

}
");
            OutPut.Out(GlobalData.SavePath + "\\RedisReader.h", sb.ToString());
            //CPP文件---------------------------------------------------------------------------
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "RedisReader.cpp", vesion, "RedisReader是用作功用查询redis数据库的读取器，调用其中方法读出相应的结构。");
            sb.Append(@"#include ""RedisReader.h""
namespace DBProduce
{
    DBProduce::RedisDBEngine* RedisReader::redisEngine = nullptr;
	void RedisReader::setRedisEngine(DBProduce::RedisDBEngine* _redisEngine)
	{
		redisEngine = _redisEngine;
	}");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
	bool RedisReader::Get" + table.Key + @"(std::shared_ptr<" + table.Key + @"> p, std::string " + table.Value[0].name + @")

    {
		if (p == nullptr)
		{
			return false;
		}
		std::string results = """";
		std::string cmd = ""hmget " + table.Key + @":"" + " + table.Value[0].name + @"
                + """);//account passwd nickname
                for (int i = 1; i < table.Value.Count; i++)
                {
                    sb.Append(@" " + table.Value[i].name + @" ");
                }

                sb.Append(@""";
		if (!redisEngine->excuteCommoned(cmd.c_str(), results))
		{
			return false;
		}
		std::vector < std::string > vec;
		DBCommon::split(results, vec, "" "");
		if (vec.size() >= " + (table.Value.Count - 1) + @")
		{
            p->" + table.Value[0].name + @" = atof(" + table.Value[0].name + @".c_str());");
                for (int i = 1; i < table.Value.Count; i++)
                {


                    if (table.Value[i].type == "float"
                        || table.Value[i].type == "double"
                        || table.Value[i].type == "decimal")
                    {
                        sb.Append(@"
            p->" + table.Value[i].name + @" = atof(vec[" + (i - 1) + @"].c_str());");
                    }
                    else if (table.Value[i].type == "short"
                            || table.Value[i].type == "int")
                    {
                        sb.Append(@"
            p->" + table.Value[i].name + @" = atoi(vec[" + (i - 1) + @"].c_str());");
                    }
                    else if (table.Value[i].type == "long")
                    {
                        sb.Append(@"
            p->" + table.Value[i].name + @" = atol(vec[" + (i - 1) + @"].c_str());");
                    }
                    else if (table.Value[i].type == "bigint")
                    {
                        sb.Append(@"
            p->" + table.Value[i].name + @" = atoll(vec[" + (i - 1) + @"].c_str());");
                    }
                    else
                    {
                        sb.Append(@"
            p->" + table.Value[i].name + @" = NetUtility::HexToBin(vec[" + (i - 1) + @"]);");
                    }

                }
                sb.Append(@"
        }
		else
		{
			return false;
		}
		return true;
	}");
            }
            sb.Append(@"
}
");
            OutPut.Out(GlobalData.SavePath + "\\RedisReader.cpp", sb.ToString());
        }

        public static void GenDBDatas()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "RedisReader.h", vesion, "RedisReader是用作功用查询redis数据库的读取器，调用其中方法读出相应的结构。");
            sb.Append(@"#pragma once
#include <mutex>
#include <thread>
#include <unordered_map>
#include ""DBTypes.h""
#include ""Singleton.h""
namespace DBProduce
{
    class DBDatas
    {
    private:");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
        std::mutex m" + table.Key + @"sMutex;
        std::unordered_map < long long, std::shared_ptr < " + table.Key + @" >> m" + table.Key + @"s;
");
            }
            sb.Append(@"
    public:");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
        bool Get" + table.Key + @"(long long id, std::shared_ptr<" + table.Key + @">& " + table.Key + @"ptr);
		bool Add" + table.Key + @"(long long id, std::shared_ptr<" + table.Key + @">& " + table.Key + @"ptr);
		bool Sub" + table.Key + @"(long long);
		std::unordered_map<long long, std::shared_ptr<" + table.Key + @">>& Get" + table.Key + @"Map();
");

            }
            sb.Append(@"
	};
}
");
            OutPut.Out(GlobalData.SavePath + "\\DBDatas.h", sb.ToString());
            //CPP文件---------------------------------------------------------------------------
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "RedisReader.cpp", vesion, "RedisReader是用作功用查询redis数据库的读取器，调用其中方法读出相应的结构。");
            sb.Append(@"#include ""DBDatas.h""

namespace DBProduce
{
");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
	bool DBDatas::Get" + table.Key + @"(long long id, std::shared_ptr<" + table.Key + @">& " + table.Key + @"ptr)
	{
		std::lock_guard<std::mutex> lg(m" + table.Key + @"sMutex);
		if (m" + table.Key + @"s.find(id) != m" + table.Key + @"s.end())
		{
			" + table.Key + @"ptr = m" + table.Key + @"s[id];
			return true;
		}
		return false;
	}
	bool DBDatas::Add" + table.Key + @"(long long id, std::shared_ptr<" + table.Key + @">& " + table.Key + @"ptr)
	{
		std::lock_guard<std::mutex> lg(m" + table.Key + @"sMutex);
		if (m" + table.Key + @"s.find(id) != m" + table.Key + @"s.end())
		{
			return false;
		}
		else
		{
			m" + table.Key + @"s.insert(std::pair<long long, std::shared_ptr<" + table.Key + @">>(id, " + table.Key + @"ptr));
			return true;
		}
	}
	bool DBDatas::Sub" + table.Key + @"(long long id)
	{
		std::lock_guard<std::mutex> lg(m" + table.Key + @"sMutex);
		if (m" + table.Key + @"s.find(id) != m" + table.Key + @"s.end())
		{
			m" + table.Key + @"s.erase(id);
			return true;
		}
		return false;
	}
	std::unordered_map<long long, std::shared_ptr<" + table.Key + @">>& DBDatas::Get" + table.Key + @"Map()
	{
		return m" + table.Key + @"s;
	}
");
            }
            sb.Append(@"
}
");
            OutPut.Out(GlobalData.SavePath + "\\DBDatas.cpp", sb.ToString());
        }




        //业务性代码和协议生成
        public static void GenDBGameTask()
        {
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DGameTask.h", vesion, "用于实现游戏服务器与数据服务器的数据表操作消息处理");
            sb.Append(@"#pragma once

class DGameTask: public wdcyClient
{
	private:
		
	public:
		DGameTask(wdcyTcpServerDispatcher *pDispatcher, evutil_socket_t fd)
				: wdcyClient(pDispatcher, fd)
		{
			registerMsgHandle();
		}
		
		/*
		 * @brief 客户端已经建立连接
		 */
		void onConnected();

		/*
		 * @brief 客户端断开连接
		 */
		void onDisconnected();

		/*
		 * @brief 连接验证
		 */
		int verifyConn(const MessageHead* pMsg, const uint32_t iLength);
		/*
		 * @brief 消息解析
		 */
		void msgParse(const MessageHead* pMsg, const uint32_t iLength);

		/*
		 * @brief 消息注册
		 */
		void registerMsgHandle();
	private:
		wdcyMsgRouter m_MsgRouter;
    public:
		//自定义事件");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
        //表" + table.Key + @"的增删改查操作
        int onGet" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength);
		int onCreate" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength);
		int onUpdate" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength);
		int onDelete" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength);

");
            }
            sb.Append(@"
	};

");
            OutPut.Out(GlobalData.SavePath + "\\DGameTask.h", sb.ToString());
            //CPP文件---------------------------------------------------------------------------
            sb.Clear();
            sb = GenCommon.GenHeader(sb, "DGameTask.cpp", vesion, "用于实现游戏服务器与数据服务器的数据表操作消息处理");

            sb.Append(@"#include ""All.h""

/*
 * @brief 客户端已经建立连接
 */
void DGameTask::onConnected()
{
	std::cout << ""有游戏服务器连接进来"" << std::endl;
	DGameTaskMgr::getInstance().addClient(this);
}

/*
 * @brief 客户端断开连接
 */
void DGameTask::onDisconnected()
{
	std::cout << ""有游戏服务器断开连接"" << std::endl;
	DGameTaskMgr::getInstance().removeClient(getSockId());
}

/*
 * @brief 游戏服务器连接验证
 */
int DGameTask::verifyConn(const MessageHead* pMsg, const uint32_t iLength)
{
	std::cout << ""游戏服务器进行验证"" << std::endl;
	GD_LogicRegister stMsg;
	stMsg.ParseFromArray(pMsg->data, pMsg->length);
	
	std::cout << ""passwd:"" << stMsg.uiserverid() << std::endl;
	std::cout << ""--------------------------"" << std::endl;
	DG_LogicRegister sendMsg;
	sendMsg.set_iret(0);
	
	Net::send(this, sendMsg, DG_REGISTER);
	std::cout << ""verifyConn success"" << std::endl;
	
	return 0;
}

/*
 * @brief 消息解析
 */
void DGameTask::msgParse(const MessageHead* pMsg, const uint32_t iLength)
{
	bool bResult = m_MsgRouter.HandMsg(pMsg, pMsg->length);
	if (!bResult)
	{
		//GAME_LOG(LOG_ERROR, ""解析消息错误,:%d"", pMsg->msgId);
	}
}
");

            sb.Append(@"/*
 * @brief 消息注册
 */
void DGameTask::registerMsgHandle()
{
#define REGIST_MSG_HANDLE(msgid, func) \
	m_MsgRouter.regMsgHandler(msgid, std::bind(&DGameTask::func, this, std::placeholders::_1, std::placeholders::_2));
	");
            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
    //表" + table.Key + @"操作消息注册
    REGIST_MSG_HANDLE(GD_GET_" + table.Key.ToUpper() + @", onGet" + table.Key + @");
    REGIST_MSG_HANDLE(GD_CREATE_" + table.Key.ToUpper() + @", onCreate" + table.Key + @");
    REGIST_MSG_HANDLE(GD_UPDATE_" + table.Key.ToUpper() + @", onUpdate" + table.Key + @");
    REGIST_MSG_HANDLE(GD_DELETE_" + table.Key.ToUpper() + @", onDelete" + table.Key + @");

");
            }
            sb.Append(@"
}");

            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {

                sb.Append(@"
int DGameTask::onGet" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength)
{");
                sb.Append(@"
	GD_Get" + table.Key + @" stMsg;
	stMsg.ParseFromArray(pMsg->data, pMsg->length);
	
	std::shared_ptr < DBProduce::" + table.Key + @" > p" + table.Key + @"(new DBProduce::" + table.Key + @"());
	if (DBProduce::RedisReader::Get" + table.Key + @"(p" + table.Key + @", stMsg." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Key + table.Value[0].name + @"()))
	{
		DG_Get" + table.Key + @" sendMsg;
		PD::" + table.Key + @"* st" + table.Key + @" = sendMsg.mutable_st" + table.Key + @"();
		
		sendMsg.set_iret(0);
	    sendMsg.set_uiaccid(stMsg.uiaccid());
		");
                for (int i = 0; i < table.Value.Count; i++)
                {
                    sb.Append(@"
		st" + table.Key + @"->set_" + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"(p" + table.Key + @" ->" + table.Value[i].name + @");
");
                }
                sb.Append(@"
        
		Net::send(this, sendMsg, DG_GET_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""获取" + table.Key + @"成功"");

	}
	else
	{
		DG_Get" + table.Key + @" sendMsg;
		PD::" + table.Key + @"* st" + table.Key + @" = sendMsg.mutable_st" + table.Key + @"();
		sendMsg.set_iret(-1);
		sendMsg.set_uiaccid(stMsg.uiaccid());
		Net::send(this, sendMsg, DG_GET_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO,""获取" + table.Key + @"失败"");

	}
	return 0;");

                sb.Append(@"
}");

                sb.Append(@"
int DGameTask::onCreate" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength)
{");

                sb.Append(@"
	GD_Create" + table.Key + @" stMsg;
	stMsg.ParseFromArray(pMsg->data, pMsg->length);
	
	std::shared_ptr < DBProduce::" + table.Key + @" > p" + table.Key + @"(new DBProduce::" + table.Key + @"());
	if (!DBProduce::RedisReader::Get" + table.Key + @"(p" + table.Key + @", stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Value[0].name + @"()))
	{
		std::shared_ptr < DBProduce::DBMsg > dbMsg(new DBProduce::DBMsg());
		dbMsg->id = stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Value[0].name + @"();
		dbMsg->dbCMD = DBProduce::DBCMD::dbinsert;
		dbMsg->tablename = """ + table.Key + @""";
		std::shared_ptr < std::map<std::string, std::string>
		        > data(new std::map<std::string, std::string>());
        ");
                for (int i = 1; i < table.Value.Count; i++)
                {
                    if (TypesChange.dbtocpp(table.Value[i].type) != "std::string")
                    {
                        sb.Append(@"
	data->insert(
		        std::pair<std::string, std::string>(""" + table.Value[i].name + @""",
		                std::to_string(stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"())));");
                    }
                    else
                    {
                        sb.Append(@"
	data->insert(
		        std::pair<std::string, std::string>(""" + table.Value[i].name + @""",
		                stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"()));");
                    }
                }
                sb.Append(@"
		dbMsg->data = data;
		DBProduce::WriteBackMgr::getInstance().WriteBack(dbMsg);
		
		DG_Create" + table.Key + @" sendMsg;
		sendMsg.set_iret(0);
		sendMsg.set_uiaccid(stMsg.uiaccid());

        PD::" + table.Key + @"* st" + table.Key + @" = sendMsg.mutable_st" + table.Key + @"();
		
		");
                for (int i = 0; i < table.Value.Count; i++)
                {
                    sb.Append(@"
		st" + table.Key + @"->set_" + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"(stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"());
");
                }
                sb.Append(@"
    ");

                sb.Append(@"
		Net::send(this, sendMsg, DG_CREATE_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""创建" + table.Key + @"成功"");
	}
	else
	{
		DG_Create" + table.Key + @" sendMsg;
		sendMsg.set_iret(-1);
		sendMsg.set_uiaccid(stMsg.uiaccid());
		Net::send(this, sendMsg, DG_CREATE_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""创建_" + table.Key + @"失败"");
	}
	
	return 0;
                ");

                sb.Append(@"
}");

                sb.Append(@"
int DGameTask::onUpdate" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength)
{");
                sb.Append(@"
GD_Update" + table.Key + @" stMsg;
	stMsg.ParseFromArray(pMsg->data, pMsg->length);
	std::shared_ptr < DBProduce::" + table.Key + @" > p" + table.Key + @"(new DBProduce::" + table.Key + @"());
	if (DBProduce::RedisReader::Get" + table.Key + @"(p" + table.Key + @", stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Value[0].name + @"()))
	{
		std::shared_ptr < DBProduce::DBMsg > dbMsg(new DBProduce::DBMsg());
		dbMsg->id = stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Value[0].name + @"();

		dbMsg->dbCMD = DBProduce::DBCMD::dbupdate;
		dbMsg->tablename = """ + table.Key + @""";
		std::shared_ptr < std::map<std::string, std::string>
		> data(new std::map<std::string, std::string>());
");
                for (int i = 1; i < table.Value.Count; i++)
                {
                    if (TypesChange.dbtocpp(table.Value[i].type) != "std::string")
                    {
                        sb.Append(@"
	data->insert(
		        std::pair<std::string, std::string>(""" + table.Value[i].name + @""",
		                std::to_string(stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"())));");
                    }
                    else
                    {
                        sb.Append(@"
	data->insert(
		        std::pair<std::string, std::string>(""" + table.Value[i].name + @""",
		                stMsg.st" + table.Key + @"()." + TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + @"()));");
                    }
                }
                sb.Append(@"
		dbMsg->data = data;
		DBProduce::WriteBackMgr::getInstance().WriteBack(dbMsg);

		DG_Update" + table.Key + @" sendMsg;
		sendMsg.set_iret(0);
		sendMsg.set_uiaccid(stMsg.uiaccid());
		Net::send(this, sendMsg, DG_UPDATE_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""更新" + table.Key + @"成功"");
	}
	else
	{
		DG_Update" + table.Key + @" sendMsg;
		sendMsg.set_iret(-1);
		sendMsg.set_uiaccid(stMsg.uiaccid());
		Net::send(this, sendMsg, DG_UPDATE_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""更新" + table.Key + @"失败"");
	}
	return 0;
");

                sb.Append(@"
}");

                sb.Append(@"
int DGameTask::onDelete" + table.Key + @"(const MessageHead* pMsg, const uint32_t iLength)
{");

                sb.Append(@"
	GD_Delete" + table.Key + @" stMsg;
	stMsg.ParseFromArray(pMsg->data, pMsg->length);

	std::shared_ptr < DBProduce::" + table.Key + @" > p" + table.Key + @"(new DBProduce::" + table.Key + @"());
	if (DBProduce::RedisReader::Get" + table.Key + @"(p" + table.Key + @", stMsg." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Key + table.Value[0].name + @"()))
	{
		std::shared_ptr < DBProduce::DBMsg > dbMsg(new DBProduce::DBMsg());
		dbMsg->id = stMsg." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Key + table.Value[0].name + @"();
		dbMsg->dbCMD = DBProduce::DBCMD::dbdelete;
		dbMsg->tablename = """ + table.Key + @""";
		std::shared_ptr < std::map<std::string, std::string>
		> data(new std::map<std::string, std::string>());
		data->insert(
			std::pair<std::string, std::string>(""" + table.Value[0].name + @""",
			std::to_string(stMsg." + TypesChange.dbtoProtohead(table.Value[0].type) + table.Key + table.Value[0].name + @"())));
		

		dbMsg->data = data;
		DBProduce::WriteBackMgr::getInstance().WriteBack(dbMsg);

		DG_Delete" + table.Key + @" sendMsg;
		sendMsg.set_iret(0);
		sendMsg.set_uiaccid(stMsg.uiaccid());
		Net::send(this, sendMsg, DG_DELETE_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""删除" + table.Key + @"成功"");
	}
	else
	{
		DG_Get" + table.Key + @"  sendMsg;
		sendMsg.set_iret(-1);
        sendMsg.set_uiaccid(stMsg.uiaccid());
		Net::send(this, sendMsg, DG_DELETE_" + table.Key.ToUpper() + @");
		GAME_LOG(LOG_INFO, ""删除" + table.Key + @"失败"");
	}

	return 0;
");

                sb.Append(@"
}");
            }

            OutPut.Out(GlobalData.SavePath + "\\DGameTask.cpp", sb.ToString());
        }

        public static void GenDBGameProto()
        {
            StringBuilder sbb = new StringBuilder();
            int protoId = 200;
            sb.Clear();
            string head = @"syntax = ""proto3"";
import ""DB_Base.proto"";
package  PDB_Option;
";
            protoId++;

            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {

                protoId++;
                sb.Append(@"
//通过id获取" + table.Key + @"中的对应数据
message GD_Get" + table.Key + @"
{
    //#define GD_GET_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
         " + TypesChange.dbtoProto(table.Value[0].type) + " " + TypesChange.dbtoProtohead(table.Value[0].type) + table.Key + @"id = 2; 

}
");
                sbb.Append(@"
    GD_GET_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
message DG_Get" + table.Key + @"
{
    //#define DG_GET_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
    int32 iRet = 2;
    PDB_Base." + table.Key + " st" + table.Key + @" =3;
}
");
                sbb.Append(@"
    DG_GET_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
//创建" + table.Key + @"中的对应数据
message GD_Create" + table.Key + @"
{
    //#define GD_CREATE_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
    PDB_Base." + table.Key + " st" + table.Key + @" =2;
}
");
                sbb.Append(@"
    GD_CREATE_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
message DG_Create" + table.Key + @"
{
    //#define DG_CREATE_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
    int32 iRet =2;
    PDB_Base." + table.Key + " st" + table.Key + @" =3;
}
");
                sbb.Append(@"
    DG_CREATE_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
//更新" + table.Key + @"中的对应数据
message GD_Update" + table.Key + @"
{
    //#define GD_UPDATE_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
    PDB_Base." + table.Key + " st" + table.Key + @" =2;
}
");
                sbb.Append(@"
    GD_UPDATE_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
message DG_Update" + table.Key + @"
{
    //#define DG_UPDATE_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
    int32 iRet = 2;
}
");
                sbb.Append(@"
    DG_UPDATE_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
//通过id删除" + table.Key + @"中的对应数据
message GD_Delete" + table.Key + @"
{
    //#define GD_DELETE_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
        " + TypesChange.dbtoProto(table.Value[0].type) + " " + TypesChange.dbtoProtohead(table.Value[0].type) + table.Key + @"id = 2; 

}
");
                sbb.Append(@"
    GD_DELETE_" + table.Key.ToUpper() + @"=" + protoId + @";");
                protoId++;
                sb.Append(@"
message DG_Delete" + table.Key + @"
{
    //#define DG_DELETE_" + table.Key.ToUpper() + @" 	" + protoId + @"
    uint32 uiaccid = 1; 
    int32 iRet = 2;
}
");
                sbb.Append(@"
    DG_DELETE_" + table.Key.ToUpper() + @"=" + protoId + @";");

            }
            sb.Insert(0, @"
//替换消息头的宏定义

enum EDB_CMD{
    DB_CMD_NONE=0;
" + sbb.ToString() + @"
}");

            sb.Insert(0, head);

            OutPut.Out(GlobalData.ProtoPath + "\\DB_Option.proto", sb.ToString());
            //------------------------------------------------------------------------------------------------

        }

        public static void GenDBStructProto()
        {
            sb.Clear();
            sb.Append(@"syntax = ""proto3"";
package  PDB_Base; ");

            foreach (KeyValuePair<String, List<DBField>> table in DownDatas.tables)
            {
                sb.Append(@"
message " + table.Key + @"
{
");
                for (int i = 0; i < table.Value.Count; i++)
                {
                    sb.Append(@"
     " + Common.TypesChange.dbtoProto(table.Value[i].type) + " " + Common.TypesChange.dbtoProtohead(table.Value[i].type) + table.Value[i].name + " = " + (i + 1) + ";");
                }

                sb.Append(@"
}
");
            }
            OutPut.Out(GlobalData.ProtoPath + "\\DB_Base.proto", sb.ToString());
            //------------------------------------------------------------------------------------------------
        }
    }
}
