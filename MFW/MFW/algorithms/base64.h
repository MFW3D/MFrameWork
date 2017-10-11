#pragma once
/*
�㷨��Base64
Base64����Ҫ���3��8λ�ֽڣ�3*8=24��ת��Ϊ4��6λ���ֽڣ�4*6=24����
��֮����6λ��ǰ�油����0���γ�8λһ���ֽڵ���ʽ�� ���ʣ�µ��ַ�����
3���ֽڣ�����0��䣬����ַ�ʹ��'='����˱����������ı�ĩβ���ܻ�
����1��2��'='��
����Ϊ�˱�֤������ı���λ�ɶ��ַ���Base64�ƶ���һ��������Ա����
  ͳһת���������Ĵ�СΪ2^6=64����Ҳ��Base64���Ƶ�������
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
