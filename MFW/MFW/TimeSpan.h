#pragma once
#include <string>
#include <map>
#include <chrono>
#include <mutex>
#include <atomic>
class TimeSpan
{
private:
	int days = 0;
	int hours = 0;
	int munites = 0;
	int secconds = 0;

public:
	//构建时间结构
	TimeSpan(int _day, int _hours, int _munites, int _secconds);


	TimeSpan();
	
	TimeSpan operator - (const TimeSpan& timeSpan);

	int GetDays();
	int GetHours();
	int GetMunites();
	int GetSecconds();

	int SetDays(int _days);
	int SetHours(int _hours);
	int SetMunites(int _munites);
	int SetSecconds(int _secconds);

	int AddDays(int _days);
	int AddHours(int _hours);
	int AddMunites(int _munites);
	int AddSecconds(int _secconds);

	std::string ToString();
	std::string ToStringAll();
};