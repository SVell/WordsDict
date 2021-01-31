#include <algorithm>
#include <iostream>
#include <sstream>

#include "Dictionary.h"

using namespace std;

// Console 
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Dictionary::handle_boolean_search(const request req, vector<string>& line)
{
	switch (req)
	{
	case NOT:
		handle_not(line);
		break;
	case AND:
		handle_and(line);
		break;
	case OR:
		handle_or(line);
		break;
	case ONE:
		break;
	}
}

void Dictionary::handle_not(vector<string>& line)
{
	const string newWord = line[1];

	const int index = binary_search_word(newWord, 0, words.size(),words);
	cout << index << endl;

	// Console color
	SetConsoleTextAttribute(hConsole, 10);

	cout << "Books: " << endl;
	for (const string book : books)
	{
		if (!count(words[index].books.begin(), words[index].books.end(), book)) {
			cout << book << endl;
		}
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void Dictionary::handle_and(vector<string>& line)
{
	const string firstWord = line[0];
	const string secondWord = line[2];

	const int firstIndex = binary_search_word(firstWord, 0, words.size(), words);
	const int secondIndex = binary_search_word(secondWord, 0, words.size(), words);

	// Console color
	SetConsoleTextAttribute(hConsole, 10);

	cout << "Books: " << endl;
	for (const string book : books)
	{
		if (count(words[firstIndex].books.begin(), words[firstIndex].books.end(), book)
			&& count(words[secondIndex].books.begin(), words[secondIndex].books.end(), book)) {
			cout << book << endl;
		}
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void Dictionary::handle_or(vector<string>& line)
{
	const string firstWord = line[0];
	const string secondWord = line[2];

	const int firstIndex = binary_search_word(firstWord, 0, words.size(), words);
	const int secondIndex = binary_search_word(secondWord, 0, words.size(), words);

	// Console color
	SetConsoleTextAttribute(hConsole, 10);

	cout << "Books: " << endl;
	for (const string book : books)
	{
		if (count(words[firstIndex].books.begin(), words[firstIndex].books.end(), book)
			|| count(words[secondIndex].books.begin(), words[secondIndex].books.end(), book)) {
			cout << book << endl;
		}
	}
	SetConsoleTextAttribute(hConsole, 7);
}
