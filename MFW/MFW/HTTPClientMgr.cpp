#include "HTTPClientMgr.h"

void HTTPClientMgr::OnRead(std::shared_ptr<NNTCPLinkNode>  session,
	std::string data, NNTCPNode& netNode)
{
	HttpResPonse httpResPonse;
	if (isretry)
	{
		int oldsize = mteamp.size();
		//继续接收
		mteamp.append(data);
		if (mteamp.size() == oldsize + datalength)
		{
			if (mRequestDealings.find(netNode.nNNodeInfo.ClientId) != mRequestDealings.end())
			{
				HTTPResposeInfo info;
				info.mHTTRequest = mRequestDealings[netNode.nNNodeInfo.ClientId];
				info.Data = mteamp;
				mHttpResPonse.SetBody("");
				info.httpResPonse = mHttpResPonse;
				pushHTTPRespose(info);
			}
			datalength = 0;
			mteamp = "";
			isretry = false;
		}
		return;
	}
	if (HttpParser::ParseDataResponse(data, httpResPonse))
	{
		mHttpResPonse = httpResPonse;
		if (httpResPonse.mParams.find("Content-Length") != httpResPonse.mParams.end())
		{
			datalength = atoi(httpResPonse.mParams["Content-Length"].c_str());
			if (httpResPonse.mBody.size() == datalength)
			{
				mteamp = httpResPonse.mBody;
				if (mRequestDealings.find(netNode.nNNodeInfo.ClientId) != mRequestDealings.end())
				{
					HTTPResposeInfo info;
					info.mHTTRequest = mRequestDealings[netNode.nNNodeInfo.ClientId];
					info.Data = mteamp;
					mHttpResPonse.SetBody("");
					info.httpResPonse = mHttpResPonse;
					pushHTTPRespose(info);
				}
				datalength = 0;
				mteamp = "";
				isretry = false;
			}
			else
			{
				isretry = true;
				int oldsize = mteamp.size();
				//继续接收
				mteamp.append(data);
				if (mteamp.size() == oldsize + datalength)
				{
					if (mRequestDealings.find(netNode.nNNodeInfo.ClientId) != mRequestDealings.end())
					{
						HTTPResposeInfo info;
						info.mHTTRequest = mRequestDealings[netNode.nNNodeInfo.ClientId];
						info.Data = mteamp;
						mHttpResPonse.SetBody("");
						info.httpResPonse = mHttpResPonse;
						pushHTTPRespose(info);
					}
					datalength = 0;
					mteamp = "";
					isretry = false;
				}
			}
		}
	}
}
void HTTPClientMgr::OnConnected(std::shared_ptr<NNTCPLinkNode>  session, NNTCPNode& netNode)
{
	if (mRequestDealings.find(netNode.nNNodeInfo.ClientId) == mRequestDealings.end())
		return;
	HTTPRequestInfo info = mRequestDealings[netNode.nNNodeInfo.ClientId];
	HttpRequest request;
	request.SetMethod(info.mEHttpMethod);
	request.SetUrl("" + info.url + "");
	request.SetVesionMajor(1);
	request.SetVesionMinor(1);
	if (request.GetMethod() == EHttpMethod::POST)
	{
		request.SetBody(info.body);
		request.AddParam("Content-Length", std::to_string(info.body.size()));
	}
	//request.AddParam("Host", "" + info.ip + " : " + std::to_string(info.port) + "");
	//request.AddParam("Host",  info.ip );
	//request.AddParam("Connection", "close");
	//request.AddParam("Connection", "keep-alive");
	for(auto itr =info.params.begin();itr!= info.params.end();itr++)
	{
		request.AddParam(itr->first, itr->second);
	}
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
	if (popHTTPRequest(info))
	{
		NNNodeInfo nNNodeInfo;
		nNNodeInfo.Ip = info.ip;
		nNNodeInfo.IsClient = true;
		nNNodeInfo.Port = info.port;
		nNNodeInfo.OnConnected = std::bind(&HTTPClientMgr::OnConnected, this, std::placeholders::_1, std::placeholders::_2);
		nNNodeInfo.OnDisConnected = std::bind(&HTTPClientMgr::OnDisConnected, this, std::placeholders::_1, std::placeholders::_2);
		nNNodeInfo.OnRead = std::bind(&HTTPClientMgr::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

		unsigned long long  clientId = NNTCPServerMgr::AddServer(handle->loop, nNNodeInfo);
		if (clientId != -1)
		{
			mRequestDealings.insert(std::pair<unsigned long long, HTTPRequestInfo>(clientId, info));
		}
	}
}
void HTTPClientMgr::start()
{
	NNNodeInfo nNNodeInfo;
	nNNodeInfo.Ip = "0.0.0.0";
	nNNodeInfo.IsClient = true;
	nNNodeInfo.Port = 8888;
	nNNodeInfo.OnConnected = std::bind(&HTTPClientMgr::OnConnected, this, std::placeholders::_1, std::placeholders::_2);
	nNNodeInfo.OnDisConnected = std::bind(&HTTPClientMgr::OnDisConnected, this, std::placeholders::_1, std::placeholders::_2);
	nNNodeInfo.OnRead = std::bind(&HTTPClientMgr::OnRead, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	nNNodeInfo.OnTimered = std::bind(&HTTPClientMgr::OnTimer, this, std::placeholders::_1);
	NNTCPServerMgr::RunServer(nNNodeInfo);
}

//httpclient
void HTTPClientMgr::pushHTTPRequest(HTTPRequestInfo& hTTRequest)
{
	std::lock_guard < std::mutex > lg(mHTTRequestsMutex);
	mHTTRequests.push(hTTRequest);
}
bool HTTPClientMgr::popHTTPRequest(HTTPRequestInfo& hTTRequest)
{
	std::lock_guard < std::mutex > lg(mHTTRequestsMutex);
	if (mHTTRequests.size() == 0)
		return false;
	hTTRequest = mHTTRequests.front();
	mHTTRequests.pop();
	return true;
}
void HTTPClientMgr::pushHTTPRespose(HTTPResposeInfo& hTTPResposeInfo)
{
	std::lock_guard < std::mutex > lg(mHTTPResposesMutex);
	mHTTPResposes.push(hTTPResposeInfo);
}
bool HTTPClientMgr::popHTTPRespose(HTTPResposeInfo& hTTPResposeInfo)
{
	std::lock_guard < std::mutex > lg(mHTTPResposesMutex);
	if (mHTTPResposes.size() == 0)
		return false;
	hTTPResposeInfo = mHTTPResposes.front();
	mHTTPResposes.pop();
	return true;
}