#include "NetTransMsg.h"
#include "NetUtility.h"

NetTransMsg::NetTransMsg()
{

}
NetTransMsg::NetTransMsg(long long& id, int cmd, std::string& data)
{
	mNetId = id;
	mCmd = cmd;
	mData = data;
}
unsigned long long NetTransMsg::GetNetId()
{
	return mNetId;
}
int NetTransMsg::GetCmd()
{
	return mCmd;
}
std::string NetTransMsg::GetData()
{
	return mData;
}
void NetTransMsg::SetNetId(unsigned long long& id)
{
	mNetId = id;
}
void NetTransMsg::SetCmd(int& cmd)
{
	mCmd = cmd;
}
void NetTransMsg::SetData(std::string& data)
{
	mData = NetUtility::BinToHex(data);
}