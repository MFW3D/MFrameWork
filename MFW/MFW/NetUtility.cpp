#include "NetUtility.h"
//#include <codecvt>
#include <vector>
#include <fstream>

#include <string>
#include <clocale>

#include <iostream>
using namespace std;



#ifdef _WIN32
#include <winsock2.h>

//#pragma comment(lib,"ws2_32.lib") 

#else
#include <sys/socket.h>
#endif
#include <assert.h>
#define LEN 16 
#include <math.h>
#include <iostream>  
#include <time.h>  
#include <stdlib.h>  
#include <string.h>  

void swapStr(char *str, int begin, int end)
{
	int i, j;

	for (i = begin, j = end; i <= j; i++, j--) {
		if (str[i] != str[j]) {
			str[i] = str[i] ^ str[j];
			str[j] = str[i] ^ str[j];
			str[i] = str[i] ^ str[j];
		}
	}
}

unsigned long long NetUtility::CombineInt32(int n1, int n2)
{
	long long l = n1;
	l = l << 32;
	l = l | n2;
	return l;
}
void NetUtility::SplitLongLong(int& n1, int& n2, long long l)
{
	n2 = l & 0x00000000FFFFFFFF;
	l = l & 0xFFFFFFFF00000000;
	n1 = l >> 32;
}


int NetUtility::iptoint( const char *ipstr)
{
	return  ntohl(inet_addr(ipstr));
}

std::string  NetUtility::inttoip(int ipint)
{
	char * newchars = (char *)malloc(LEN);
	memset(newchars, '\0', LEN);
	newchars[0] = '.';
	char token[4];
	int bt, ed, len, cur;

	while (ipint) {
		cur = ipint % 256;
		sprintf(token, "%d", cur);
		strcat(newchars, token);
		ipint /= 256;
		if (ipint)  strcat(newchars, ".");
	}

	len = strlen(newchars);
	swapStr(newchars, 0, len - 1);

	for (bt = ed = 0; ed < len;) {
		while (ed < len && newchars[ed] != '.') {
			ed++;
		}
		swapStr(newchars, bt, ed - 1);
		ed += 1;
		bt = ed;
	}

	newchars[len - 1] = '\0';

	return newchars;
}

void NetUtility::GetIpPort(uv_tcp_t* client, int& ip, int& port)
{
	sockaddr_in addrMy;
	memset(&addrMy, 0, sizeof(addrMy));
	int len = sizeof(addrMy);
	uv_tcp_getpeername(client, (sockaddr*)&addrMy, &len);
	std::string ipstr = inet_ntoa(addrMy.sin_addr);
	ip=NetUtility::iptoint(ipstr.c_str());
	port = addrMy.sin_port;
	return;
}
std::string NetUtility::BinToHex(const std::string &strBin, bool bIsUpper)
{
	std::string strHex;
	strHex.resize(strBin.size() * 2);
	for (size_t i = 0; i < strBin.size(); i++)
	{
		uint8_t cTemp = strBin[i];
		for (size_t j = 0; j < 2; j++)
		{
			uint8_t cCur = (cTemp & 0x0f);
			if (cCur < 10)
			{
				cCur += '0';
			}
			else
			{
				cCur += ((bIsUpper ? 'A' : 'a') - 10);
			}
			strHex[2 * i + 1 - j] = cCur;
			cTemp >>= 4;
		}
	}

	return strHex;
}

std::string NetUtility::HexToBin(const std::string &strHex)
{
	if (strHex.size() % 2 != 0)
	{
		return "";
	}

	std::string strBin;
	strBin.resize(strHex.size() / 2);
	for (size_t i = 0; i < strBin.size(); i++)
	{
		uint8_t cTemp = 0;
		for (size_t j = 0; j < 2; j++)
		{
			char cCur = strHex[2 * i + j];
			if (cCur >= '0' && cCur <= '9')
			{
				cTemp = (cTemp << 4) + (cCur - '0');
			}
			else if (cCur >= 'a' && cCur <= 'f')
			{
				cTemp = (cTemp << 4) + (cCur - 'a' + 10);
			}
			else if (cCur >= 'A' && cCur <= 'F')
			{
				cTemp = (cTemp << 4) + (cCur - 'A' + 10);
			}
			else
			{
				return "";
			}
		}
		strBin[i] = cTemp;
	}

	return strBin;
}



