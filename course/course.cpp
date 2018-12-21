// course.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream> //for std::cout, std::cin
#include <fstream> // for file operations
#include <string> //for std::string and std::getline
#include <vector> //for std::vector

struct entry //database entry structure
{
	std::string name;
	std::string sign;
	int date[3];
};

class database
{
private:
	std::vector<entry> data; //vector of entries
	bool compare(entry, entry); //comparison function (alphabetical). used for sorting
	std::string filename = "base.txt"; //name of file to open/write to
public:
	database() //empty constructor
	{
	}
	~database() //destructor clears the vector
	{
		data.clear();
	}
	void createentry();
	void deleteentry(int);
	void editentry(int);
	void print(int);
	void printall();
	void sort();
	void find(std::string);
	int findpos(std::string);
	void dataimport();
	void dataexport();
	bool isequal(entry, entry);
	int size();
};

//_________________________________
//_______function signatures_______
//_________________________________
std::string zodiac(int[3]);
int input_int(int, int);
std::string input_string_cap();
void input_date(int(&)[3]);
bool stringempty(std::string);
bool fileempty(std::ifstream(&));


//_________________________________
//__________main function__________
//_________________________________
int main()
{
	database staff;
	int menu;
	while (true)
	{
		system("cls");
		std::cout << "Main menu.\nEnter number of option:\n";
		std::cout << "1. Create new entry\n";
		std::cout << "2. Delete existing entry\n";
		std::cout << "3. Edit existing entry\n";
		std::cout << "4. Sort entries alphabetically\n";
		std::cout << "5. Find existing entry by name\n";
		std::cout << "6. Find existing entry by number\n";
		std::cout << "7. Print all entries\n";
		std::cout << "8. Import database from file\n";
		std::cout << "9. Export database to file\n";
		std::cout << "0. Exit\n\n";
		std::cout << "Input: ";
		menu = input_int(0, 9);
		switch (menu)
		{
		case 1:
		{
			staff.createentry();
			std::cout << "\n";
			system("pause");
			break;
		}
		case 2:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			std::cout << "Enter name of entry to be deleted: ";
			std::string name = input_string_cap();
			int pos = staff.findpos(name);
			if (pos == -1)
			{
				std::cout << "Entry not found.\n";
				system("pause");
				break;
			}
			std::cout << "Following entry has been deleted:\n";
			staff.print(pos);
			staff.deleteentry(pos);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 3:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			std::cout << "Enter name of entry to be edited: ";
			std::string name = input_string_cap();
			int pos = staff.findpos(name);
			staff.editentry(pos);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 4:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			std::cout << "Sorting...\n";
			staff.sort();
			std::cout << "Sort complete.\n\n";
			system("pause");
			break;
		}
		case 5:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			std::cout << "Enter name to find: ";
			std::string name = input_string_cap();
			staff.find(name);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 6:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			std::cout << "Enter number of entry: ";
			int pos = input_int(1, staff.size());
			staff.print(pos - 1);
			std::cout << "\n";
			system("pause");
			break;
		}
		case 7:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			staff.printall();
			std::cout << "\n";
			system("pause");
			break;
		}
		case 8:
		{
			staff.dataimport();
			std::cout << "\n";
			system("pause");
			break;
		}
		case 9:
		{
			if (!staff.size())
			{
				std::cout << "Database is empty.\n\n";
				system("pause");
				break;
			}
			staff.dataexport();
			std::cout << "\n";
			system("pause");
			break;
		}
		case 0:
		{
			std::cout << "Exiting.\n";
			return 0;
		}
		}
	}
}

//_________________________________
//_________class funcions__________
//_________________________________

