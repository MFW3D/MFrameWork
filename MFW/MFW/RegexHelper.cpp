#include "RegexHelper.h"

bool RegexHelper::Regex_Email(const std::string& email)
{
	if (regex_match(email, pattern_Email))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void RegexHelper::init()
{
	pattern_Email = std::regex("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");

}

bool RegexHelper::Search(const std::string& src, const  std::string& parttern, std::vector<std::string>& res)
{
	std::regex reg(parttern);
	auto words_begin =
		std::sregex_iterator(src.begin(), src.end(), reg);
	auto words_end = std::sregex_iterator();
	res.clear();
	for (std::sregex_iterator i = words_begin; i != words_end; ++i)
	{
		std::smatch match = *i;
		std::string match_str = match.str();
		res.push_back(match_str);
	}
	if (res.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}