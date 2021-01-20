#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>

enum request
{
	NOT,
	AND,
	OR
};

struct word {
	std::string line;
	int number;
	std::vector<std::string> books;
};

class Dictionary
{
	
public:
	std::vector<word> words;
	std::vector<std::string> books;

	void createDict(const std::string& path);
	void handleRequest(const request req, std::vector<std::string>& line);
private:
	void handleFile(const std::string& path, std::string book);
	void binarySearch(const word& word, const int l, const int r);
	void insertWord(const word& word);
	void cleanString(std::string& word);
	void createOutputFile();

	int binarySearchWord(const std::string& word, const int l, const int r);
	
	void handleNot(std::vector<std::string>& line);
	void handleAnd(std::vector<std::string>& line);
	void handleOr(std::vector<std::string>& line);
	
};

#endif // !DICTIONARY_H

