#pragma once
#include <string>
#include <vector>

using std::string;

class BTreeNode
{
    string* keys;
    int t;
    BTreeNode** C;
    int n;
    bool leaf;
public:
    
    BTreeNode(int _t, bool _leaf);

    void insertNonFull(string k);

    void splitChild(int i, BTreeNode* y);

    void traverse(string k, std::vector<string>);

    BTreeNode* search(string k);

    void search_and_print(string k);

    friend class BTree;
};