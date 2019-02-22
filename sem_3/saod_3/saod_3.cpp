// saod_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>



struct task
{
	int task_priority;
	int task_duration;
	int task_time;
	int task_number;
};

task randomtask(int);
task usertask(int);

class squeue
{
private:
	int size = 10;
	task queue[10];
	int front;
	int rear;
public:
	squeue()
	{
		front = -1;
		rear = -1;
	}
	void insert(task);
	void remove();
	task getfirst();
	bool isempty();
	void display();
};

class sstack
{
private:
	int size = 10;
	task stack[10];
	int front;
	int rear;
public:
	sstack()
	{
		front = -1;
		rear = -1;
	}
	void insert(task);
	void remove();
	task getfirst();
	bool isempty();
	void display();
};

int main()
{
	srand(time(NULL));
	squeue f0;
	squeue f1;
	squeue f2;
	sstack s;
	task processor;
	processor.task_priority = 0;
	processor.task_duration = 0;
	int tasknum;
	std::cout << "Input number of tasks: ";
	std::cin >> tasknum;
	task *taskqueue = new task[tasknum];
	int temp;
	int tasknumstart = tasknum;
	std::cout << "Choose option:\n1. Generate tasks randomly.\n2. Input tasks manually.\n";
	std::cin >> temp;
	if (temp == 1)
	{
		std::cout << "Generated tasks:\n";
		for (int i = 0; i < tasknum; ++i)
		{
			taskqueue[i] = randomtask(i + 1);
			std::cout << "Task " << taskqueue[i].task_number << ". Priority: " << taskqueue[i].task_priority << "; Duration: " << taskqueue[i].task_duration << "; Admission time: " << taskqueue[i].task_time << ".\n";
		}
		std::cout << "\n\n";
	}
	if (temp == 2)
	{
		for (int i = 0; i < tasknum; ++i)
		{
			taskqueue[i] = usertask(i + 1);
		}
	}
	int timer = 1;
	while (true)
	{
		for (int i = 0; i < tasknumstart; ++i)
		{
			if (taskqueue[i].task_time == timer)
			{
				switch (taskqueue[i].task_priority)
				{
				case 0:
				{
					f0.insert(taskqueue[i]);
					--tasknum;
					break;
				}
				case 1:
				{
					f1.insert(taskqueue[i]);
					--tasknum;
					break;
				}
				case 2:
				{
					f2.insert(taskqueue[i]);
					--tasknum;
					break;
				}
				}
			}
		}
		if (!s.isempty() && !(processor.task_duration))
		{
			if (s.getfirst().task_priority == 0)
			{
				processor = s.getfirst();
				s.remove();
			}
			if ((s.getfirst().task_priority == 1) && f0.isempty())
			{
				processor = s.getfirst();
				s.remove();
			}
			if ((s.getfirst().task_priority == 2) && f0.isempty() && f1.isempty())
			{
				processor = s.getfirst();
				s.remove();
			}
		}
		if (!f0.isempty())
		{
			if (!(processor.task_duration))
			{
				processor = f0.getfirst();
				f0.remove();
			}
			else
			{
				if ((processor.task_priority > f0.getfirst().task_priority) && (((taskqueue[processor.task_number - 1].task_time - processor.task_duration) * 2) < taskqueue[processor.task_number - 1].task_time))
				{
					s.insert(processor);
					processor = f0.getfirst();
					f0.remove();
				}
			}
		}
		if (!f1.isempty())
		{
			if (!(processor.task_duration))
			{
				processor = f1.getfirst();
				f1.remove();
			}
			else
			{
				if ((processor.task_priority > f1.getfirst().task_priority) && (((taskqueue[processor.task_number - 1].task_time - processor.task_duration) * 2) < taskqueue[processor.task_number - 1].task_time))
				{
					s.insert(processor);
					processor = f1.getfirst();
					f1.remove();
				}
			}
		}
		if (!f2.isempty())
		{
			if (!(processor.task_duration))
			{
				processor = f2.getfirst();
				f2.remove();
			}
			else
			{
				if ((processor.task_priority > f2.getfirst().task_priority) && (((taskqueue[processor.task_number - 1].task_time - processor.task_duration) * 2) < taskqueue[processor.task_number - 1].task_time))
				{
					s.insert(processor);
					processor = f2.getfirst();
					f2.remove();
				}
			}
		}

		std::cout << "Program tick #" << timer << ":\n";
		if (!processor.task_duration)
		{
			std::cout << "Processor is free.\n";
		}
		else
		{
			std::cout << "Processor is working on task " << processor.task_number << ". Priority: " << processor.task_priority << ". Ticks remaining: " << processor.task_duration << "/" << taskqueue[processor.task_number - 1].task_duration << ".\n";
		}
		std::cout << "Stack content:\n";
		s.display();
		std::cout << "Queue f0 content:\n";
		f0.display();
		std::cout << "Queue f1 content:\n";
		f1.display();
		std::cout << "Queue f2 content:\n";
		f2.display();
		std::cout << "\n";
		//system("pause");

		++timer;
		if (processor.task_duration)
		{
			--processor.task_duration;
		}
		if (!tasknum && !(processor.task_duration) && f0.isempty() && f1.isempty() && f2.isempty() && s.isempty())
		{
			std::cout << "\nAll tasks completed.\n";
			break;
		}
	}
	system("pause");
}

