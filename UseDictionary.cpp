#include <iostream>
#include <windows.h>

#include "Dictionary.h"

using namespace std;

// Console 
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Dictionary::handle_request(const request req, vector<string> &line)
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
	}
}

void Dictionary::handle_not(vector<string>& line)
{
	const string newWord = line[1];
	
	const int index = binary_search_word(newWord, 0, words.size());
	cout << index << endl;

	// Console color
	SetConsoleTextAttribute(hConsole, 10);
	
	cout << "Books: " << endl;
	for(const string book : books)
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

	const int firstIndex = binary_search_word(firstWord, 0, words.size());
	const int secondIndex = binary_search_word(secondWord, 0, words.size());

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

	const int firstIndex = binary_search_word(firstWord,0,words.size());
	const int secondIndex = binary_search_word(secondWord, 0, words.size());

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

int Dictionary::binary_search_word(const string &word, const int l, const int r)
{
	
	if (r >= l) {
		const int mid = l + (r - l) / 2;

		if (words[mid].line == word) {
			return mid;
		}

		if (words[mid].line > word) {
			return binary_search_word(word, l, mid - 1);
		}
		return binary_search_word(word, mid + 1, r);
	}
	
    return -1;
}

