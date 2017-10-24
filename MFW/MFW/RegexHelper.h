#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <regex> 
#include <vector>

#include "Singleton.h"

class RegexHelper:public MFW::Singleton<RegexHelper> {
private:
	std::regex pattern_Email;
public:
	//验证输入
	bool Regex_Email(const std::string& email);
	virtual void init();


	//查询
	bool Search(const std::string& src, const  std::string& parttern, std::vector<std::string>& res );
	//替换

};