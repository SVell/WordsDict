// Constructor for BTreeNode class 
#include "BTreeNode.h"

#include <iostream>

#include "BTree.h"


BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property 
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys 
    // and child pointers 
    keys = new string[2 * t - 1];
    C = new BTreeNode * [2 * t];

    // Initialize the number of keys as 0 
    n = 0;
}
std::vector<string> traverseRes;
// Function to traverse all nodes in a subtree rooted with this node 
void BTreeNode::traverse(string k, std::vector<string> addition)
{
    // There are n keys and n+1 children, traverse through n keys 
    // and first n children 
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i], 
        // traverse the subtree rooted with child C[i]. 
        if (leaf == false)
            C[i]->traverse(k, addition);

        bool isEqual = true;

        if (k.length() > keys[i].length()) isEqual = false;
    	
        for (int j = 0; j < k.length() && j < keys[i].length(); ++j)
        {
            if (keys[i].at(j) != k.at(j))
            {
                isEqual = false;
                break;
            }
        }

        if (isEqual)
        {
            string res = keys[i];
        	
	        while(res[res.size() - 1] != '$')
        	{
                res = res.substr(1, res.length()) + res.at(0);
	        }

            res = res.substr(0, res.length() - 1);
            //std::cout << "Pepe" << std::endl;
            //std::cout << res << std::endl;

        	if(!count(traverseRes.begin(), traverseRes.end(),res))
        	{
                bool passes = true;
                if(addition.size() > 2)
                {
	                for(int i = 1; i < addition.size() - 1; i++)
	                {
		                //std::cout << addition[i] << std::endl;
                        string check = res;
                        check = check.substr(addition[0].size(), check.length() - addition[addition.size() - 1].size());
	                	
		                if(check.find(addition[i]) != string::npos)
		                {
                            traverseRes.push_back(res);
                            std::cout << res << std::endl;
		                }
	                }
                }
        		
                else
                {
                    traverseRes.push_back(res);
                    std::cout << res << std::endl;
                }
        	}
        }
    }

    // Print the subtree rooted with last child 
    if (leaf == false)
        C[i]->traverse(k, addition);
}

// Function to search key k in subtree rooted with this node 
BTreeNode* BTreeNode::search(string k)
{
    // Find the first key greater than or equal to k 
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If key is not found here and this is a leaf node 
    if (leaf == true)
        return NULL;

    // Go to the appropriate child 
    return C[i]->search(k);
}

void BTreeNode::search_and_print(string k)
{
    BTreeNode* p = search(k);

	for(int i = 0; i < p->keys->size(); ++i)
	{
        std::cout << p->keys[i] << std::endl;
	}
}