#include "DBCommon.h"
using namespace std;
namespace DBProduce
{
	DBCommon::DBCommon()
	{
	}
	DBCommon::~DBCommon()
	{
	}
	std::string DBCommon::get_file_contents(const char *filename)
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
	string DBCommon::trim(const string& str)
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
	int DBCommon::split(const string& str, vector<string>& ret_, string sep)
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
	string DBCommon::replace(const string& str, const string& src,
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
}
