#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

#include "CreateDictionary.h"

using namespace std;


int main()
{
	Dictionary dict;
	dict.createDict("D:/C++/WordsDict/Books");

	
	
	while(true)
	{
		string command;
		
		cout << "Enter your Command: " << endl;
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
			cout << "Input command error" << endl;
			continue;
		}
		else if(commands.size() == 2)
		{
			dict.handleRequest(NOT, commands);
		}
		else
		{
			if(commands[1] == "and")
			{
				dict.handleRequest(AND, commands);
			}
			else if(commands[1] == "or")
			{
				dict.handleRequest(OR, commands);
			}
		}
	}
}
