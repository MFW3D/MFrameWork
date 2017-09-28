#pragma once
/*
算法：Base64
Base64编码要求把3个8位字节（3*8=24）转化为4个6位的字节（4*6=24），
、之后在6位的前面补两个0，形成8位一个字节的形式。 如果剩下的字符不足
3个字节，则用0填充，输出字符使用'='，因此编码后输出的文本末尾可能会
出现1或2个'='。
　　为了保证所输出的编码位可读字符，Base64制定了一个编码表，以便进行
  统一转换。编码表的大小为2^6=64，这也是Base64名称的由来。
*/
#include <iostream>
#include <string>
#include <string.h>

namespace MFWAlg {
	class Base64 {
		public:
			static std::string encodeBase64(unsigned char *input, int input_len);
			static std::string decodeBase64(std::string input);
			static int indexOfCode(const char c);
	};
}
