#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>

// Boolean search Enum
enum request
{
	NOT,
	AND,
	OR
};

// Main struct
struct word {
	std::string line;
	int number;
	std::vector<std::string> books;
};

class Dictionary
{
	
public:
	// All words and books from files
	std::vector<word> words;
	std::vector<std::string> books;

	// Main public methods
	void create_dict(const std::string& path);
	void handle_request(const request req, std::vector<std::string>& line);
private:
	void handle_file(const std::string& path, std::string &book);
	// Insertion binary search
	void binary_search(const word& word, const int l, const int r);
	void insert_word(const word& word);
	void clean_string(std::string& word);
	void create_output_file();

	// Binary search by word
	int binary_search_word(const std::string& word, const int l, const int r);

	// Handling boolean search
	void handle_not(std::vector<std::string>& line);
	void handle_and(std::vector<std::string>& line);
	void handle_or(std::vector<std::string>& line);
	
};

#endif // !DICTIONARY_H

