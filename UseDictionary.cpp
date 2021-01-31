#include <algorithm>
#include <iostream>
#include <sstream>

#include "Dictionary.h"

using namespace std;

// Console 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void Dictionary::handle_request(const request req, string& line, int range)
{
	transform(line.begin(), line.end(), line.begin(), ::tolower);
	
	
	vector<string> res;
	
	switch (req)
	{
	case PHRASE:
		search_phrase(line);
		break;
	case RANGE:
		range += 2;
		res = search_range(line, range);
		SetConsoleTextAttribute(console, 10);
		cout << "Books: " << endl;
		for(auto l : res)
		{
			cout << l << endl;
		}
		SetConsoleTextAttribute(console, 7);
		break;
	case TWOWORDS:
		search_phrase_two(line);
		break;
	case TWOPAIRS:
		range *= 2;
		range += 2;
		res = search_range_two(line, range);
		SetConsoleTextAttribute(console, 10);
		cout << "Books: " << endl;
		for (auto l : res)
		{
			cout << l << endl;
		}
		SetConsoleTextAttribute(console, 7);
		break;
	}
}

void Dictionary::search_phrase(string& line)
{
	vector<string> allBook = books;
	
	istringstream iss(line);
	vector<string> res;
	copy((istream_iterator<string>(iss)), istream_iterator<string>(), back_inserter(res));

	const int firstIndex = binary_search_word(res[0], 0, words.size() - 1, words);

	bool hasPhrase = true;
	
	// Console color
	SetConsoleTextAttribute(console, 10);

	cout << "Books: " << endl;
	for(int i = 0; i < res.size()-1; ++i)
	{
		string newline = res[i];
		newline += " " + res[i + 1];
		
		vector<string> b = search_range(newline, 3);
		vector<string> temp;

		if (b.size() == 0)
		{
			hasPhrase = false;
			break;
		}
		
		for(int i = 0; i < allBook.size(); ++i)
		{
			for (int j = 0; j < b.size(); ++j)
			{
				if(allBook[i] == b[j] && !count(temp.begin(), temp.end(), allBook[i]))
				{
					temp.push_back(allBook[i]);
				}
			}
		}

		allBook = temp;
	}

	if(hasPhrase)
	{
		for (auto l : allBook)
		{
			cout << l << endl;
		}
	}

	SetConsoleTextAttribute(console, 7);
}

void Dictionary::search_phrase_two(string& line)
{
	vector<string> allBook = books;

	istringstream iss(line);
	vector<string> res;
	copy((istream_iterator<string>(iss)), istream_iterator<string>(), back_inserter(res));

	const int firstIndex = binary_search_word(res[0], 0, twoWordIndex.size() - 1,twoWordIndex);

	bool hasPhrase = true;

	// Console color
	SetConsoleTextAttribute(console, 10);

	cout << "Books: " << endl;
	for (int i = 0; i < res.size() - 1; ++i)
	{
		string newline = res[i];
		newline += " " + res[i + 1];

		vector<string> b = search_two_words(newline);
		vector<string> temp;

		if (b.size() == 0)
		{
			hasPhrase = false;
			break;
		}

		for (int i = 0; i < allBook.size(); ++i)
		{
			for (int j = 0; j < b.size(); ++j)
			{
				if (allBook[i] == b[j] && !count(temp.begin(), temp.end(), allBook[i]))
				{
					temp.push_back(allBook[i]);
				}
			}
		}

		allBook = temp;
	}

	if (hasPhrase)
	{
		for (auto l : allBook)
		{
			cout << l << endl;
		}
	}

	SetConsoleTextAttribute(console, 7);
}

vector<string> Dictionary::search_range(string& line, int range)
{
	vector<string> allBooks;
	
	istringstream iss(line);
	vector<string> res;
	copy((istream_iterator<string>(iss)), istream_iterator<string>(), back_inserter(res));
	
	const string firstWord = res[0];
	const string secondWord = res[1];

	const int firstIndex = binary_search_word(firstWord, 0, words.size(), words);
	const int secondIndex = binary_search_word(secondWord, 0, words.size(), words);

	for (const book b : words[firstIndex].books)
	{
		auto f = find(words[secondIndex].books.begin(), words[secondIndex].books.end(), b.name);
		if (f != words[secondIndex].books.end()) {
			for(auto p1 : b.positions)
			{
				for (auto p2 : f->positions)
				{
					if(p2 <= (p1 + range) && !(p2 <= p1))
					{
						allBooks.push_back(b.name);
					}
				}
			}
		}
	}
	

	return allBooks;
}

vector<string> Dictionary::search_range_two(string& line, int range)
{
	vector<string> allBooks;

	istringstream iss(line);
	vector<string> res;
	copy((istream_iterator<string>(iss)), istream_iterator<string>(), back_inserter(res));

	const string firstWord = res[0] + " " + res[1];
	const string secondWord = res[2] + " " + res[3];

	const int firstIndex = binary_search_word(firstWord, 0, twoWordIndex.size() - 1, twoWordIndex);
	const int secondIndex = binary_search_word(secondWord, 0, twoWordIndex.size() - 1, twoWordIndex);
	
	for (const book b : twoWordIndex[firstIndex].books)
	{
		auto f = find(twoWordIndex[secondIndex].books.begin(), twoWordIndex[secondIndex].books.end(), b.name);
		if (f != twoWordIndex[secondIndex].books.end()) {
			for (auto p1 : b.positions)
			{
				for (auto p2 : f->positions)
				{
					if (p2 <= (p1 + range) && !(p2 <= p1))
					{
						allBooks.push_back(b.name);
					}
				}
			}
		}
	}


	return allBooks;
}

vector<string> Dictionary::search_two_words(string& line)
{
	vector<string> allBooks;
	
	const int index = binary_search_word(line, 0, twoWordIndex.size() - 1, twoWordIndex);
	
	for(const string book : books)
	{
		if (count(twoWordIndex[index].books.begin(), twoWordIndex[index].books.end(), book)) {
			allBooks.push_back(book);
		}
	}

	return allBooks;
}

int Dictionary::binary_search_word(const string &w, const int l, const int r, std::vector<word>& container)
{
	if (r >= l) {
		const int mid = l + (r - l) / 2;

		if (container[mid].line == w) {
			return mid;
		}

		if (container[mid].line > w) {
			return binary_search_word(w, l, mid - 1, container);
		}
		return binary_search_word(w, mid + 1, r, container);
	}
	
    return -1;
}

