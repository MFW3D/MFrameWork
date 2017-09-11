#pragma once
#include <string>
/*
跨网络消息的封装
*/
class NetTransMsg
{
private:
	long long mNetId = 0;
	int mCmd = 0;
	std::string mData = "";
public:
	NetTransMsg();
	NetTransMsg(long long& id, int cmd, std::string& data);
	unsigned long long GetNetId();
	int GetCmd();
	std::string GetData();
	void SetNetId(unsigned long long& id);
	void SetCmd(int& cmd);
	void SetData(std::string& data);
};