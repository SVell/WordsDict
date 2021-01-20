#include <iostream>

#include "CreateDictionary.h"

using namespace std;

void Dictionary::handleRequest(const request req, vector<string> &line)
{
	switch (req)
	{
		case NOT:
			handleNot(line);
			break;
		case AND:
			handleAnd(line);
			break;
		case OR:
			handleOr(line);
			break;
	}
}

void Dictionary::handleNot(vector<string>& line)
{
	string newWord = line[1];
	
	int index = binarySearchWord(newWord, 0, words.size());
	cout << index << endl;
	cout << "Books: " << endl;
	
	for(string b : books)
	{
		if (!count(words[index].books.begin(), words[index].books.end(), b)) {
			cout << b << endl;
		}
	}
}
void Dictionary::handleAnd(vector<string>& line)
{
	string firstWord = line[0];
	string secondWord = line[2];

	int firstIndex = binarySearchWord(firstWord, 0, words.size());
	int secondIndex = binarySearchWord(secondWord, 0, words.size());

	cout << "Books: " << endl;
	
	for (string b : books)
	{
		if (count(words[firstIndex].books.begin(), words[firstIndex].books.end(), b) 
			&& count(words[secondIndex].books.begin(), words[secondIndex].books.end(), b)) {
			cout << b << endl;
		}
	}
}
void Dictionary::handleOr(vector<string>& line)
{
	string firstWord = line[0];
	string secondWord = line[2];

	int firstIndex = binarySearchWord(firstWord,0,words.size());
	int secondIndex = binarySearchWord(secondWord, 0, words.size());

	cout << "Books: " << endl;

	for (string b : books)
	{
		if (count(words[firstIndex].books.begin(), words[firstIndex].books.end(), b)
			|| count(words[secondIndex].books.begin(), words[secondIndex].books.end(), b)) {
			cout << b << endl;
		}
	}
}

int Dictionary::binarySearchWord(const string &word, const int l, const int r)
{
	
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (words[mid].line == word) {
			return mid;
		}

		if (words[mid].line > word) {
			return binarySearchWord(word, l, mid - 1);
		}
		return binarySearchWord(word, mid + 1, r);
	}
	
    return -1;
}

