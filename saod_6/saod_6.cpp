//saod_6 AVL trees
//task 9: preorder traversal, divide by 2 nodes divisible by 4
//k(i) = |k(i)-k(i-1)| where k(i) - key of node i-th node in preorder traversal

#include "pch.h"
#include <iostream>

struct tree
{
	int key = 0;
	tree* left = NULL;
	tree* right = NULL;
	int h = 1;
	tree(int k)
	{
		key = k;
	}
};
 
void input(int(&));
int height(tree*);
int deltah(tree*);
void fixh(tree*);
tree* rotr(tree*);
tree* rotl(tree*);
tree* balance(tree*);
tree* insert(tree*, int);
tree* findmin(tree*);
tree* remove(tree*, int);
void print(tree*, int = 0);
bool found(tree*, int);
void search(tree*, int, int = 1);
void task1(tree*);
int _abs(int);
void task2_1(tree*);
int task2_2(tree*, int = 0);

int main()
{
	tree* root = NULL;
	int menu;
	while (true)
	{
		system("cls");
		std::cout << "Main menu:\n"
			"1. Add a node.\n"
			"2. Remove a node.\n"
			"3. Search for a node by key.\n"
			"4. Print the tree.\n"
			"5. Print the tree as a list.\n"
			"6. Do the task.\n"
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
			std::cout << "Enter a key: ";
			input(menu);
			if (found(root, menu))
			{
				std::cout << "Node with such key already exists.\n";
				system("pause");
				break;
			}
			root = insert(root, menu);
			system("pause");
			break;
		}
		case 2:
		{
			std::cout << "Enter a key: ";
			input(menu);
			if (found(root, menu))
			{
				root = remove(root, menu);
			}
			else
			{
				std::cout << "Node with such key doesn't exist.\n";
			}
			system("pause");
			break;
		}
		case 3:
		{
			std::cout << "Enter a key: ";
			input(menu);
			search(root, menu);
			system("pause");
			break;
		}
		case 4:
		{
			if (!root)
			{
				std::cout << "Tree is empty.\n";
			}
			else
			{
				print(root);
			}
			system("pause");
			break;
		}
		case 5:
		{
			if (!root)
			{
				std::cout << "Tree is empty.\n";
			}
			else
			{
				task1(root);
				std::cout << "\n";
			}
			system("pause");
			break;
		}
		case 6:
		{
			if (!root)
			{
				std::cout << "Tree is empty.\n";
			}
			else
			{
				task2_1(root);
				task2_2(root);
			}
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

int height(tree* r)
{
	return r ? r->h : 0;
}

int deltah(tree* r)
{
	return height(r->right) - height(r->left);
}

void fixh(tree* r)
{
	if (height(r->left) > height(r->right))
	{
		r->h = height(r->left) + 1;
	}
	else
	{
		r->h = height(r->right) + 1;
	}
}

tree* rotr(tree* r)
{
	tree* t = r->left;
	r->left = t->right;
	t->right = r;
	fixh(r);
	fixh(t);
	return t;
}

tree* rotl(tree* r)
{
	tree* t = r->right;
	r->right = t->left;
	t->left = r;
	fixh(r);
	fixh(t);
	return t;
}

tree* balance(tree* r)
{
	fixh(r);
	if (deltah(r) == 2)
	{
		if (deltah(r->right) < 0)
		{
			r->right = rotr(r->right);
		}
		return rotl(r);
	}
	if (deltah(r) == -2)
	{
		if (deltah(r->left) > 0)
		{
			r->left = rotl(r->left);
		}
		return rotr(r);
	}
	return r;
}

tree* insert(tree* r, int key)
{
	if (!r)
	{
		return new tree(key);
	}
	if (key < r->key)
	{
		r->left = insert(r->left, key);
	}
	else
	{
		r->right = insert(r->right, key);
	}
	return balance(r);
}

tree* findmin(tree* r)
{
	return r->left ? findmin(r->left) : r;
}

tree* remove(tree* r, int key)
{
	if (!r)
		return r;
	if (key < r->key)
		r->left = remove(r->left, key);
	else if (key > r->key)
		r->right = remove(r->right, key);
	else
	{
		if ((!r->left) || (!r->right))
		{
			tree *temp = r->left ? r->left : r->right;
			if (!temp)
			{
				r = NULL;
			}
			else
			{
				*r = *temp;
			}
			delete temp;
		}
		else
		{
			tree* temp = findmin(r->right);
			r->key = temp->key;
			r->right = remove(r->right, temp->key);
		}
	}
	if (!r)
		return r;
	return balance(r);
}

void print(tree* r, int l)
{
	if (r)
	{
		print(r->right, l + 1);
		for (int i = 0; i < l; ++i)
		{
			std::cout << "\t";
		}
		std::cout << r->key << "\n";
		print(r->left, l + 1);
	}
}

bool found(tree* r, int key)
{
	if (!r)
	{
		return 0;
	}
	if (r->key == key)
	{
		return 1;
	}
	else if (r->key < key)
	{
		return found(r->right, key);
	}
	else
	{
		return found(r->left, key);
	}
}

void search(tree* r, int key, int i)
{
	if (!r)
	{
		std::cout << "Key " << key << " was not found.\n";
		return;
	}
	if (r->key == key)
	{
		std::cout << "Key " << key << " was found in " << i <<  " steps.\n";
		return;
	}
	else if (r->key < key)
	{
		search(r->right, key, ++i);
	}
	else
	{
		search(r->left, key, ++i);
	}
}

void task1(tree* r)
{
	if (!r)
	{
		return;
	}
	std::cout << r->key << " ";
	task1(r->left);
	task1(r->right);
}

int _abs(int value)
{
	return value > 0 ? value : -value;
}

void task2_1(tree* r)
{
	if (!r)
	{
		return;
	}
	r->key = _abs(r->key);
	r->key = (r->key % 4) ? r->key : r->key / 2;
	task2_1(r->left);
	task2_1(r->right);
}

int task2_2(tree* r, int prev)
{
	if (!r)
	{
		return prev;
	}
	r->key = _abs(r->key - prev);
	prev = task2_2(r->left, r->key);
	task2_2(r->right, prev);
}