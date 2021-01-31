#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <windows.h>

#include "Dictionary.h"

using namespace std;

void use_dictionary(Dictionary& dict)
{
	while (true)
	{
		int range;
		int x;
		string line;
		string temp;
		
		cout << "1 - Find phrase" << endl;
		cout << "2 - Find words in range" << endl;
		cout << "3 - Use Two Words dictionary find phrase" << endl;
		cout << "4 - Use Two Words dictionary find 2 pairs" << endl;
		
		getline(cin, line);
		x = stoi(line);
		
		cout << "Enter line: ";
		getline(cin, line);

		switch (x)
		{
		case 0:
			break;
		case 1:
			dict.handle_request(PHRASE, line);
			break;
		case 2:
			cout << "Enter Range: ";
			getline(cin, temp);
			range = stoi(temp);
			if (range <= 0)
			{
				cerr << "Invalid Range" << endl;
				continue;
			}
			dict.handle_request(RANGE, line,range);
			break;
		case 3:
			dict.handle_request(TWOWORDS, line);
			break;
		case 4:
			cout << "Enter Range: ";
			getline(cin, temp);
			range = stoi(temp);
			if (range <= 0)
			{
				cerr << "Invalid Range" << endl;
					continue;
			}
			dict.handle_request(TWOPAIRS, line, range);
			break;
		default:
			cerr << "Incorrect value" << endl;
		}
	}
}

void use_boolean_search(Dictionary& dict)
{
	while (true)
	{
		string command;

		cout << "Enter your Command: ";
		getline(cin, command);

		transform(command.begin(), command.end(), command.begin(), ::tolower);

		vector<string> commands;

		std::istringstream iss(command);
		for (std::string s; iss >> s; )
		{
			commands.push_back(s);
		}


		if (commands.size() > 3 || commands.size() == 0)
		{
			cerr << "Input command error";
		}
		else if (commands.size() == 2)
		{
			dict.handle_boolean_search(NOT, commands);
		}
		else
		{
			if (commands[1] == "and")
			{
				dict.handle_boolean_search(AND, commands);
			}
			else if (commands[1] == "or")
			{
				dict.handle_boolean_search(OR, commands);
			}
			else
			{
				cout << "Exiting" << endl;
				break;
			}
		}
		cout << endl;
	}
}

int main()
{
	Dictionary dict;
	dict.create_dict("D:/C++/WordsDict/Books");
	system("cls");

	cout << "Dictionary created" << endl;

	
	while(true)
	{
		int x;
		string line;

		cout << "1 - Boolean Search" << endl;
		cout << "2 - Use Dictionary" << endl;
		
		getline(cin, line);
		x = stoi(line);

		switch (x)
		{
		case 1:
			use_boolean_search(dict);
			break;
		case 2:
			use_dictionary(dict);
			break;
		default:
			cerr << "Invalid Input" << endl;
		}
	}
}