//creates entry with given name, date and automatically fills sign field
void database::createentry()
{
	entry temp;
	std::cout << "Enter a name: ";
	temp.name = input_string_cap();
	std::cout << "Enter birth date.\n";
	int date[3];
	input_date(date);
	temp.date[0] = date[0]; //assigning each memeber individually
	temp.date[1] = date[1]; //since default arrays are unassignable
	temp.date[2] = date[2];
	temp.sign = zodiac(temp.date);
	int check = 0;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		if (isequal(data[i], temp))
		{
			++check;
			std::cout << "\nThis entry already exists:\n";
			print(i);
		}
	}
	if (!check)
	{
		data.push_back(temp);
	}
}

//deletes entry on given position
void database::deleteentry(int pos)
{
	data.erase(data.begin() + pos);
}

//edits data of given entry
void database::editentry(int pos)
{
	entry temp;
	std::cout << "Enter new name: ";
	temp.name = input_string_cap();
	std::cout << "Enter new birth date:\n";
	int date[3];
	input_date(date);
	temp.date[0] = date[0];
	temp.date[1] = date[1];
	temp.date[2] = date[2];
	temp.sign = zodiac(temp.date);
	int check = 0;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		if (isequal(data[i], temp))
		{
			++check;
			std::cout << "\nThis entry already exists:\n";
			print(i);
		}
	}
	if (!check)
	{
		data[pos] = temp;
	}

}

//prints database entry with given number
void database::print(int pos)
{
	std::cout << "Entry #" << (pos + 1) << ":\nName:\t\t" << data[pos].name << ".\nBirth date:\t" << data[pos].date[0] << "." << data[pos].date[1] << "." << data[pos].date[2] << "\nSign:\t\t" << data[pos].sign << ".\n";
}

void database::printall()
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("| #:  | Name:                                      | Date:      | Sign:       |\n");
	printf("+-----+--------------------------------------------+------------+-------------+\n");
	for (int i = 0; i < data.size(); ++i)
	{
		printf("| %3i | %42s | %02i.%02i.%04i | %11s |\n", (i + 1), data[i].name.c_str(), data[i].date[0], data[i].date[1], data[i].date[2], data[i].sign.c_str());
	}
	printf("+-----------------------------------------------------------------------------+\n");
}

//compares entries names alphabetically: returns 1 is e1 is less than e2
bool database::compare(entry e1, entry e2)
{
	return (e1.name.compare(e2.name) < 0);
}

//sorts database entries alphabetically
void database::sort()
{
	int minpos;
	entry temp;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		minpos = i;
		for (unsigned int j = i + 1; j < data.size(); ++j)
		{
			if (compare(data[j], data[minpos]))
			{
				minpos = j;
			}
		}
		temp = data[i];
		data[i] = data[minpos];
		data[minpos] = temp;
	}
}

//finds entry starting with given name. prints all suitable entries
void database::find(std::string name)
{
	int count = 0;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		if (data[i].name.find(name) != std::string::npos)
		{
			print(i);
			++count;
		}
	}
	if (!count)
	{
		std::cout << "No entries with that name.";
	}
}

//returns position of entry with given name
int database::findpos(std::string name)
{
	std::vector<int> results;
	int pos;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		if (data[i].name.find(name) != std::string::npos)
		{
			results.push_back(i);
		}
	}
	if (results.empty())
	{
		std::cout << "No entries with that name.";
		return -1;
	}
	if (results.size() > 1)
	{
		std::cout << "Several entries found:\n\n";
		for (unsigned int i = 0; i < results.size(); ++i)
		{
			std::cout << "Result " << (i + 1) << ":\n";
			print(results.at(i));
			std::cout << "\n";
		}
		std::cout << "Enter number of result to work on: ";
		pos = input_int(1, results.size());
		return results.at(pos - 1);
	}
	else
	{
		return results.at(0);
	}
}

