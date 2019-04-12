// oop_3.cpp : task 4
// complex number class in polar form

#include "pch.h"
#include <cmath>
#include <string>
#include <iostream>

constexpr double PI = 3.14159265359;

class complex
{
private:
	double rad;
	double ang;
	double recta(complex);	//gets real part of complex number
	double rectb(complex);	//gets imaginary part of comlex number
	double polr(double, double);
	double pola(double, double);
	double crad(double);
public:
	complex();
	complex(double, double);
	complex(const complex (&));
	complex(std::string);
	~complex();
	complex operator+(complex);
	complex operator-(complex);
	complex operator*(complex);
	complex operator/(complex);
	bool operator==(complex);
	bool operator!=(complex);
	bool operator>(complex);
	bool operator<(complex);
	bool operator>=(complex);
	bool operator<=(complex);
	std::string tostr();
};

int main()
{
    std::cout << "Hello World!\n"; 
}

complex::complex()
{
	rad = 0;
	ang = 0;
}

complex::complex(double r, double a)
{
	rad = r;
	ang = a;
}

complex::complex(std::string s)
{
	size_t pos = s.find(',');
	if (pos != std::string::npos)
	{
		std::string b = s;
		s.erase(s.begin() + pos, s.end());
		rad = std::stod(s);
		s = b;
		s.erase(s.begin(), s.begin() + pos);
		ang = std::stod(s);
	}
	else
	{
		rad = 0;
		ang = 0;
	}
}

complex::complex(const complex &c)
{
	rad = c.rad;
	ang = c.ang;
}

complex::~complex()
{

}

double complex::recta(complex c)
{
	return (c.rad * cos(c.ang));
}

double complex::rectb(complex c)
{
	return (c.rad * sin(c.ang));
}

double complex::polr(double a, double b)
{
	return (sqrt((a * a) + (b * b)));
}

double complex::pola(double a, double b)
{
	return (atan2(a, b));
}

double complex::crad(double r)
{
	double rad = r;
	while ((rad - (2 * PI)) >= 0)
	{
		rad -= 2 * PI;
	}
	while ((rad + (2 * PI)) <= 0)
	{
		rad += 2 * PI;
	}
	return rad;
}

complex complex::operator+(complex c)
{
	double a = recta(*this);
	double b = rectb(*this);
	a += recta(c);
	b += recta(c);
	return (complex(polr(a, b), pola(a, b)));
}

complex complex::operator-(complex c)
{
	double a = recta(*this);
	double b = rectb(*this);
	a -= recta(c);
	b -= recta(c);
	return (complex(polr(a, b), pola(a, b)));
}

complex complex::operator*(complex c)
{
	return (complex((this->rad * c.rad), (crad(this->ang + c.ang))));
}

complex complex::operator/(complex c)
{
	return (complex((this->rad / c.rad), (crad(this->ang - c.ang))));
}

bool complex::operator==(complex c)
{
	return ((this->rad == c.rad) && (this->ang == c.ang)) ? 1 : 0;
}

bool complex::operator!=(complex c)
{
	return ((this->rad == c.rad) && (this->ang == c.ang)) ? 0 : 1;
}

bool complex::operator>(complex c)
{
	return (this->rad > c.rad) ? 1 : 0;
}

bool complex::operator<(complex c)
{
	return (this->rad < c.rad) ? 1 : 0;
}

bool complex::operator>=(complex c)
{
	return (this->rad >= c.rad) ? 1 : 0;
}

bool complex::operator<=(complex c)
{
	return (this->rad <= c.rad) ? 1 : 0;
}

std::string complex::tostr()
{
	std::string s = "";
	s += std::to_string(rad);
	s += ", ";
	s += std::to_string(ang);
	return s;
}