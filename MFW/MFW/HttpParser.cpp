#include "HttpParser.h"

HttpRequest HttpParser::mHttpRequest;
HttpResPonse HttpParser::mHttpResPonse;
http_parser HttpParser::mParser;
http_parser_settings HttpParser::mSettings;
std::string HttpParser::mlastHeaderKey;
bool HttpParser::mIsInit;
bool HttpParser::mIsRespone;
std::string HttpParser::Methods[] = {
	"DELETE" ,
	"GET",
	"HEAD",
	"POST",
	"PUT",
	"CONNECT",
	"OPTIONS",
	"TRACE",
	"COPY",
	"LOCK",
	"MKCOL",
	"MOVE",
	"PROPFIND",
	"PROPPATCH",
	"SEARCH",
	"UNLOCK",
	"BIND",
	"REBIND",
	"UNBIND",
	"REPORT",
	"MKACTIVITY",
	"CHECKOUT",
	"MERGE",
	"MSEARCH",
	"NOTIFY",
	"SUBSCRIBE",
	"UNSUBSCRIBE",
	"PATCH",
	"PURGE",
	"MKCALENDAR",
	"LINK",
	"UNLINK",
};
std::map<int, std::string> HttpParser::Status;

std::string  HttpMsg::GetBody()
{
	return mBody;
}
void HttpMsg::SetBody(std::string body)
{
	mBody = body;
}
EHttpMethod HttpMsg::GetMethod()
{
	return mMethod;
}
void HttpMsg::SetMethod(EHttpMethod method)
{
	mMethod = method;
}

int HttpMsg::GetVesionMajor()
{
	return mVesionMajor;
}
void  HttpMsg::SetVesionMajor(int vesion)
{
	mVesionMajor = vesion;
}
int HttpMsg::GetVesionMinor()
{
	return mVesionMijor;
}
void  HttpMsg::SetVesionMinor(int vesion)
{
	mVesionMijor = vesion;
}
std::unordered_map<std::string, std::string> HttpMsg::GetParams()
{
	return mParams;
}
bool HttpMsg::AddParam(std::string key, std::string value)
{
	if (mParams.find(key) == mParams.end())
	{
		mParams.insert(std::pair<std::string, std::string>(key, value));
		return true;
	}
	return false;
}

int HttpMsg::GetStatus()
{
	return mStatus;
}
void HttpMsg::SetStatus(int status)
{
	mStatus = status;
}
std::string  HttpMsg::GetUrl()
{
	return mUrl;
}
void  HttpMsg::SetUrl(std::string url)
{
	mUrl = url;
}
void HttpMsg::Clear()
{
	mStatus = -1;
	mBody = "";
	mMethod = EHttpMethod::Error;
	mVesionMajor = -1;
	mVesionMijor = -1;
	mUrl = "";
	mParams.clear();
}

bool HttpRequest::ParseToString(std::string& result)
{
	if (mMethod == EHttpMethod::Error||
		mVesionMajor == -1 ||
		mVesionMijor == -1 )
		return false;
	result = "";
	result.append(HttpParser::Methods[(int)mMethod]);
	result.append(" ");
	result.append(mUrl);
	result.append(" ");
	result.append("HTTP/");
	result.append(std::to_string(mVesionMajor));
	result.append(".");
	result.append(std::to_string(mVesionMijor));
	result.append("\r\n");
	for (auto itr = mParams.begin(); itr != mParams.end(); itr++)
	{
		result.append(itr->first);
		result.append(": ");
		result.append(itr->second);
		result.append("\r\n");
	}
	result.append("\r\n");
	result.append(mBody);
	return true;
}
void HttpRequest::Clear()
{
	::HttpMsg::Clear();

}