string NetUtility::ws2s(const wstring& ws)
{
	string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

wstring NetUtility::s2ws(const string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	int nret = mbstowcs(_Dest, _Source, _Dsize);
	wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");

	return result;

}

wstring NetUtility::UTF2Uni(const char* src, std::wstring &t)
{
	if (src == NULL)
	{
		return L"";
	}

	int size_s = strlen(src);
	int size_d = size_s + 10;          //?

	wchar_t *des = new wchar_t[size_d];
	memset(des, 0, size_d * sizeof(wchar_t));

	int s = 0, d = 0;
	bool toomuchbyte = true; //set true to skip error prefix.

	while (s < size_s && d < size_d)
	{
		unsigned char c = src[s];
		if ((c & 0x80) == 0)
		{
			des[d++] += src[s++];
		}
		else if ((c & 0xE0) == 0xC0)  ///< 110x-xxxx 10xx-xxxx
		{
			wchar_t &wideChar = des[d++];
			wideChar = (src[s + 0] & 0x3F) << 6;
			wideChar |= (src[s + 1] & 0x3F);

			s += 2;
		}
		else if ((c & 0xF0) == 0xE0)  ///< 1110-xxxx 10xx-xxxx 10xx-xxxx
		{
			wchar_t &wideChar = des[d++];

			wideChar = (src[s + 0] & 0x1F) << 12;
			wideChar |= (src[s + 1] & 0x3F) << 6;
			wideChar |= (src[s + 2] & 0x3F);

			s += 3;
		}
		else if ((c & 0xF8) == 0xF0)  ///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		{
			wchar_t &wideChar = des[d++];

			wideChar = (src[s + 0] & 0x0F) << 18;
			wideChar = (src[s + 1] & 0x3F) << 12;
			wideChar |= (src[s + 2] & 0x3F) << 6;
			wideChar |= (src[s + 3] & 0x3F);

			s += 4;
		}
		else
		{
			wchar_t &wideChar = des[d++]; ///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 

			wideChar = (src[s + 0] & 0x07) << 24;
			wideChar = (src[s + 1] & 0x3F) << 18;
			wideChar = (src[s + 2] & 0x3F) << 12;
			wideChar |= (src[s + 3] & 0x3F) << 6;
			wideChar |= (src[s + 4] & 0x3F);

			s += 5;
		}
	}

	t = des;
	delete[] des;
	des = NULL;

	return t;
}
string NetUtility::UTF2Uni(const char* src, std::string &t)
{
	if (src == NULL)
	{
		return "";
	}

	int size_s = strlen(src);
	int size_d = size_s + 10;          //?

	char *des = new char[size_d];
	memset(des, 0, size_d * sizeof(char));

	int s = 0, d = 0;
	bool toomuchbyte = true; //set true to skip error prefix.

	while (s < size_s && d < size_d)
	{
		unsigned char c = src[s];
		if ((c & 0x80) == 0)
		{
			des[d++] += src[s++];
		}
		else if ((c & 0xE0) == 0xC0)  ///< 110x-xxxx 10xx-xxxx
		{
			char &wideChar = des[d++];
			wideChar = (src[s + 0] & 0x3F) << 6;
			wideChar |= (src[s + 1] & 0x3F);

			s += 2;
		}
		else if ((c & 0xF0) == 0xE0)  ///< 1110-xxxx 10xx-xxxx 10xx-xxxx
		{
			char &wideChar = des[d++];

			wideChar = (src[s + 0] & 0x1F) << 12;
			wideChar |= (src[s + 1] & 0x3F) << 6;
			wideChar |= (src[s + 2] & 0x3F);

			s += 3;
		}
		else if ((c & 0xF8) == 0xF0)  ///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		{
			char &wideChar = des[d++];

			wideChar = (src[s + 0] & 0x0F) << 18;
			wideChar = (src[s + 1] & 0x3F) << 12;
			wideChar |= (src[s + 2] & 0x3F) << 6;
			wideChar |= (src[s + 3] & 0x3F);

			s += 4;
		}
		else
		{
			char &wideChar = des[d++]; ///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 

			wideChar = (src[s + 0] & 0x07) << 24;
			wideChar = (src[s + 1] & 0x3F) << 18;
			wideChar = (src[s + 2] & 0x3F) << 12;
			wideChar |= (src[s + 3] & 0x3F) << 6;
			wideChar |= (src[s + 4] & 0x3F);

			s += 5;
		}
	}

	t = des;
	delete[] des;
	des = NULL;

	return t;
}

