#include "DBMsg.h"

namespace DBProduce
{
	DBMsg::DBMsg()
	{
		tablename = "";
		dbCMD = DBCMD::dbnone;
	}
	DBMsg::DBMsg(std::string _tablename, DBCMD _dbCMD,std::map<std::string, std::string>  _data)
	{
		tablename = _tablename;
		dbCMD = _dbCMD;
		data = _data;
	}

}
