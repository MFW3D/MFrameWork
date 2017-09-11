#pragma once
#include <map>

#include "Singleton.h"

class AuthenticationMgr
{
private:
	//用于认证的key，储存ip和端口的64位和
	std::map<long long, std::string > keys;

public:

};
