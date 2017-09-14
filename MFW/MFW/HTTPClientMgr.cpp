#include "HTTPClientMgr.h"

void HTTPClientMgr::OnRead(std::shared_ptr<NNTCPLinkNode>  session, std::string data, NNTCPNode& netNode)
{
	HttpResPonse httpResPonse;
	if (HttpParser::ParseDataResponse(data, httpResPonse))
	{

	}
	else
	{

	}
}
void HTTPClientMgr::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	HttpRequest request;
	request.SetMethod(EHttpMethod::GET);
	//request.SetUrl(NetUtility::UrlEncode("/index.html"));
	request.SetUrl("/");
	request.SetVesionMajor(1);
	request.SetVesionMinor(1);
	request.AddParam("Host", "67.218.141.114 : 8080");
	request.AddParam("Connection", "keep - alive");
	request.AddParam("Upgrade - Insecure - Requests", "1");
	request.AddParam("User - Agent", "Mozilla / 5.0 (Windows NT 6.1; WOW64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 60.0.3112.90 Safari / 537.36");
	request.AddParam("Accept", "text / html, application / xhtml + xml, application / xml; q = 0.9, image / webp, image / apng, */*;q=0.8");
	request.AddParam("Accept-Encoding", "gzip, deflate");
	request.AddParam("Accept-Language", "zh-CN,zh;q=0.8");
	request.SetBody("");
	std::string data = "";
	request.ParseToString(data);
	netNode.SendData(session, data);
}
void HTTPClientMgr::OnDisConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
}
void HTTPClientMgr::OnTimer(uv_timer_t* handle)
{
	HTTPRequestInfo info;
	while (popHTTRequest(info))
	{
		NNNodeInfo nNNodeInfo;
		nNNodeInfo.Ip = info.ip;
		nNNodeInfo.isClient = true;
		nNNodeInfo.Port = info.port;
		nNNodeInfo.OnConnected = std::bind(&HTTPClientMgr::OnConnected, this, std::placeholders::_1, std::placeholders::_2);
		nNNodeInfo.OnDisConnected = std::bind(&HTTPClientMgr::OnDisConnected, this, std::placeholders::_1, std::placeholders::_2);
		nNNodeInfo.OnRead = std::bind(&HTTPClientMgr::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

		NNTCPServerMgr::AddServer(handle->loop, nNNodeInfo);
	}

}
void HTTPClientMgr::start()
{
	NNNodeInfo nNNodeInfo;
	nNNodeInfo.Ip = "0.0.0.0";
	nNNodeInfo.isClient = true;
	nNNodeInfo.Port = 8888;
	nNNodeInfo.OnConnected = std::bind(&HTTPClientMgr::OnConnected, this, std::placeholders::_1, std::placeholders::_2);
	nNNodeInfo.OnDisConnected = std::bind(&HTTPClientMgr::OnDisConnected, this, std::placeholders::_1, std::placeholders::_2);
	nNNodeInfo.OnRead = std::bind(&HTTPClientMgr::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	nNNodeInfo.OnTimered = std::bind(&HTTPClientMgr::OnTimer, this, std::placeholders::_1);
	NNTCPServerMgr::RunServer(nNNodeInfo);
}

//httpclient
void HTTPClientMgr::pushHTTRequest(HTTPRequestInfo& hTTRequest)
{
	std::lock_guard < std::mutex > lg(mHTTRequestsMutex);
	mHTTRequests.push(hTTRequest);
}
bool HTTPClientMgr::popHTTRequest(HTTPRequestInfo& hTTRequest)
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