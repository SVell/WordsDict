#pragma once

#include <map>
#include <string>
#include <vector>
#include <windows.h>

#include "Structs.h"

class Dictionary
{
public:
	// All words and books from files
	std::vector<word> words;
	std::vector<word> twoWordIndex;
	std::vector<std::string> books;

	std::map<std::string, ThreeGram> treeGrams;

	// Main public methods
	void create_dict(const std::string& path);
	void handle_request(const request req, std::string &line, int range = 0);
	void handle_boolean_search(const request req, std::vector<std::string>& line);

	void create_bTree(const std::string& path);

private:
	void handle_file(const std::string& path, std::string &book);
	// Insertion binary search
	void binary_search(const word& w, const int l, const int r, std::vector<word>& container);
	void insert_word(const word& w, std::vector<word> &container);
	void clean_string(std::string& word);
	void create_output_file();

	void create_rearrangements(const std::string& path);

	// Binary search by word
	int binary_search_word(const std::string& w, const int l, const int r, std::vector<word>& container);

	// Search
	void search_phrase(std::string& line);
	void search_phrase_two(std::string& line);
	std::vector<std::string> search_range(std::string& line, int range);
	std::vector<std::string> search_range_two(std::string& line, int range);
	std::vector<std::string> search_two_words(std::string& line);

	// Boolean Search
	void handle_not(std::vector<std::string>& line);
	void handle_and(std::vector<std::string>& line);
	void handle_or(std::vector<std::string>& line);

	// Word Rearrangement
	void create_TreeGram(std::string l);
	void rearrange_word(std::string l);
};

