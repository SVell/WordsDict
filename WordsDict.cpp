#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <windows.h>

#include "Dictionary.h"

using namespace std;


int main()
{
	Dictionary dict;
	dict.create_dict("D:/C++/WordsDict/Books");
	system("cls");

	cout << "Dictionary created" << endl;
	
	while(true)
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
		else if(commands.size() == 2)
		{
			dict.handle_request(NOT, commands);
		}
		else
		{
			if(commands[1] == "and")
			{
				dict.handle_request(AND, commands);
			}
			else if(commands[1] == "or")
			{
				dict.handle_request(OR, commands);
			}
		}
		cout << endl;
	}
}
