//saod_5 sorting algorythms
//task 9: find number of different elements. sort by merging.

#include "pch.h"
#include <iostream>	//for cout and cin;
#include <vector>	//for vector
#include <ctime>	//for time;
#include <cstdlib>	//for rand;

class list
{
public:
	void print();
	void addnumber(int);
	bool deletenumber(int);
	void generate(int);
	void mergesort();
	int uniquenumbers();
protected:
	int swapcount = 0;
	int compcount = 0;
private:
	int find(int);
	int size();
	std::vector<int> numbers;
	std::vector<int> sort(std::vector<int>);
	std::vector<int> merge(std::vector<int>, std::vector<int>);
};

void input(int(&));

int main()
{
	srand(time(NULL));
	list array;
	int menu = 0;
	int temp;
	while (true)
	{
		system("cls");
		std::cout << "Main menu:\n"
			"0. Sort elements.\n"
			"1. Generate random elements.\n"
			"2. Add element.\n"
			"3. Delete element.\n"
			"4. Print all elements and info.\n"
			"5. Exit.\n\n"
			"Option: ";
		input(menu);
		switch (menu)
		{
		case 0:
			array.mergesort();
			std::cout << "Sort complete.\n";
			std::cout << '\n';
			system("pause");
			break;
		case 1:
			std::cout << "Input number of elements: ";
			input(temp);
			array.generate(temp);
			std::cout << "Generated " << temp << " elements.\n";
			std::cout << '\n';
			system("pause");
			break;
		case 2:
			std::cout << "Input an element: ";
			input(temp);
			array.addnumber(temp);
			std::cout << "Element " << temp << " added.\n";
			std::cout << '\n';
			system("pause");
			break;
		case 3:
			std::cout << "Input an element: ";
			input(temp);
			if (!array.deletenumber(temp))
			{
				std::cout << "All instances of " << temp << " deleted.\n";
			}
			else
			{
				std::cout << "No instances of " << temp << " found.\n";
			}
			std::cout << '\n';
			system("pause");
			break;
		case 4:
			array.print();
			std::cout << '\n';
			system("pause");
			break;
		case 5:
			std::cout << "Exiting...\n";
			return 0;
		default:
			std::cout << "Wrong input. Try again.";
			std::cout << '\n';
			system("pause");
		}
	}
}

//prints all elements and number of swaps and comparisons.
void list::print()
{
	std::cout << "Elements:\n\n";
	for (int i = 0; i < size(); ++i)
	{
		std::cout << numbers[i] << "\t";
	}
	std::cout << "\n\nNumber of comparisons: " << compcount <<
		"\nNumber of swaps: " << swapcount <<
		"\nNumber of unique elements: " << uniquenumbers() << "\n";

}

//adds given element and sorts vector again.
void list::addnumber(int num)
{
	numbers.push_back(num);
	swapcount = 0;
	compcount = 0;
}

//deletes given element.
bool list::deletenumber(int num)
{
	int pos = find(num);
	if (pos == -1)
	{
		return 0;
	}
	numbers.erase(numbers.begin() + pos);
	if (!deletenumber(num))
	{
		swapcount = 0;
		compcount = 0;
		return 1;
	}
	return 0;
}

//generates a new random vector of given size
void list::generate(int size)
{
	numbers.clear();
	swapcount = 0;
	compcount = 0;
	for (int i = 0; i < size; ++i)
	{
		numbers.push_back(rand() % size);
	}
}

//sorts vector using merge sort method.
void list::mergesort()
{
	swapcount = 0;
	compcount = 0;
	numbers = sort(numbers);
}

int list::uniquenumbers()
{
	int count = 0;
	bool check;
	for (int i = 0; i < size(); ++i)
	{
		check = 0;
		for (int j = (i + 1); j < size(); ++j)
		{
			if (numbers[i] == numbers[j])
			{
				check = 1;
			}
		}
		if (!check)
		{
			++count;
		}
	}
	return count;
}

//returns position of first instance of given element. return -1 if there's none
int list::find(int num)
{
	int pos = 0;
	while (pos < size())
	{
		if (numbers[pos] == num)
		{
			return pos;
		}
		++pos;
	}
	return -1;
}

int list::size()
{
	return numbers.size();
}

//splits vector in halves until they are a single number and then merges back
//sorted from smallest to largest element.
std::vector<int> list::sort(std::vector<int> a)
{
	if (a.size() == 1)
	{
		return a;
	}
	std::vector<int> v1;
	std::vector<int> v2;
	unsigned int i = 0;
	for (; ((i * 2) < a.size()); ++i)
	{
		v1.push_back(a[i]);
	}
	for (; i < a.size(); ++i)
	{
		v2.push_back(a[i]);
	}
	v1 = sort(v1);
	v2 = sort(v2);
	return merge(v1, v2);
}

//merges elements contained in both input vectors into 1, sorted from smallest
//element to largest.
std::vector<int> list::merge(std::vector<int> v1, std::vector<int> v2)
{
	std::vector<int> c;
	while (v1.size() && v2.size())
	{
		++compcount;
		if (v1[0] <= v2[0])
		{
			++swapcount;
			c.push_back(v1[0]);
			v1.erase(v1.begin());
		}
		else
		{
			++swapcount;
			c.push_back(v2[0]);
			v2.erase(v2.begin());
		}
	}
	while (v1.size())
	{
		++swapcount;
		c.push_back(v1[0]);
		v1.erase(v1.begin());
	}
	while (v2.size())
	{
		++swapcount;
		c.push_back(v2[0]);
		v2.erase(v2.begin());
	}
	return c;
}

//contantly asks for input until an integer is entered.
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