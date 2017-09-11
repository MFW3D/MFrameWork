#include "TimeSpan.h"

TimeSpan::TimeSpan(int _day, int _hours, int _munites, int _secconds)
{
	days = _day;
	hours = _hours;
	munites = _munites;
	secconds = _secconds;
}

TimeSpan::TimeSpan()
{

}
TimeSpan TimeSpan::operator - (const TimeSpan& timeSpan)
{
	TimeSpan t = *this;
	t.days -= timeSpan.days;
	t.hours -= timeSpan.hours;
	t.munites -= timeSpan.munites;
	t.secconds -= timeSpan.secconds;
	return t;
}
int TimeSpan::GetDays()
{
	return days;
}
int TimeSpan::GetHours()
{
	return hours;
}
int TimeSpan::GetMunites()
{
	return munites;
}
int TimeSpan::GetSecconds()
{
	return secconds;
}

int TimeSpan::SetDays(int _days)
{
	return days = _days;
}
int TimeSpan::SetHours(int _hours)
{
	return hours = _hours;
}
int TimeSpan::SetMunites(int _munites)
{
	return munites = _munites;
}
int TimeSpan::SetSecconds(int _secconds)
{
	return secconds = _secconds;
}

int TimeSpan::AddDays(int _days)
{
	return days += _days;
}
int TimeSpan::AddHours(int _hours)
{
	int teamp = hours + _hours;
	int day = teamp / 24;
	int hour = teamp % 24;
	if (day != 0)
	{
		AddDays(day);
		SetHours(hour);
	}
	else
	{
		int _hour = GetHours() + _hours;
		SetHours(_hour);
	}
	return GetHours();
}
int TimeSpan::AddMunites(int _munites)
{
	int teamp = munites + _munites;
	int hour = teamp / 60;
	int mu = teamp % 60;
	if (hour != 0)
	{
		AddHours(hour);
		SetMunites(mu);
	}
	else
	{
		int _munite = GetMunites() + _munites;
		SetMunites(_munite);
	}
	return GetMunites();
}
int TimeSpan::AddSecconds(int _secconds)
{
	int teamp = secconds + _secconds;
	int mu = teamp / 60;
	int sec = teamp % 60;
	if (mu != 0)
	{
		AddMunites(mu);
		SetSecconds(sec);
	}
	else
	{
		int _sec = GetSecconds() + _secconds;
		SetSecconds(_sec);

	}
	return GetSecconds();
}

std::string TimeSpan::ToString()
{
	std::string result = "";
	char buffer[3];
	sprintf(buffer, "%02d", GetHours());
	result.append(std::string(buffer) + ":");
	sprintf(buffer, "%02d", GetMunites());
	result.append(std::string(buffer) + ":");
	sprintf(buffer, "%02d", GetSecconds());
	result.append(std::string(buffer));
	return result;
}
std::string TimeSpan::ToStringAll()
{
	std::string result = "";
	char buffer[3];
	if (days != 0)
		result.append(std::to_string(GetDays()) + " ");
	sprintf(buffer, "%02d", GetHours());
	result.append(std::string(buffer) + ":");
	sprintf(buffer, "%02d", GetMunites());
	result.append(std::string(buffer) + ":");
	sprintf(buffer, "%02d", GetSecconds());
	result.append(std::string(buffer));
	return result;
}