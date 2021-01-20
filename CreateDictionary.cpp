#include <iostream>
#include <filesystem>
#include <sstream>
#include <iterator>
#include <regex>
#include <fstream>
#include <functional>
#include "Dictionary.h"

using namespace std;
namespace fs = std::filesystem;

int words_count = 0;
int total_words_count = 0;

long long microseconds;

void Dictionary::create_dict(const string &path) {
    const auto st = std::chrono::high_resolution_clock::now();

    string bookName, bookPath;

	for (const auto& file : fs::directory_iterator(path)) {
		
        bookPath = file.path().string();
        bookName = bookPath.substr(path.size()+1, bookPath.size()- path.size() - 5);
        books.push_back(bookName);
        bookPath.replace(path.size(), 1, "/");
        cout << bookPath << endl;

        cout << "FileOpen" << endl;

		handle_file(bookPath, bookName);
	}

    cout << "FileWrite" << endl;

    const auto elapsed = std::chrono::high_resolution_clock::now() - st;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    create_output_file();
}


void Dictionary::handle_file(const string &path, string &book) {
    fstream myFile;
    string line;

    myFile.open(path.c_str());

    word newWord;
    newWord.number = 1;
    newWord.books.push_back(book);

    vector<string> results;
	
    while (getline(myFile, line))
    {
        clean_string(line);

        istringstream iss(line);
        results.clear();
        copy((istream_iterator<string>(iss)), istream_iterator<string>(),back_inserter(results));


        for (int i = 0; i < results.size(); ++i) {

            total_words_count++;
        
            newWord.line = results[i];
            
            binary_search(newWord, 0, words.size() - 1);
        }
    }
}

void Dictionary::binary_search(const word &word,const int l, const int r) {

    if (r >= l) {
        int mid = l + (r - l) / 2;
     
        if (words[mid].line == word.line) {

            words[mid].number++;

            if (!count(words[mid].books.begin(), words[mid].books.end(), word.books[0])) {
                words[mid].books.push_back(word.books[0]);
            }
            return;
        }

        if (words[mid].line > word.line) {
            return binary_search(word, l, mid - 1);
        }
        return binary_search(word, mid+1, r);
    }


    insert_word(word);
}

void Dictionary::insert_word(const word &word) {
    for (auto it = words.begin(); it != words.end(); ++it) {
        if (word.line < (*it).line) {
            words.insert(it, word);
            words_count++;
            return;
        }
    }

    words.push_back(word);
    words_count++;
}

const regex symb("[^\\w\\s]");
string result;
void Dictionary::clean_string(string &word) {
    
    transform(word.begin(), word.end(), word.begin(), ::tolower);
	
    result.clear();
	
    regex_replace(std::back_inserter(result), word.begin(), word.end(), symb, " ");

    word = result;
}

void Dictionary::create_output_file() {

    ofstream MyFile("Dictionary.txt");

    MyFile << "Time of execution: " << (double)microseconds/1000000 << "\n";
    MyFile << "Total Number of words: " << total_words_count << "\n";
    MyFile << "Unique Number of words: " << words_count << "\n";

    for (int i = 0; i < words.size(); ++i) {
        MyFile << "\"" << words[i].line << "\"" << " - Books: ";

        for (int j = 0; j < words[i].books.size() - 1; ++j) {
            MyFile << words[i].books[j] << ", ";
        }
        MyFile << words[i].books[words[i].books.size() - 1] << "; Count: " << words[i].number << "\n";
    }
}