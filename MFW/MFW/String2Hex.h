#pragma once 
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include "string.h"
using namespace std;
#define BINARYSIZE 204800
#define HEXSIZE 204800
class String2Hex
{
private:
	static char datas[BINARYSIZE];
	static char datasHex[HEXSIZE];
	static inline void Hex2Char(char *szHex, unsigned char *rch)
	{
		int i;
		for (i = 0; i < 2; i++)
		{
			if (*(szHex + i) >= '0' && *(szHex + i) <= '9')
				*rch = (*rch << 4) + (*(szHex + i) - '0');
			else if (*(szHex + i) >= 'a' && *(szHex + i) <= 'f')
				*rch = (*rch << 4) + (*(szHex + i) - 'a' + 10);
			else
				break;
		}
	}

	static inline void HexStr2CharStr(char *pszHexStr, int iSize, char *pucCharStr)
	{
		int i;
		unsigned char ch;
		if (iSize % 2 != 0) return;
		for (i = 0; i < iSize / 2; i++)
		{
			Hex2Char(pszHexStr + 2 * i, &ch);
			pucCharStr[i] = ch;
		}
	}

	static inline void Char2Hex(unsigned char ch, char *szHex)
	{
		int i;
		unsigned char byte[2];
		byte[0] = ch / 16;
		byte[1] = ch % 16;
		for (i = 0; i < 2; i++)
		{
			if (byte[i] >= 0 && byte[i] <= 9)
				szHex[i] = '0' + byte[i];
			else
				szHex[i] = 'a' + byte[i] - 10;
		}
		szHex[2] = 0;
	}
	static inline void CharStr2HexStr(char *pucCharStr, int iSize, char *pszHexStr)
	{
		int i;
		char szHex[3];
		pszHexStr[0] = 0;
		for (i = 0; i < iSize; i++)
		{
			Char2Hex(pucCharStr[i], szHex);
			strcat(pszHexStr, szHex);
		}
	}

public :
	static inline void Binary2Hex(std::string& bstr,std::string& hstr)
	{
		memset(datas, 0, BINARYSIZE);
		memset(datasHex, 0, HEXSIZE);
		hstr.clear();
		memcpy(datas, bstr.c_str(), bstr.length());
		CharStr2HexStr(datas, bstr.length(), datasHex);
		hstr.append(datasHex);
	}
	static inline void Hex2Binary(std::string& hstr,std::string& bstr )
	{
		memset(datas, 0, BINARYSIZE);
		memset(datasHex, 0, HEXSIZE);
		bstr.clear();
		memcpy(datasHex, hstr.c_str(), hstr.length());
		HexStr2CharStr(datasHex, hstr.length(), datas);
		for (int i = 0; i < hstr.length()/2; i++)
		{
			bstr += datas[i];
		}
	}

	static inline string BinToHex(const string &strBin, bool bIsUpper = false)
	{
		string strHex;
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

	static inline string HexToBin(const string &strHex)
	{
		if (strHex.size() % 2 != 0)
		{
			return "";
		}

		string strBin;
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
};