//imports data vector from file
void database::dataimport()
{
	std::vector<entry> newdata;
	entry temp;
	std::string line;
	std::ifstream infile;
	infile.open(filename);
	if (fileempty(infile))
	{
		std::cout << "Import failed. File is empty or is not created yet.\n";
		return;
	}
	std::cout << "Importing database from file...\n";
	int count = 0;
	while (std::getline(infile, line))
	{
		if (line.find_first_of('#') != std::string::npos)
		{
			while (std::getline(infile, line) && stringempty(line)) {}
			temp.name = line;
			while (std::getline(infile, line) && stringempty(line)) {}
			sscanf_s(line.c_str(), "%d%*c%d%*c%d", &temp.date[0], &temp.date[1], &temp.date[2]);
			temp.sign = zodiac(temp.date);
			if ((temp.date[0] == 0) || (temp.date[1] == 0) || (temp.date[2] == 0))
			{
				++count;
				continue;
			}
			newdata.push_back(temp);
			temp.name = "";
			temp.date[0] = 0; temp.date[1] = 0; temp.date[2] = 0;
			temp.sign = "";
		}
	}
	infile.close();
	if (newdata.size() == 0)
	{
		std::cout << "Import failed. File is corrupted.\n";
	}
	else
	{
		data = newdata;
		if (count)
		{
			std::cout << "There were errors while importing.\nError count: " << count << ".\n";
		}
		std::cout << "Import complete.\n";
	}
}

//exports data vector to file
void database::dataexport()
{
	std::ofstream outfile;
	outfile.open(filename);
	std::cout << "Exporting...\n";
	for (int i = 0; i < size(); ++i)
	{
		outfile << "Entry #" << (i + 1) << "\n";
		outfile << data[i].name << "\n";
		outfile << data[i].date[0] << "." << data[i].date[1] << "." << data[i].date[2] << "\n\n";
		//outfile << data[i].sign << "\n\n";
	}
	outfile.close();
	std::cout << "Exporting complete.\n";
}

//returns 1 if entries are equal in all fields
bool database::isequal(entry e1, entry e2)
{
	if (e1.name == e2.name && e1.date[0] == e2.date[0] && \
		e1.date[1] == e2.date[1] && e1.date[2] == e2.date[2])
	{
		return 1;
	}
	return 0;
}

//returns size of database
int database::size()
{
	return data.size();
}

//_________________________________
//______non class functions________
//_________________________________

//returns zodiac sign as a string based input date
std::string zodiac(int date[3])
{
	if (((date[0] >= 21) && (date[1] == 3)) || ((date[0] <= 19) && (date[1] == 4)))
	{
		return "Aeries";
	}
	if (((date[0] >= 20) && (date[1] == 4)) || ((date[0] <= 20) && (date[1] == 5)))
	{
		return "Taurus";
	}
	if (((date[0] >= 21) && (date[1] == 5)) || ((date[0] <= 20) && (date[1] == 6)))
	{
		return "Gemini";
	}
	if (((date[0] >= 21) && (date[1] == 6)) || ((date[0] <= 22) && (date[1] == 7)))
	{
		return "Cancer";
	}
	if (((date[0] >= 23) && (date[1] == 7)) || ((date[0] <= 22) && (date[1] == 8)))
	{
		return "Leo";
	}
	if (((date[0] >= 23) && (date[1] == 8)) || ((date[0] <= 22) && (date[1] == 9)))
	{
		return "Virgo";
	}
	if (((date[0] >= 23) && (date[1] == 9)) || ((date[0] <= 22) && (date[1] == 10)))
	{
		return "Libra";
	}
	if (((date[0] >= 23) && (date[1] == 10)) || ((date[0] <= 21) && (date[1] == 11)))
	{
		return "Scorpio";
	}
	if (((date[0] >= 22) && (date[1] == 11)) || ((date[0] <= 21) && (date[1] == 12)))
	{
		return "Sagittarius";
	}
	if (((date[0] >= 22) && (date[1] == 12)) || ((date[0] <= 19) && (date[1] == 1)))
	{
		return "Capricorn";
	}
	if (((date[0] >= 20) && (date[1] == 1)) || ((date[0] <= 18) && (date[1] == 2)))
	{
		return "Aquarius";
	}
	if (((date[0] >= 19) && (date[1] == 2)) || ((date[0] <= 20) && (date[1] == 3)))
	{
		return "Pisces";
	}
	return "Unknown sign";
}

