#include "DBReader.h"

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
            mysql_query(&conn, "SET NAMES UTF8");
			printf("mysql %s Connection success!\n", host);
		}
		else
		{
			fprintf(stderr, "Connection failed!\n");
			if (mysql_errno(&conn))
			{
				fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&conn),
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
	{
        DBAccounttoHandler();
        DBUserInfotoHandler();
	}
	void DBReader::SetDBHandler(DBHandler* _Handler)
	{
		dbHandlers.push_back(_Handler);
	}
    void DBReader::DBAccounttoHandler()
	{
		int res = mysql_query(&conn, "SELECT * from DBAccount");
		if (res)
		{
			fprintf(stderr, "SELECT error: %s\n", mysql_error(&conn));
		}
		else
		{
			res_ptr = mysql_use_result(&conn);
			if (res_ptr)
			{
				while ((sqlrow = mysql_fetch_row(res_ptr)))
				{
					mysql_field_count (&conn);
					std::shared_ptr < DBAccount> p (new DBAccount());
					p->uid= atoll(sqlrow[0]);
					p->acc= sqlrow[1];
					p->pwd= sqlrow[2];
					p->tel= sqlrow[3];
					p->wx= sqlrow[4];
					p->qq= sqlrow[5];
					p->lastlogin= atoll(sqlrow[6]);
					p->createtime= atoll(sqlrow[7]);

                    if(p->uid>DBIds::DBAccount)
                    {
                        DBIds::DBAccount=p->uid;
                    }
					for (auto handler : dbHandlers)
					{
						if (handler != nullptr)
                        {     
					        handler->readDBAccount(p);
                        }
					}
				}
				if (mysql_errno (&conn))
				{
					fprintf(stderr, "Retrive error: %s\n", mysql_error(&conn));
				}
				mysql_free_result (res_ptr);
			}
		}
    }
    void DBReader::DBUserInfotoHandler()
	{
		int res = mysql_query(&conn, "SELECT * from DBUserInfo");
		if (res)
		{
			fprintf(stderr, "SELECT error: %s\n", mysql_error(&conn));
		}
		else
		{
			res_ptr = mysql_use_result(&conn);
			if (res_ptr)
			{
				while ((sqlrow = mysql_fetch_row(res_ptr)))
				{
					mysql_field_count (&conn);
					std::shared_ptr < DBUserInfo> p (new DBUserInfo());
					p->uid= atoll(sqlrow[0]);
					p->nickname= sqlrow[1];

                    if(p->uid>DBIds::DBUserInfo)
                    {
                        DBIds::DBUserInfo=p->uid;
                    }
					for (auto handler : dbHandlers)
					{
						if (handler != nullptr)
                        {     
					        handler->readDBUserInfo(p);
                        }
					}
				}
				if (mysql_errno (&conn))
				{
					fprintf(stderr, "Retrive error: %s\n", mysql_error(&conn));
				}
				mysql_free_result (res_ptr);
			}
		}
    }
}
