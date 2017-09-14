#include "HTTPClientMgr.h"




//httpclient
void HTTPClientMgr::pushHTTRequest(HTTRequestInfo& hTTRequest)
{
	std::lock_guard < std::mutex > lg(mHTTRequestsMutex);
	mHTTRequests.push(hTTRequest);
}
bool HTTPClientMgr::popHTTRequest(HTTRequestInfo& hTTRequest)
{
	std::lock_guard < std::mutex > lg(mHTTRequestsMutex);
	if (mHTTRequests.size() == 0)
		return false;
	hTTRequest = mHTTRequests.front();
	mHTTRequests.pop();
	return true;
}
void HTTPClientMgr::pushHTTRequest(HTTPResposeInfo& hTTPResposeInfo)
{
	std::lock_guard < std::mutex > lg(mHTTPResposesMutex);
	mHTTPResposes.push(hTTPResposeInfo);
}
bool HTTPClientMgr::popHTTRequest(HTTPResposeInfo& hTTPResposeInfo)
{
	std::lock_guard < std::mutex > lg(mHTTPResposesMutex);
	if (mHTTPResposes.size() == 0)
		return false;
	hTTPResposeInfo = mHTTPResposes.front();
	mHTTPResposes.pop();
	return true;
}