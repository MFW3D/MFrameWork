#include "Server_KeyManager.h"
#include "NetUtility.h"

void Server_KeyManager::SetClientsTokens(long long Key, std::string& token)
{
	if (ClientsTokens.find(Key) != ClientsTokens.end())
	{
		ClientsTokens[Key] = token;
	}
	else
	{
		ClientsTokens.insert(std::pair<long long, std::string>(Key, token));
	}
}
bool Server_KeyManager::GetClientsTokens(long long Key, std::string& token)
{
	if (ClientsTokens.find(Key) != ClientsTokens.end())
	{
		token=ClientsTokens[Key];
	}
	else
	{
		return false;
	}
}
void Server_KeyManager::DelClientsTokens(long long Key)
{
	if (ClientsTokens.find(Key) != ClientsTokens.end())
	{
		ClientsTokens.erase(Key);
	}
}

std::string Server_KeyManager::GetKey(long long seed)
{
	seed += CHRONO_SYSTEM_NOW_MICRO();
	return std::to_string(seed);
}