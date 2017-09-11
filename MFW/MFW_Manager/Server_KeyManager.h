#pragma once
#include <map>
#include "Singleton.h"

class Server_KeyManager:public MFW::Singleton<Server_KeyManager>
{
private:
	std::map<long long, std::string> ClientsTokens;
public:
	void SetClientsTokens(long long Key, std::string& token);
	bool GetClientsTokens(long long Key, std::string& token);
	void DelClientsTokens(long long Key);

	std::string GetKey(long long seed);
};
