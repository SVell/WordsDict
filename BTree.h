#pragma once

#include<iostream>
#include <vector>

#include "BTreeNode.h"
using std::string;

class BTree
{
    BTreeNode* root; // Pointer to root node 
    int t; // Minimum degree

	
public:
    // Constructor (Initializes tree as empty) 
    BTree(int _t)
    {
        root = NULL;  t = _t;
    }

    // function to traverse the tree 
    void traverse(string k, std::vector<string> addition)
    {
        if (root != NULL) root->traverse(k, addition);
    }

    // function to search a key in this tree 
    BTreeNode* search(string k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    // The main function that inserts a new key in this B-Tree 
    void insert(string k);

    void search_and_print(string k);

    void search_jocker(string k);
};