//returns user input integer within specified boundaries
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
			std::cout << "Incorrect input. Input must be an integer.\nTry again: ";
			flag = 0;
			continue;
		}
		if ((integer > max) || (integer < min))
		{
			std::cout << "Incorrect input. Input must be between " << min << " and " << max << ".\nTry again: ";
			continue;
		}
		return integer;
	}
}

//returns user input string, with every first letter of word capitalized
//string must only contain letters, hyphen and space, without consecutive hyphens or spaces or hyphen or space at the start or the end
std::string input_string_cap()
{
	std::string temp;
	int check;
	while (true)
	{
		std::getline(std::cin, temp);
		check = 0;
		if (temp.empty())
		{
			continue;
		}
		for (unsigned int i = 0; i < temp.size(); ++i)
		{
			if (!(((temp[i] > 64) && (temp[i] < 91)) || ((temp[i] > 96) && (temp[i] < 123)) || ((temp[i] == 45) || (temp[i] == 32))))
			{
				++check;
			}
		}
		if (((temp[0] == '-') || (temp[0] == ' ')) || ((temp[temp.size() - 1] == '-') || (temp[temp.size() - 1] == ' ')))
		{
			++check;
		}
		for (unsigned int i = 1; i < (temp.size() - 1); ++i)
		{
			if (((temp[i] == '-') || (temp[i] == ' ')) && (((temp[i - 1] == '-') || (temp[i - 1] == ' ')) || ((temp[i + 1] == '-') || (temp[i + 1] == ' '))))
			{
				++check;
			}
		}
		if (check)
		{
			std::cout << "Wrong input. Input must only contain letters, space and hyphen.\nWords must not start or end with hyphen.\nInput must not  contain two or more consecutive spaces or hyphens.\nTry again: ";
			continue;
		}
		break;
	}
	temp[0] = toupper(temp[0]);
	for (unsigned int i = 1; i < temp.size(); ++i)
	{
		if ((temp[i - 1] == ' ') || (temp[i - 1] == '-'))
		{
			temp[i] = toupper(temp[i]);
		}
		else
		{
			temp[i] = tolower(temp[i]);
		}
	}
	return temp;
}

//returns pointer to array containig a valid user input date
void input_date(int(&date)[3])
{
	while (true)
	{
		std::cout << "Day: ";
		date[0] = input_int(1, 31);
		std::cout << "Month: ";
		date[1] = input_int(1, 12);
		std::cout << "Year: ";
		date[2] = input_int(1900, 2018);
		if (((date[1] == 2) && (date[0] > 29)) || ((date[1] == 4) && (date[0] > 30)) || ((date[1] == 6) && (date[0] > 30)) || ((date[1] == 9) && (date[0] > 30)) || ((date[1] == 11) && (date[0] > 30)))
		{
			std::cout << "Wrong input. Such date does not exist.\nTry again.\n";
			continue;
		}
		if ((date[1] == 2) && (date[0] == 29))
		{
			if ((date[2] % 4) || (!(date[2] % 100) && (date[2] % 400)))
			{
				std::cout << "Wrong input. Year " << date[2] << " is not a leap year.\nTry again.\n";
				continue;
			}
		}
		break;
	}
}

//returns 1 if string only constists of spaces or is empty
bool stringempty(std::string str)
{
	if (str.empty())
	{
		return 1;
	}
	for (unsigned int i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
		{
			return 0;
		}
	}
	return 1;
}

//returns 1 if file in the stream is empty
bool fileempty(std::ifstream(&file))
{
	return (file.peek() == std::ifstream::traits_type::eof());
}