void squeue::insert(task t)
{
	if (front == -1)
	{
		++front;
	}
	if (rear != size - 1)
	{
		queue[rear + 1] = t;
		++rear;
	}
	else
	{
		std::cout << "Error. Queue is full.\n";
	}
}

void squeue::remove()
{
	if (front != -1)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			queue[i] = queue[i + 1];
		}
		--rear;
		if (rear == -1)
		{
			front = -1;
		}
	}
	else
	{
		std::cout << "Error. Queue is empty.\n";
	}
}

task squeue::getfirst()
{
	if (front != -1)
	{
		return queue[front];
	}
	else
	{
		std::cout << "Error. Queue is empty.\n";
	}
}

bool squeue::isempty()
{
	if (front == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void squeue::display()
{
	if (front == -1)
	{
		std::cout << "Queue is empty.\n";
	}
	else
	{
		for (int i = 0; i < rear + 1; ++i)
		{
			std::cout << "Task " << queue[i].task_number << ". Priority:" << queue[i].task_priority << ". Duration: " << queue[i].task_duration << ".\n";
		}
	}
}

void sstack::insert(task t)
{
	if (front == -1)
	{
		++front;
	}
	if (rear != size - 1)
	{
		for (int i = size - 2; i > -1; --i)
		{
			stack[i + 1] = stack[i];
		}
		stack[front] = t;
		++rear;
	}
	else
	{
		std::cout << "Error. Stack is full.\n";
	}
}

void sstack::remove()
{
	if (front != -1)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			stack[i] = stack[i + 1];
		}
		--rear;
		if (rear == -1)
		{
			front = -1;
		}
	}
	else
	{
		std::cout << "Error. Stack is empty.\n";
	}
}

task sstack::getfirst()
{
	if (front != -1)
	{
		return stack[front];
	}
	else
	{
		std::cout << "Error. Stack is empty.\n";
	}
}

bool sstack::isempty()
{
	if (front == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void sstack::display()
{
	if (front == -1)
	{
		std::cout << "Stack is empty.\n";
	}
	else
	{
		for (int i = 0; i < rear + 1; ++i)
		{
			std::cout << "Task " << stack[i].task_number << ". Priority:" << stack[i].task_priority << ". Duration: " << stack[i].task_duration << ".\n";
		}
	}
}

task randomtask(int num)
{
	task t;
	t.task_duration = rand() % 9 + 1;
	t.task_priority = rand() % 3;
	t.task_time = rand() % 10 + 1;
	t.task_number = num;
	return t;
}

task usertask(int num)
{
	task t;
	int temp;
	std::cout << "Input task duration: ";
	std::cin >> temp;
	t.task_duration = temp;
	std::cout << "Input task priority: ";
	std::cin >> temp;
	t.task_priority = temp;
	std::cout << "Input task admission time: ";
	std::cin >> temp;
	t.task_time = temp;
	t.task_number = num;
	return t;
}