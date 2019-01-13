//saod_4 hashing algorythms
//task 9: 1500 elements, open hashing, key format - "LDDDDL" (Letter/Digit)

#include "pch.h"
#include <iostream>	//cin, cout
#include <fstream>	//ofstream
#include <ctime>	//time()
#include <cstdlib>	//rand()

const int size = 1500;	//number of elements
const int keysize = 7;	//one more that key lenght for null terminator
const char tablefile[] = "hashtable.txt";	//name of table file
const char collifile[] = "collisions.txt";	//name of collisions file

struct element
{
	char key[keysize] = { '0' };
	element *collision = NULL;
};

void randomkey(char(&)[keysize]);
bool checkkey(char(&)[keysize]);
bool compkey(char(&)[keysize], char(&)[keysize]);
int hash(char(&)[keysize]);
bool addelement(element*[size], char(&)[keysize]);
bool delelement(element*[size], char(&)[keysize]);
void cleartable(element*[size]);
void rfilltable(element*[size]);
void printtable(element*[size]);
void input(int(&));
void inputkey(char(&)[keysize]);
void exporttable(element*[size]);
void exportcolli(element*[size]);

int main()
{
	srand(time(NULL));
	element *hashtable[size] = { NULL };
	element *temp;
	char key[keysize];
	int index;
	int menu;
	while (true)
	{
		system("cls");
		std::cout << "Main menu:\n"
			"1. Add random elements.\n"
			"2. Add element.\n"
			"3. Delete element.\n"
			"4. Find element by key.\n"
			"5. Find element by index.\n"
			"6. Clear hashtable.\n"
			"7. Print table.\n"
			"8. Export table to file.\n"
			"9. Export collision table to file.\n"
			"0. Exit.\n\n"
			"Option: ";
		input(menu);
		switch (menu)
		{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			rfilltable(hashtable);
			std::cout << "Filled hashtable with random keys.\n";
			system("pause");
			break;
		}
		case 2:
		{
			std::cout << "Enter a key: ";
			inputkey(key);
			addelement(hashtable, key);
			system("pause");
			break;
		}
		case 3:
		{
			std::cout << "Enter a key: ";
			inputkey(key);
			delelement(hashtable, key);
			system("pause");
			break;
		}
		case 4:
		{
			std::cout << "Enter a key: ";
			inputkey(key);
			temp = hashtable[hash(key)];
			int count = 0;
			while (temp != NULL)
			{
				if (compkey(temp->key, key))
				{
					++count;
				}
				temp = temp->collision;
			}
			if (count)
			{
				std::cout << (hash(key) + 1) << ".\t -> " << key << "\n";
			}
			else
			{
				std::cout << "Element not found.\n";
			}
			system("pause");
			break;
		}
		case 5:
		{
			std::cout << "Enter index: ";
			do
			{
				input(index);
			} while (index < 1 || index > size);
			temp = hashtable[index - 1];
			std::cout << index << ".\t-> ";
			while (temp != NULL)
			{
				std::cout << (temp->key) << " -> ";
				temp = temp->collision;
			}
			std::cout << "NULL\n";
			system("pause");
			break;
		}
		case 6:
		{
			cleartable(hashtable);
			std::cout << "Hashtable cleared";
			system("pause");
			break;
		}
		case 7:
		{
			printtable(hashtable);
			system("pause");
			break;
		}
		case 8:
		{
			exporttable(hashtable);
			system("pause");
			break;
		}
		case 9:
		{
			exportcolli(hashtable);
			system("pause");
			break;
		}
		default:
		{
			std::cout << "Wrong input.\n";
			system("pause");
			break;
		}
		}
	}
}

void randomkey(char(&key)[keysize])
{
	key[0] = 'A' + (rand() % ('Z' - 'A'));
	key[1] = '0' + (rand() % ('9' - '0'));
	key[2] = '0' + (rand() % ('9' - '0'));
	key[3] = '0' + (rand() % ('9' - '0'));
	key[4] = '0' + (rand() % ('9' - '0'));
	key[5] = 'A' + (rand() % ('Z' - 'A'));
	key[6] = '\0';
}

