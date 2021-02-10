#include <filesystem>
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

    treeGrams.at("pep");
    // tree.search_bTree("yes");

	while(true)
	{
        string line;
        getline(cin, line);
        tree.search_bTree(line);
	}
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
                rearrange_word(l);
                create_TreeGram(l);
        	}
        }
    }
    myFile.close();
}

void Dictionary::rearrange_word(string l)
{
    l = "$" + l;
    tree.insert(l);
    for (int i = 0; i < l.length() - 1; ++i)
    {
        l = l.substr(1, l.length()) + l.at(0);
        tree.insert(l);
    }
}

void Dictionary::create_TreeGram(string l)
{
    string clearLine = l;
	
    l = "$" + l + "$";
	
    vector<string> keys;
	
    int i = 0;
    string temp;
    for(i; i < l.length() - 3; ++i)
    {
        temp += l.at(i);
        temp += l.at(i+1);
        temp += l.at(i+2);
    	
        keys.push_back(temp);
        temp.clear(); // Yet another comment
    }

    while (i < l.length())
    {
        temp += l[i];
        i++;
    }
    keys.push_back(temp);

	for(auto it = keys.cbegin(); it != keys.cend(); ++it)
	{
        auto p = treeGrams.find(*it);
        if(p != treeGrams.end())
        {
	        if(!count(p->second.lines.cbegin(), p->second.lines.cend(), clearLine))
			{
                p->second.lines.push_back(clearLine);
	        }
        }
        else
        {
            ThreeGram g;
            g.lines.push_back(clearLine);

            treeGrams.insert(make_pair(*it, g));
        }
	}
}