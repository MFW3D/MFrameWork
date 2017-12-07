#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <chrono>
#include <algorithm>
#include <functional>
#include <wchar.h>

#include <random>
#include "uv.h"

#define CHRONO_SYSTEM_NOW()   (std::chrono::time_point_cast<std::chrono::milliseconds>(SystemTimePoint::clock::now()).time_since_epoch().count())
#define CHRONO_SYSTEM_NOW_MICRO() (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count())


class NetUtility
{
private:
public:
	/*合并后n1占高32位，n2占低32位*/
	static unsigned long long CombineInt32(unsigned long n1,int n2);
	/*拆解后n1值高32位，n2值低32位*/
	static void SplitLongLong(unsigned long& n1,int& n2, long long l);
	/*ip int 和string类型的转换*/
	static int iptoint(  const char *ipstr);
	static std::string inttoip(unsigned int ipint);
	static void GetIpPort(uv_tcp_t* client, unsigned long& ip, int& port);
	static void GetIpPort(uv_udp_t* client, unsigned long& ip, int& port);
	static std::string BinToHex(const std::string &strBin, bool bIsUpper=false);
	static std::string HexToBin(const std::string &strHex);

	static std::string ws2s(const std::wstring& ws);

	static std::wstring s2ws(const std::string& s);

	static std::wstring UTF2Uni(const char* src, std::wstring &t);
	static std::string UTF2Uni(const char* src, std::string &t);

	static int Uni2UTF(const std::wstring& strRes, char *utf8, int nMaxSize);

	static std::string s2utfs(const  std::string&  strSrc);

	static std::string  utfs2s(const std::string& strutf);

	static std::string get_file_contents(const char *filename);
	static std::string trim(const std::string& str);
	static int split(const std::string& str,
		std::vector<std::string>& ret_, std::string sep = ",");
	static std::string replace(const std::string& str,
		const std::string& src, const std::string& dest);
	//时间操作
	static int getCurrentYear();
	static int getCurrentMouth();
	static int getCurrentDay();
	static int getCurrentHour();
	static int getCurrentMunite();
	static int getCurrentSeccond();
	//获取当天日期int：例如20170603
	static int getCurrentDate();
	static int ConvertToDate(const char * str_time, const char * format);
	static int ConvertToDate(time_t time);

	static std::string getCurrentSystemTime();
	static std::string getCurrentSystemDate();
	static std::string getCurrentSystemTimeStand();
	static std::string getCurrentSystemTimeGMT();
	static time_t ConvertStrToTm(const char * str_time, const char* format );

	//去除字符串中的所有c字符
	static void removeAll(std::string &str, char c);

	static std::string IntToStringFormat(int data, int length);

	static char Char2Int(char ch);

	static char Str2Bin(char *str);
	static int php_htoi(char *s);
	static std::string UrlEncode(const std::string& str);
	static std::string urldecode(std::string &str_source);

	static std::string intToBytes(int value);
	static int bytesToInt(char ary[], int offset);

	static int rand(int min, int max);

};