// saod_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

void arrayfill(int* array, int len);
int negsum(int* array, int len);
int evencount(int* array, int len);
int dignum(int num);

int main()
{
	srand(time(NULL));
	int len;
	printf("Input array length: ");
	std::cin >> len;
	int* array = new int[len];
	arrayfill(array, len);
	int option = 0;
	while (option != 5)
	{
		system("cls");
		printf("Input an option: \n");
		printf("1. Calculate sum of negative elements.\n");
		printf("2. Calculate number of even elements.\n");
		printf("3. Output the array.\n");
		printf("4. Generate new array.\n");
		printf("5. Exit\n");
		std::cin >> option;
		switch (option)
		{
		case 1:
		{
			printf("Sum of negative elements: %i \n", negsum(array, len));
			system("pause");
			break;
		}
		case 2:
		{
			printf("Number of even elements: %i \n", evencount(array, len));
			system("pause");
			break;
		}
		case 3:
		{
			printf("Generated array: \n");
			for (int i = 0; i < len; ++i)
			{

				printf("%*i", (dignum(len) + 1), array[i]);
			}
			printf("\n");
			system("pause");
			break;
		}
		case 4:
		{
			printf("Input array length: ");
			std::cin >> len;
			arrayfill(array, len);
			system("pause");
			break;
		}
		case 5:
		{
			break;
		}
		default:
		{
			printf("Wrong input.\n");
			system("pause");
			break;
		}
		break;
		}
	}
	return 0;
}

void arrayfill(int* array, int len)
{
	for (int i = 0; i < len; ++i)
	{
		array[i] = rand() % len - ((len / 2) - 1);
	}
}

int negsum(int* array, int len)
{
	int sum = 0;
	for (int i = 0; i < len; ++i)
	{
		if (array[i] < 0)
		{
			sum += array[i];
		}
	}
	return sum;
}

int evencount(int* array, int len)
{
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		if (!(array[i] % 2))
			++count;
	}
	return count;
}

int dignum(int num)
{
	int count = 0;
	while (num != 0)
	{
		num /= 10;
		++count;
	}
	return count;
}