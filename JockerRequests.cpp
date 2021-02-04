#include <filesystem>
#include <chrono>
#include <iterator>
#include <fstream>
#include <iostream>
#include <sstream>


#include "BTree.h"
#include "Dictionary.h"

using namespace std;

namespace fs = std::filesystem;

BTree tree(3);

void Dictionary::create_bTree(const std::string& path)
{	
    long long microseconds;
    
    const auto st = std::chrono::high_resolution_clock::now();

    string bookName, bookPath;

    for (const auto& file : fs::directory_iterator(path)) {

        bookPath = file.path().string();
        bookName = bookPath.substr(path.size() + 1, bookPath.size() - path.size() - 5);
    	
        bookPath.replace(path.size(), 1, "/");

        cout << bookPath << endl;
        cout << "FileOpen" << endl;

        create_rearrangements(bookPath, bookName);
    }
	
    const auto elapsed = std::chrono::high_resolution_clock::now() - st;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    tree.search_jocker("y*a*s");
    //tree.traverse("r$jun");
}

void Dictionary::create_rearrangements(const std::string& path, std::string& book)
{
    fstream myFile;
    string line;

    myFile.open(path.c_str());

    int wordNum = 0;

    vector<string> results;

    while (getline(myFile, line))
    {
        clean_string(line);

        istringstream iss(line);
        results.clear();
        copy((istream_iterator<string>(iss)), istream_iterator<string>(), back_inserter(results));

        for (auto it = results.cbegin(); it != results.cend(); ++it) 
        {
        	if(tree.search(*it) == nullptr)
        	{
                string l = *it;
                l = "$" + l;
        		for(int i = 0; i < l.length() - 1; ++i)
        		{
                    l = l.substr(1, l.length()) + l.at(0);
                    tree.insert(l);
        		}
                
        	}
        }
    }
    myFile.close();
}