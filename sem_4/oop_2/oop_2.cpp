// oop_2.cpp : task 2
// create t_end_d class containing current time and date, that has output method

#include "pch.h"
#include <iostream>
#include <ctime>

class t_end_d
{
private:
	time_t startTime;
public:
	t_end_d();
	t_end_d(time_t);
	t_end_d(const t_end_d(&));
	~t_end_d();
	void print();
};

int main()
{
	t_end_d timedate1 = t_end_d();
	t_end_d timedate2 = t_end_d(time(nullptr));
	t_end_d timedate3 = t_end_d(timedate1);
	std::cout << "Default t_end_d values: \n";
	timedate1.print();
	std::cout << "Current system time t_end_d: \n";
	timedate2.print();
	std::cout << "Copied t_end_d: \n";
	timedate3.print();
	return 0;
}

t_end_d::t_end_d()
{
	startTime = 0;
}

t_end_d::t_end_d(time_t time)
{
	startTime = time;
}

t_end_d::t_end_d(const t_end_d &time)
{
	startTime = time.startTime;
}

t_end_d::~t_end_d()
{

}

void t_end_d::print()
{
	char timestr[26];
	ctime_s(timestr, sizeof timestr, &startTime);
	std::cout << "Time of class creation:\n" << timestr << "\n";
	//time_t currTime = time(nullptr);
	//ctime_s(timestr, sizeof timestr, &currTime);
	//std::cout << "Current time:\n" << timestr << "\n";
}