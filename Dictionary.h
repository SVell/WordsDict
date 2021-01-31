#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>

struct book;

// Boolean search Enum
enum request
{
	PHRASE,
	RANGE,
	TWOWORDS,
	TWOPAIRS
};

// Main struct
struct word {
	std::string line;
	int number;
	std::vector<book> books;
};

struct book
{
	std::string name;
	std::vector<int> positions;
};

inline bool operator==(const book& b1, const book& b2)
{
	return b1.name == b2.name;
}

inline bool operator==(const book& b1, const std::string& b2)
{
	return b1.name == b2;
}

inline bool operator==(const book& b1, const int b2)
{
	return std::count(b1.positions.begin(), b1.positions.end(), b2);
}

class Dictionary
{
	
public:
	// All words and books from files
	std::vector<word> words;
	std::vector<word> twoWordIndex;
	std::vector<std::string> books;

	// Main public methods
	void create_dict(const std::string& path);
	void handle_request(const request req, std::string &line, int range = 0);
private:
	void handle_file(const std::string& path, std::string &book);
	void create_two_words_index(const std::string& path, std::string& book);
	// Insertion binary search
	void binary_search(const word& word, const int l, const int r);
	void two_word_binary_search(const word& word, const int l, const int r);
	void insert_word(const word& word);
	void insert_two_word(const word& word);
	void clean_string(std::string& word);
	void create_output_file();

	// Binary search by word
	int binary_search_word(const std::string& word, const int l, const int r);
	int binary_search_two_word(const std::string& word, const int l, const int r);

	// Search
	void search_phrase(std::string& line);
	void search_phrase_two(std::string& line);
	std::vector<std::string> search_range(std::string& line, int range);
	std::vector<std::string > search_range_two(std::string& line, int range);
	std::vector<std::string> search_two_words(std::string& line);;
};

#endif // !DICTIONARY_H

