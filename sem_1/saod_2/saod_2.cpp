// saod_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

struct node
{
	char letter;
	node *prev;
	node *next;
};

class dllist
{
	node *head, *tail;
public:
	dllist()
	{
		head = NULL;
		tail = NULL;
	}
	void createnode(char data)
	{
		node *temp = new node;
		temp->letter = data;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp->prev = NULL;
		}
		else
		{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}
	void deletenode(int pos)
	{
		node *temp = new node;
		temp = head;
		for (int i = 0; i < pos; ++i)
		{
			temp = temp->next;
		}
		if (pos == 0)
		{
			head = temp->next;
			temp->next->prev = temp->prev;
		}
		else
		{
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		delete(temp);
	}
	void process()
	{
		node *temp = new node;
		temp = head;
		int pos = 0;
		while (temp != tail)
		{
			if (temp->letter == '*')
			{
				if (pos == 0)
				{
					deletenode(pos);
					temp = temp->next;
				}
				else
				{
					deletenode(pos);
					temp = temp->prev;
					--pos;
					if (pos == 0)
					{
						deletenode(pos);
						temp = temp->next;
					}
					else
					{
						deletenode(pos);
						temp = temp->prev;
						--pos;
					}
				}
			}
			temp = temp->next;
			++pos;
		}
	}
	void display()
	{
		node *temp = new node;
		temp = head;
		while (temp != NULL)
		{
			printf("%c", temp->letter);
			temp = temp->next;
		}
	}
};

int main()
{
	printf("Special symbol is '*'\n");
	printf("Input the string: \n");
	std::string str;
	std::cin >> str;
	dllist list;
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		list.createnode(str.at(i));
	}
	list.process();
	printf("Processed string: \n");
	list.display();
	return 0;
}