int NetUtility::Uni2UTF(const wstring& strRes, char *utf8, int nMaxSize)
{
	if (utf8 == NULL) {
		return -1;
	}
	int len = 0;
	int size_d = nMaxSize;


	for (wstring::const_iterator it = strRes.begin(); it != strRes.end(); ++it)
	{
		wchar_t wchar = *it;
		if (wchar < 0x80)
		{  //
		   //length = 1;
			utf8[len++] = (char)wchar;
		}
		else if (wchar < 0x800)
		{
			//length = 2;

			if (len + 1 >= size_d)
				return -1;

			utf8[len++] = 0xc0 | (wchar >> 6);
			utf8[len++] = 0x80 | (wchar & 0x3f);
		}
		else if (wchar < 0x10000)
		{
			//length = 3;
			if (len + 2 >= size_d)
				return -1;

			utf8[len++] = 0xe0 | (wchar >> 12);
			utf8[len++] = 0x80 | ((wchar >> 6) & 0x3f);
			utf8[len++] = 0x80 | (wchar & 0x3f);
		}
		else if (wchar < 0x200000)
		{
			//length = 4;
			if (len + 3 >= size_d)
				return -1;

			utf8[len++] = 0xf0 | ((int)wchar >> 18);
			utf8[len++] = 0x80 | ((wchar >> 12) & 0x3f);
			utf8[len++] = 0x80 | ((wchar >> 6) & 0x3f);
			utf8[len++] = 0x80 | (wchar & 0x3f);
		}

	}


	return len;
}

string NetUtility::s2utfs(const  string&  strSrc)
{
	string  strRes;
	wstring  wstrUni = s2ws(strSrc);

	char*  chUTF8 = new char[wstrUni.length() * 3];
	memset(chUTF8, 0x00, wstrUni.length() * 3);
	Uni2UTF(wstrUni, chUTF8, wstrUni.length() * 3);
	strRes = chUTF8;
	delete[]chUTF8;
	return strRes;
}

string  NetUtility::utfs2s(const string& strutf)
{
	wstring  wStrTmp;
	UTF2Uni(strutf.c_str(), wStrTmp);
	return ws2s(wStrTmp);
}

std::string NetUtility::get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}
string NetUtility::trim(const string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}
	return str.substr(pos);
}
int NetUtility::split(const string& str, vector<string>& ret_, string sep)
{
	if (str.empty())
	{
		return 0;
	}
	string tmp;
	string::size_type pos_begin = str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}
string NetUtility::replace(const string& str, const string& src,
	const string& dest)
{
	string ret;

	string::size_type pos_begin = 0;
	string::size_type pos = str.find(src);
	while (pos != string::npos)
	{
		ret.append(str.data() + pos_begin, pos - pos_begin);
		ret += dest;
		pos_begin = pos + 1;
		pos = str.find(src, pos_begin);
	}
	if (pos_begin < str.length())
	{
		ret.append(str.begin() + pos_begin, str.end());
	}
	return ret;
}
int NetUtility::getCurrentYear()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	return ((int)ptm->tm_year + 1900);
}

int NetUtility::getCurrentMouth()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	return ((int)ptm->tm_mon + 1);
}

int NetUtility::getCurrentDay()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	return ((int)ptm->tm_mday);
}
int NetUtility::getCurrentDate()
{
	auto tt = std::chrono::system_clock::to_time_t
	(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, "%d%02d%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday);
	 int result=atoi(std::string(date).c_str());
	 return result;
}
int NetUtility::getCurrentHour()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	return ((int)ptm->tm_hour);
}
int NetUtility::getCurrentMunite()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	return ((int)ptm->tm_min);
}
int NetUtility::getCurrentSeccond()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	return ((int)ptm->tm_sec);
}

