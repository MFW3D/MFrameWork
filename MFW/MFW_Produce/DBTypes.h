#pragma once
#include <string>
namespace DBProduce
{
	struct DBAccount
	{
		long long uid;
		std::string acc;
		std::string pwd;
		std::string tel;
		std::string wx;
		std::string qq;
		long long lastlogin;
		long long createtime;
	};
	struct DBUserInfo
	{
		long long uid;
		std::string nickname;
	};
}