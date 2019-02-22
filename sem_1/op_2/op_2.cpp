// op_2.cpp : number sequence processing (with stl)
// task 14: in a one dimensional array calculate:
// 1. number of elements equal to 0
// 2. sum of elements after smallest element
// sort elements by their modules

#include "pch.h"
#include <iostream>	//std::cout, std::cin
#include <vector>	//std::vector<>
#include <cmath>	//std::abs()
#include <ctime>	//std::time()
#include <cstdlib>	//std::rand()

int input_int(int, int);
double input_double();
void modsort(std::vector<double>(&));
void randomvector(std::vector<double>(&), unsigned int);
void printvector(std::vector<double>(&));

int main()
{
	srand(time(NULL));
	std::vector<double> numbers;
	int input;
	unsigned int size;
	while (true)
	{
		system("cls");
		std::cout << "Choose an option:\n"
			"1. Input array manually.\n"
			"2. Generate random array.\n"
			"3. Sort array.\n"
			"4. Print array and information.\n"
			"0. Exit.\n";
		input = input_int(0, 4);
		switch (input)
		{
		case 0:
			return 0;
		case 1:
			numbers.clear();
			system("cls");
			std::cout << "Input number of elements: ";
			size = input_int(1, 256);
			double dinput;
			for (unsigned int i = 0; i < size; ++i)
			{
				system("cls");
				std::cout << "Input element #" << i + 1 << ".\n";
				dinput = input_double();
				numbers.push_back(dinput);
			}
			system("pause");
			break;
		case 2:
			system("cls");
			std::cout << "Input number of elements: ";
			size = input_int(1, 256);
			randomvector(numbers, size);
			system("cls");
			system("pause");
			break;
		case 3:
			system("cls");
			if (!numbers.size())
			{
				std::cout << "Array is empty.\n";
				system("pause");
				break;
			}
			modsort(numbers);
			system("pause");
			break;
		case 4:
			system("cls");
			if (!numbers.size())
			{
				std::cout << "Array is empty.\n";
				system("pause");
				break;
			}
			printvector(numbers);
			system("pause");
			break;
		default:
			continue;
		}
	}
}

int input_int(int min, int max)
{
	bool flag = 0;
	int integer;
	while (true)
	{
		std::cin >> integer;
		if (std::cin.fail())
		{
			++flag;
		}
		else if (std::cin.peek() != '\n')
		{
			++flag;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (flag)
		{
			std::cout << "Incorrect input. Input must be an integer.\n"
				"Try again: ";
			flag = 0;
			continue;
		}
		if ((integer > max) || (integer < min))
		{
			std::cout << "Incorrect input. Input must be between " << min << " and " << max << ".\n"
				"Try again: ";
			continue;
		}
		return integer;
	}
}

double input_double()
{
	bool flag = 0;
	double number;
	while (true)
	{
		std::cin >> number;
		if (std::cin.fail())
		{
			++flag;
		}
		else if (std::cin.peek() != '\n')
		{
			++flag;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (flag)
		{
			std::cout << "Incorrect input. Input must be a real value.\n"
				"Try again: ";
			flag = 0;
			continue;
		}
		return number;
	}
}

void modsort(std::vector<double> (&numbers))
{
	int minpos;
	double temp;
	for (unsigned int i = 0; i < numbers.size(); ++i)
	{
		minpos = i;
		for (unsigned int j = i + 1; j < numbers.size(); ++j)
		{
			if (abs(numbers[j]) < abs(numbers[minpos]))
			{
				minpos = j;
			}
		}
		temp = numbers[i];
		numbers[i] = numbers[minpos];
		numbers[minpos] = temp;
	}
}

void randomvector(std::vector<double> (&numbers), unsigned int size)
{
	numbers.clear();
	for (unsigned int i = 0; i < size; ++i)
	{
		numbers.push_back(rand() % 20000 - 10000);
		numbers[i] /= 100;
	}
}

void printvector(std::vector<double>(&numbers))
{
	unsigned int count = 0;
	unsigned int minpos = 0;
	double sum = 0;
	std::cout << "Vector content:\n";
	for (unsigned int i = 0; i < numbers.size(); ++i)
	{
		std::cout << numbers[i] << "\t";
		if (numbers[i] < numbers[minpos])
		{
			minpos = i;
		}
		if (numbers[i] == 0)
		{
			++count;
		}
	}
	for (unsigned int i = (minpos + 1); i < numbers.size(); ++i)
	{
		sum += numbers[i];
	}
	std::cout << "\nNumber of elements equal to 0: " << count << ".\n";
	if ((minpos + 1) == numbers.size())
	{
		std::cout << "Sum of elements after minimum element: no elements.\n";
	}
	else
	{
		std::cout << "Sum of elements after minumum element: " << sum << ".\n";
	}
	std::cout << "Position of minimum element: " << (minpos + 1) << ".\n";
}