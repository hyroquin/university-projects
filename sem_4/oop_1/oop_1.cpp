// oop_1.cpp : task 4
// create date class with IsValid method.

#include "pch.h"
#include <iostream>

class date
{
private:
	int day;
	int month;
	int year;
public:
	date();	//constructor with default values
	~date();	//class destructor
	date(int, int, int);	//constructor overload for non default values
	bool isValid();	//check if date is valid
};

void input(int(&));

int main()
{
	int temp1, temp2, temp3;
	std::cout << "Enter a date:\n"
		"Day: ";
	input(temp1);
	std::cout << "Month: ";
	input(temp2);
	std::cout << "Year: ";
	input(temp3);
	date mydate(temp1, temp2, temp3);
	if (mydate.isValid())
	{
		std::cout << "This date is valid.";
	}
	else
	{
		std::cout << "This date is invalid.";
	}
	return 0;
}

//consturtor with default values.
date::date()
{
	day = 1;
	month = 1;
	year = 1900;
}

//construcotr with specified values.
date::date(int day, int month, int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

//empty destructor.
date::~date()
{

}

//returns 1 if date is valid, returns 0 if not.
bool date::isValid()
{
	if ((day > 31) ||
		((month == 2) && (day > 29)) || 
		((month == 4) && (day > 30)) || 
		((month == 6) && (day > 30)) || 
		((month == 9) && (day > 30)) || 
		((month == 11) && (day > 30)))
	{
		return 0;
	}
	if ((month == 2) && (day == 29))	//leap year check.
	{
		if ((year % 4) || (!(year % 100) && (year % 400)))
		{
			return 0;
		}
	}
	return 1;
}

//waits for integer input, ignores invalid inputs.
void input(int(&integer))
{
	while (true)
	{
		std::cin >> integer;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (std::cin.get() != '\n')
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		return;
	}
}