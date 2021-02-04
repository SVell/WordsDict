#pragma once

#include<iostream>
#include <vector>

#include "BTreeNode.h"
using std::string;

class BTree
{
    BTreeNode* root;
    int t;

	
public:
    BTree(int _t)
    {
        root = NULL;  t = _t;
    }

    void traverse(string k, std::vector<string> addition)
    {
        if (root != NULL) root->traverse(k, addition);
    }

    BTreeNode* search(string k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(string k);

    void search_and_print(string k);

    void search_bTree(string k);
};