bool HttpResPonse::ParseToString(std::string& result)
{
	if (mMethod == EHttpMethod::Error ||
		mVesionMajor == -1 ||
		mVesionMijor == -1)
		return false;
	if (HttpParser::Status.find(mStatus) == HttpParser::Status.end())
		return false;
	result = "";
	result.append("HTTP/");
	result.append(std::to_string(mVesionMajor));
	result.append(".");
	result.append(std::to_string(mVesionMijor));
	result.append(" ");
	result.append(std::to_string(mStatus));
	result.append(" ");
	result.append(HttpParser::Status[mStatus]);
	result.append("\r\n");

	for (auto itr = mParams.begin(); itr != mParams.end(); itr++)
	{
		result.append(itr->first);
		result.append(": ");
		result.append(itr->second);
		result.append("\r\n");
	}
	result.append("\r\n");
	result.append(mBody);
	return true;
}
void HttpResPonse::Clear()
{
}

void HttpParser::Init()
{
	mSettings.on_message_begin = OnMessageBegin;
	mSettings.on_headers_complete = OnHeadersComplete;
	mSettings.on_message_complete = OnMessageComplete;
	mSettings.on_header_field = OnHeaderField;
	mSettings.on_header_value = OnHeaderValue;
	mSettings.on_url = OnUrl;
	mSettings.on_status = OnStatus;
	mSettings.on_body = OnBody;

	Status.insert(std::pair<int, std::string>(100, "Continue"));
	Status.insert(std::pair<int, std::string>(101, "Protocols"));
	Status.insert(std::pair<int, std::string>(102, "Processing"));
	Status.insert(std::pair<int, std::string>(200, "OK"));
	Status.insert(std::pair<int, std::string>(201, "Created"));
	Status.insert(std::pair<int, std::string>(202, "Accepted"));
	Status.insert(std::pair<int, std::string>(203, "Non-Authoritative Information"));
	Status.insert(std::pair<int, std::string>(204, "Continue"));
	Status.insert(std::pair<int, std::string>(205, "Continue"));
	Status.insert(std::pair<int, std::string>(206, "Continue"));
	Status.insert(std::pair<int, std::string>(207, "Continue"));
	Status.insert(std::pair<int, std::string>(208, "Continue"));
	Status.insert(std::pair<int, std::string>(300, "Continue"));
	Status.insert(std::pair<int, std::string>(301, "Continue"));
	Status.insert(std::pair<int, std::string>(302, "Continue"));
	Status.insert(std::pair<int, std::string>(303, "Continue"));
	Status.insert(std::pair<int, std::string>(304, "Continue"));
	Status.insert(std::pair<int, std::string>(305, "Continue"));
	Status.insert(std::pair<int, std::string>(307, "Continue"));
	Status.insert(std::pair<int, std::string>(308, "Continue"));
	Status.insert(std::pair<int, std::string>(400, "Continue"));
	Status.insert(std::pair<int, std::string>(401, "Continue"));
	Status.insert(std::pair<int, std::string>(402, "Continue"));
	Status.insert(std::pair<int, std::string>(403, "Continue"));
	Status.insert(std::pair<int, std::string>(404, "Continue"));
	Status.insert(std::pair<int, std::string>(405, "Continue"));
	Status.insert(std::pair<int, std::string>(406, "Continue"));
	Status.insert(std::pair<int, std::string>(407, "Continue"));
	Status.insert(std::pair<int, std::string>(408, "Continue"));
	Status.insert(std::pair<int, std::string>(409, "Continue"));
	Status.insert(std::pair<int, std::string>(410, "Continue"));
	Status.insert(std::pair<int, std::string>(411, "Continue"));
	Status.insert(std::pair<int, std::string>(412, "Continue"));
	Status.insert(std::pair<int, std::string>(413, "Continue"));
	Status.insert(std::pair<int, std::string>(414, "Continue"));
	Status.insert(std::pair<int, std::string>(415, "Continue"));
	Status.insert(std::pair<int, std::string>(416, "Continue"));
	Status.insert(std::pair<int, std::string>(417, "Continue"));
	Status.insert(std::pair<int, std::string>(421, "Continue"));
	Status.insert(std::pair<int, std::string>(422, "Continue"));
	Status.insert(std::pair<int, std::string>(423, "Continue"));
	Status.insert(std::pair<int, std::string>(424, "Continue"));
	Status.insert(std::pair<int, std::string>(426, "Continue"));
	Status.insert(std::pair<int, std::string>(428, "Continue"));
	Status.insert(std::pair<int, std::string>(429, "Continue"));
	Status.insert(std::pair<int, std::string>(431, "Continue"));
	Status.insert(std::pair<int, std::string>(451, "Continue"));
	Status.insert(std::pair<int, std::string>(501, "Continue"));
	Status.insert(std::pair<int, std::string>(502, "Continue"));
	Status.insert(std::pair<int, std::string>(503, "Continue"));
	Status.insert(std::pair<int, std::string>(504, "Continue"));
	Status.insert(std::pair<int, std::string>(505, "Continue"));
	Status.insert(std::pair<int, std::string>(506, "Continue"));
	Status.insert(std::pair<int, std::string>(507, "Continue"));
	Status.insert(std::pair<int, std::string>(508, "Continue"));
	Status.insert(std::pair<int, std::string>(510, "Continue"));
	Status.insert(std::pair<int, std::string>(511, "Continue"));
}
int HttpParser::OnMessageBegin(http_parser* p)
{
	return 0;
}
int HttpParser::OnHeadersComplete(http_parser* p)
{
	return 0;
}
int HttpParser::OnMessageComplete(http_parser* p)
{
	return 0;
}
int HttpParser::OnHeaderField(http_parser* p, const char *at, size_t length)
{
	mlastHeaderKey = std::string(at, length);
	return 0;
}
int HttpParser::OnHeaderValue(http_parser* p, const char *at, size_t length)
{
	if (mlastHeaderKey != "")
	{
		if (mIsRespone) {
			mHttpResPonse.AddParam(mlastHeaderKey, std::string(at, length));
		}
		else
		{
			mHttpRequest.AddParam(mlastHeaderKey, std::string(at, length));
		}
	}
	mlastHeaderKey = "";
	return 0;
}
int HttpParser::OnUrl(http_parser* p, const char *at, size_t length)
{
	if (mIsRespone) {
		mHttpResPonse.SetUrl(std::string(at, length));
	}
	else
	{
		mHttpRequest.SetUrl(std::string(at, length));
	}
	return 0;
}
int HttpParser::OnStatus(http_parser* p, const char *at, size_t length)
{
	if (mIsRespone) {
		mHttpResPonse.SetStatus(p->status_code);
	}
	else {
		mHttpRequest.SetStatus(p->status_code);
	}
	return 0;
}
int HttpParser::OnBody(http_parser* p, const char *at, size_t length)
{
	if (mIsRespone)	{
		mHttpResPonse.SetBody(std::string(at, length));
	}
	else {
		mHttpRequest.SetBody(std::string(at, length));
	}
	return 0;
}