std::string NetUtility::getCurrentSystemTime()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, "%d-%02d-%02d-%02d:%02d:%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}
std::string NetUtility::getCurrentSystemTimeStand()
{
	auto tt = std::chrono::system_clock::to_time_t
	(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}
std::string NetUtility::getCurrentSystemTimeGMT()
{
	time_t rawTime;
	struct tm* timeInfo;
	char szTemp[30] = { 0 };
	time(&rawTime);
	timeInfo = gmtime(&rawTime);
	strftime(szTemp, sizeof(szTemp), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
	return std::string(szTemp);
}
std::string NetUtility::getCurrentSystemDate()
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, "%d%02d%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}

int NetUtility::ConvertToDate(const char * str_time,const char * format)
{
	time_t time = ConvertStrToTm(str_time,format);
	return ConvertToDate(time);
}
int NetUtility::ConvertToDate(time_t time)
{
	struct tm* ptm = localtime(&time);
	char date[60] = { 0 };
	sprintf(date, "%d%02d%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday);
	int result = atoi(std::string(date).c_str());
	return result;
}
time_t strtotime(char* const date, char* const format = "%Y%m%d%H%M%S")
{
	return 0;
}

string   timetodate(time_t const timer)
{
	struct tm *l = localtime(&timer);

	char buf[128];
	snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d", l->tm_year + 1900, l->tm_mon + 1, l->tm_mday, l->tm_hour, l->tm_min, l->tm_sec);
	string s(buf);
	return s;

}
time_t NetUtility::ConvertStrToTm(const char * str_time,const char* format)
{

	struct tm tt;
	memset(&tt, 0, sizeof(tt));
#if _WIN32
	strftime((char*)str_time, 64, format, &tt);
#else
	strptime(str_time, format, &tt);

#endif
	return mktime(&tt);
}


//去除字符串中的所有c字符
void NetUtility::removeAll(std::string &str, char c)
{
	std::string::iterator new_end = std::remove_if(str.begin(), str.end(), std::bind2nd(std::equal_to<char>(), c));
	str.erase(new_end, str.end());
}

std::string NetUtility::IntToStringFormat(int data, int length)
{
	char buffer[] = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	std::string check = "%0";
	check.append(std::to_string(length));
	check.append("d");
	sprintf(buffer, check.c_str(), data);
	std::string result (buffer,length);
	return result;
}

using namespace std;

char NetUtility::Char2Int(char ch) {
	if (ch >= '0' && ch <= '9')return (char)(ch - '0');
	if (ch >= 'a' && ch <= 'f')return (char)(ch - 'a' + 10);
	if (ch >= 'A' && ch <= 'F')return (char)(ch - 'A' + 10);
	return -1;
}

char NetUtility::Str2Bin(char *str) {
	char tempWord[2];
	char chn;

	tempWord[0] = Char2Int(str[0]);                                //make the B to 11 -- 00001011
	tempWord[1] = Char2Int(str[1]);                                //make the 0 to 0  -- 00000000

	chn = (tempWord[0] << 4) | tempWord[1];                //to change the BO to 10110000

	return chn;
}
int NetUtility::php_htoi(char *s)
{
	int value;
	int c;

	c = ((unsigned char *)s)[0];
	if (isupper(c))
		c = tolower(c);
	value = (c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10) * 16;

	c = ((unsigned char *)s)[1];
	if (isupper(c))
		c = tolower(c);
	value += c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;

	return (value);
}

std::string NetUtility::urldecode(std::string &str_source)
{
	char const *in_str = str_source.c_str();
	int in_str_len = strlen(in_str);
	int out_str_len = 0;
	std::string out_str;
	char *str;

	str = _strdup(in_str);
	char *dest = str;
	char *data = str;

	while (in_str_len--) {
		if (*data == '+') {
			*dest = ' ';
		}
		else if (*data == '%' && in_str_len >= 2 && isxdigit((int) *(data + 1))
			&& isxdigit((int) *(data + 2))) {
			*dest = (char)php_htoi(data + 1);
			data += 2;
			in_str_len -= 2;
		}
		else {
			*dest = *data;
		}
		data++;
		dest++;
	}
	*dest = '\0';
	out_str_len = dest - str;
	out_str = str;
	free(str);
	return out_str;
}

std::string NetUtility::intToBytes(int value)
{
	std::string ary("0000", 4);
	ary[3] = (unsigned char)((value & 0xFF000000) >> 24);
	ary[2] = (unsigned char)((value & 0x00FF0000) >> 16);
	ary[1] = (unsigned char)((value & 0x0000FF00) >> 8);
	ary[0] = (unsigned char)((value & 0x000000FF));
	return ary;
}
int NetUtility::bytesToInt(char ary[], int offset)
{
	int value;
	value = (int)((ary[offset] & 0xFF)
		| ((ary[offset + 1] << 8) & 0xFF00)
		| ((ary[offset + 2] << 16) & 0xFF0000)
		| ((ary[offset + 3] << 24) & 0xFF000000));
	return value;
}


int NetUtility::rand(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}