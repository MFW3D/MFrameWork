#pragma once
#include <mutex>
#include <thread>
#include <unordered_map>
#include "DBTypes.h"
#include "Singleton.h"
namespace DBProduce
{
    class DBDatas
    {
    private:
        std::mutex mDBAccountsMutex;
        std::unordered_map < long long, std::shared_ptr < DBAccount >> mDBAccounts;

        std::mutex mDBUserInfosMutex;
        std::unordered_map < long long, std::shared_ptr < DBUserInfo >> mDBUserInfos;

    public:
        bool GetDBAccount(long long id, std::shared_ptr<DBAccount>& DBAccountptr);
		bool AddDBAccount(long long id, std::shared_ptr<DBAccount>& DBAccountptr);
		bool SubDBAccount(long long);
		std::unordered_map<long long, std::shared_ptr<DBAccount>>& GetDBAccountMap();

        bool GetDBUserInfo(long long id, std::shared_ptr<DBUserInfo>& DBUserInfoptr);
		bool AddDBUserInfo(long long id, std::shared_ptr<DBUserInfo>& DBUserInfoptr);
		bool SubDBUserInfo(long long);
		std::unordered_map<long long, std::shared_ptr<DBUserInfo>>& GetDBUserInfoMap();

	};
}
