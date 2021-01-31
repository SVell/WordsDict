#pragma once

#include <vector>
#include <string>
#include <windows.h>

#include "Structs.h"

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
	void handle_boolean_search(const request req, std::vector<std::string>& line);
private:
	void handle_file(const std::string& path, std::string &book);
	// Insertion binary search
	void binary_search(const word& w, const int l, const int r, std::vector<word>& container);
	void insert_word(const word& w, std::vector<word> &container);
	void clean_string(std::string& word);
	void create_output_file();

	// Binary search by word
	int binary_search_word(const std::string& w, const int l, const int r, std::vector<word>& container);

	// Search
	void search_phrase(std::string& line);
	void search_phrase_two(std::string& line);
	std::vector<std::string> search_range(std::string& line, int range);
	std::vector<std::string > search_range_two(std::string& line, int range);
	std::vector<std::string> search_two_words(std::string& line);

	// Boolean Search
	void handle_not(std::vector<std::string>& line);
	void handle_and(std::vector<std::string>& line);
	void handle_or(std::vector<std::string>& line);
};

