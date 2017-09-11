/************************************************************
 * FileName: DBCommon.h
 * Author: 毛自豪
 * Version : V0.1
 * Date: 2015年09月02日 17:12:28
 * Description: 数据服务器常用的基本操作
 *
 ***********************************************************/
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace DBProduce
{
	class DBCommon
	{
		public:
			DBCommon();
			virtual ~DBCommon();

			static  std::string get_file_contents(const char *filename);
			 static std::string trim(const std::string& str);
			 static int split(const std::string& str,
			        std::vector<std::string>& ret_, std::string sep = ",");
			 static std::string replace(const std::string& str,
			        const std::string& src, const std::string& dest);
			
	};

}
