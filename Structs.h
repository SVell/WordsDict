#pragma once

enum request
{
	PHRASE,
	RANGE,
	TWOWORDS,
	TWOPAIRS,
	NOT,
	OR,
	AND,
	ONE
};

struct book
{
	std::string name;
	std::vector<int> positions;
};

// Main struct
struct word {
	std::string line;
	int number = 0;
	std::vector<book> books;
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