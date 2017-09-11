#include "DBDatas.h"

namespace DBProduce
{

	bool DBDatas::GetDBAccount(long long id, std::shared_ptr<DBAccount>& DBAccountptr)
	{
		std::lock_guard<std::mutex> lg(mDBAccountsMutex);
		if (mDBAccounts.find(id) != mDBAccounts.end())
		{
			DBAccountptr = mDBAccounts[id];
			return true;
		}
		return false;
	}
	bool DBDatas::AddDBAccount(long long id, std::shared_ptr<DBAccount>& DBAccountptr)
	{
		std::lock_guard<std::mutex> lg(mDBAccountsMutex);
		if (mDBAccounts.find(id) != mDBAccounts.end())
		{
			return false;
		}
		else
		{
			mDBAccounts.insert(std::pair<long long, std::shared_ptr<DBAccount>>(id, DBAccountptr));
			return true;
		}
	}
	bool DBDatas::SubDBAccount(long long id)
	{
		std::lock_guard<std::mutex> lg(mDBAccountsMutex);
		if (mDBAccounts.find(id) != mDBAccounts.end())
		{
			mDBAccounts.erase(id);
			return true;
		}
		return false;
	}
	std::unordered_map<long long, std::shared_ptr<DBAccount>>& DBDatas::GetDBAccountMap()
	{
		return mDBAccounts;
	}

	bool DBDatas::GetDBUserInfo(long long id, std::shared_ptr<DBUserInfo>& DBUserInfoptr)
	{
		std::lock_guard<std::mutex> lg(mDBUserInfosMutex);
		if (mDBUserInfos.find(id) != mDBUserInfos.end())
		{
			DBUserInfoptr = mDBUserInfos[id];
			return true;
		}
		return false;
	}
	bool DBDatas::AddDBUserInfo(long long id, std::shared_ptr<DBUserInfo>& DBUserInfoptr)
	{
		std::lock_guard<std::mutex> lg(mDBUserInfosMutex);
		if (mDBUserInfos.find(id) != mDBUserInfos.end())
		{
			return false;
		}
		else
		{
			mDBUserInfos.insert(std::pair<long long, std::shared_ptr<DBUserInfo>>(id, DBUserInfoptr));
			return true;
		}
	}
	bool DBDatas::SubDBUserInfo(long long id)
	{
		std::lock_guard<std::mutex> lg(mDBUserInfosMutex);
		if (mDBUserInfos.find(id) != mDBUserInfos.end())
		{
			mDBUserInfos.erase(id);
			return true;
		}
		return false;
	}
	std::unordered_map<long long, std::shared_ptr<DBUserInfo>>& DBDatas::GetDBUserInfoMap()
	{
		return mDBUserInfos;
	}

}
