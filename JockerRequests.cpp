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
    string bookPath;

    for (const auto& file : fs::directory_iterator(path)) {

        bookPath = file.path().string();
    	
        bookPath.replace(path.size(), 1, "/");

        cout << bookPath << endl;
        cout << "FileOpen" << endl;

        create_rearrangements(bookPath);
    }

    tree.search_bTree("yes");
}

void Dictionary::create_rearrangements(const std::string& path)
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