bool HttpParser::ParseDataRequest(std::string data, HttpRequest& httpRequest)
{
	if (!mIsInit) {
		Init();
	}
	mIsRespone = false;
	mHttpRequest.Clear();
	http_parser_init(&mParser, HTTP_REQUEST);
	size_t parsed;
	parsed = http_parser_execute(&mParser, &mSettings, data.c_str(), data.size());
	if (parsed == 0)
		return false;
	mHttpRequest.SetMethod((EHttpMethod)mParser.method);
	mHttpRequest.SetVesionMajor(mParser.http_major);
	mHttpRequest.SetVesionMinor(mParser.http_minor);
	httpRequest = mHttpRequest;
	return true;
}
bool HttpParser::ParseDataResponse(std::string data, HttpResPonse& httpResPonse)
{
	if (!mIsInit) {
		Init();
	}
	mIsRespone = true;
	mHttpResPonse.Clear();
	http_parser_init(&mParser, HTTP_RESPONSE);
	size_t parsed;
	parsed = http_parser_execute(&mParser, &mSettings, data.c_str(), data.size());
	if (parsed == 0)
		return false;
	mHttpResPonse.SetMethod((EHttpMethod)mParser.method);
	mHttpResPonse.SetVesionMajor(mParser.http_major);
	mHttpResPonse.SetVesionMinor(mParser.http_minor);
	httpResPonse = mHttpResPonse;
	return true;
}