bool checkkey(char(&key)[keysize])
{
	if (key[0] > 'Z' || key[0] < 'A')
	{
		return 0;
	}
	if (key[1] > '9' || key[1] < '0')
	{
		return 0;
	}
	if (key[2] > '9' || key[2] < '0')
	{
		return 0;
	}
	if (key[3] > '9' || key[3] < '0')
	{
		return 0;
	}
	if (key[4] > '9' || key[4] < '0')
	{
		return 0;
	}
	if (key[5] > 'Z' || key[5] < 'A')
	{
		return 0;
	}
	return 1;
}

bool compkey(char(&key1)[keysize], char(&key2)[keysize])
{
	for (int i = 0; i < keysize; ++i)
	{
		if (key1[i] != key2[i])
		{
			return 0;
		}
	}
	return 1;
}

int hash(char (&key)[keysize])
{
	return
		(
			(
			(int)key[0] * (int)key[0] +
			(int)key[1] * (int)key[1] +
			(int)key[2] * (int)key[2] +
			(int)key[3] * (int)key[3] +
			(int)key[4] * (int)key[4] +
			(int)key[5] * (int)key[5] -
			17666
				) % size
			);
}

bool addelement(element *table[size], char (&key)[keysize])
{
	element *temp = new element;
	for (int i = 0; i < keysize; ++i)
	{
		temp->key[i] = key[i];
	}
	temp->collision = table[hash(key)];
	table[hash(key)] = temp;
	return 1;
}

bool delelement(element *table[size], char(&key)[keysize])
{
	element *temp = table[hash(key)];
	element *prev = table[hash(key)];
	if (compkey(temp->key, key))
	{
		table[hash(key)] = table[hash(key)]->collision;
		delete temp;
		return 1;
	}
	while (temp != NULL)
	{
		if (compkey(temp->key, key))
		{
			prev->collision = temp->collision;
			delete temp;
			return 1;
		}
		prev = temp;
		temp = temp->collision;
	}
	return 0;
}

void cleartable(element *table[size])
{
	for (int i = 0; i < size; ++i)
	{
		table[i] = NULL;
	}
}

void rfilltable(element *table[size])
{
	cleartable(table);
	char temp[keysize];
	for (int i = 0; i < size; ++i)
	{
		randomkey(temp);
		addelement(table, temp);
	}
}

void printtable(element *table[size])
{
	element *temp;
	for (int i = 0; i < size; ++i)
	{
		temp = table[i];
		std::cout << i + 1 << ".\t-> ";
		while (temp != NULL)
		{
			std::cout << (temp->key) << " -> ";
			temp = temp->collision;
		}
		std::cout << "NULL\n";
	}
}

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

void inputkey(char(&key)[keysize])
{
	while (true)
	{
		std::cin >> key;
		//key[6] = '0' may be used to avoid next check and return valid key
		if (key[6] != '\0')
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		if (!checkkey(key))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		return;
	}
}

void exporttable(element *table[size])
{
	std::ofstream output;
	output.open(tablefile);
	element *temp;
	for (int i = 0; i < size; ++i)
	{
		temp = table[i];
		output << i + 1 << ".\t";
		while (temp != NULL)
		{
			output << (temp->key) << "\t";
			temp = temp->collision;
		}
		output << "\n";
	}
	output.close();
}

void exportcolli(element *table[size])
{
	std::ofstream output;
	output.open(collifile);
	element *temp;
	int count = 0;
	for (int i = 0; i < size; ++i)
	{
		temp = table[i];
		output << i + 1 << "\t";
		while (temp != NULL)
		{
			++count;
			temp = temp->collision;
		}
		output << count << "\n";
		count = 0;
	}
	output.close();
}