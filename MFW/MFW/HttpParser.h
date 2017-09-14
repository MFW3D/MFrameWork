#pragma once
#include "http_parser.h"
#include <string>
#include <iostream>
#include <map>
#include <iostream>
#include <unordered_map>

enum class EHttpMethod
{
	Error = 32,
	EDELETE = 0,
	GET = 1,
	HEAD = 2,
	POST = 3,
	PUT = 4,
	CONNECT = 5,
	OPTIONS = 6,
	TRACE = 7,
	COPY = 8,
	LOCK = 9,
	MKCOL = 10,
	MOVE = 11,
	PROPFIND = 12,
	PROPPATCH = 13,
	SEARCH = 14,
	UNLOCK = 15,
	BIND = 16,
	REBIND = 17,
	UNBIND = 18,
	REPORT = 19,
	MKACTIVITY = 20,
	CHECKOUT = 21,
	MERGE = 22,
	MSEARCH = 23,
	NOTIFY = 24,
	SUBSCRIBE = 25,
	UNSUBSCRIBE = 26,
	PATCH = 27,
	PURGE = 28,
	MKCALENDAR = 29,
	LINK = 30,
	UNLINK = 31,
};

class HttpMsg
{
public:
	std::string mBody;
	int mStatus;
	EHttpMethod mMethod;
	int mVesionMajor;
	int mVesionMijor;
	std::string mUrl;
	std::unordered_map<std::string, std::string> mParams;

	std::string  GetBody();
	void  SetBody(std::string body);
	EHttpMethod  GetMethod();
	void  SetMethod(EHttpMethod method);
	int GetStatus();
	void SetStatus(int status);
	int GetVesionMajor();
	void  SetVesionMajor(int vesion);
	int  GetVesionMinor();
	void  SetVesionMinor(int vesion);
	std::string GetUrl();
	void SetUrl(std::string url);
	std::unordered_map<std::string, std::string> GetParams();
	bool AddParam(std::string key, std::string value);

	virtual bool ParseToString(std::string& result) = 0;
	virtual void Clear();
};


class HttpRequest:public HttpMsg
{
private:
public:
	virtual bool ParseToString(std::string& result);
	virtual void Clear();
};
class HttpResPonse:public HttpMsg
{
private:
public:
	virtual bool ParseToString(std::string& result);
	virtual void Clear();
};

class HttpParser
{
private:

	static HttpRequest mHttpRequest;
	static HttpResPonse mHttpResPonse;
	static http_parser mParser;
	static http_parser_settings mSettings;
	static std::string mlastHeaderKey;
	static bool mIsRespone;
	static bool mIsInit;
	static void Init();
	static int OnMessageBegin(http_parser* p);
	static int OnHeadersComplete(http_parser* p);
	static int OnMessageComplete(http_parser* p);
	static int OnHeaderField(http_parser* p, const char *at, size_t length);
	static int OnHeaderValue(http_parser* p, const char *at, size_t length);
	static int OnUrl(http_parser* p, const char *at, size_t length);
	static int OnStatus(http_parser* p, const char *at, size_t length);
	static int OnBody(http_parser* p, const char *at, size_t length);
public:
	static std::string Methods[];
	static std::map<int, std::string> Status;
	static bool ParseDataRequest(std::string data, HttpRequest& httpRequest);
	static bool ParseDataResponse(std::string data, HttpResPonse& httpResPonse);
};
