#include <iostream>
#include <filesystem>
#include <sstream>
#include <iterator>
#include <regex>
#include <fstream>
#include <functional>
#include "CreateDictionary.h"

using namespace std;
namespace fs = std::filesystem;

int wordsCount = 0;
int totalWordsCount = 0;

long long microseconds;

void Dictionary::createDict(const string &path) {
    const auto st = std::chrono::high_resolution_clock::now();

    string book;
    string p;

	for (const auto& file : fs::directory_iterator(path)) {
		
        p = file.path().string();
        book = p.substr(path.size()+1, p.size()- path.size() - 5);
        books.push_back(book);
        p.replace(path.size(), 1, "/");
        cout << p << endl;

        cout << "FileOpen" << endl;

		handleFile(p, book);
	}

    cout << "FileWrite" << endl;

    const auto elapsed = std::chrono::high_resolution_clock::now() - st;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    createOutputFile();
}


void Dictionary::handleFile(const string &path, string book) {
    fstream myFile;
    string line;

    myFile.open(path.c_str());

    word newWord;
    newWord.number = 1;
    newWord.books.push_back(book);

    vector<string> results;
	
    while (getline(myFile, line))
    {
        cleanString(line);

        istringstream iss(line);
        results.clear();
        copy((istream_iterator<string>(iss)), istream_iterator<string>(),back_inserter(results));


        for (int i = 0; i < results.size(); ++i) {

            totalWordsCount++;
        
            newWord.line = results[i];
            
            binarySearch(newWord, 0, words.size() - 1);
        }
    }
}

void Dictionary::binarySearch(const word &word,const int l, const int r) {

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
            return binarySearch(word, l, mid - 1);
        }
        return binarySearch(word, mid+1, r);
    }


    insertWord(word);
}

void Dictionary::insertWord(const word &word) {
    for (auto it = words.begin(); it != words.end(); ++it) {
        if (word.line < (*it).line) {
            words.insert(it, word);
            wordsCount++;
            return;
        }
    }

    words.push_back(word);
    wordsCount++;
}

const regex symb("[^\\w\\s]");
string result;
void Dictionary::cleanString(string &word) {
    
    transform(word.begin(), word.end(), word.begin(), ::tolower);
	
    result.clear();
	
    regex_replace(std::back_inserter(result), word.begin(), word.end(), symb, " ");

    word = result;
}

void Dictionary::createOutputFile() {

    ofstream MyFile("Dictionary.txt");

    MyFile << "Time of execution: " << (double)microseconds/1000000 << "\n";
    MyFile << "Total Number of words: " << totalWordsCount << "\n";
    MyFile << "Unique Number of words: " << wordsCount << "\n";

    for (int i = 0; i < words.size(); ++i) {
        MyFile << "\"" << words[i].line << "\"" << " - Books: ";

        for (int j = 0; j < words[i].books.size() - 1; ++j) {
            MyFile << words[i].books[j] << ", ";
        }
        MyFile << words[i].books[words[i].books.size() - 1] << "; Count: " << words[i].number << "\n";
    }
}