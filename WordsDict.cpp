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

int main()
{
	Dictionary dict;
	dict.create_dict("D:/C++/WordsDict/Books");
	system("cls");

	cout << "Dictionary created" << endl;
	
	use_dictionary(dict);
}
