#include "BTreeNode.h"

#include <iostream>

#include "BTree.h"


BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;

    keys = new string[2 * t - 1];
    C = new BTreeNode * [2 * t];
	
    n = 0;
}

std::vector<string> traverseRes;

void BTreeNode::traverse(string k, std::vector<string> addition)
{
    int i;
    for (i = 0; i < n; i++)
    {
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

        	if(!count(traverseRes.begin(), traverseRes.end(),res))
        	{
                bool passes = true;
                if(addition.size() > 2)
                {
	                for(int i = 1; i < addition.size() - 1; i++)
	                {
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

    if (leaf == false)
        C[i]->traverse(k, addition);
}

BTreeNode* BTreeNode::search(string k)
{
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(k);
}