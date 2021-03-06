#include "BTree.h"

#include <sstream>
#include <cstddef>

void BTree::insert(string k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode* s = new BTreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(string k)
{
    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y)
{
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n = n + 1;
}

void BTree::search_and_print(string k)
{
    BTreeNode* p = search(k);

	if(p == NULL)
	{
		std::cout << "No such word" << std::endl;
        return;
	}
	
    for (int i = 0; i < p->keys->size(); ++i)
    {
        string temp = p->keys[i];

        if (k == temp)
        {
            temp = temp.substr(0, temp.length() - 1);
            std::cout << temp << std::endl;
        }
    }
}

void BTree::search_bTree(string k)
{
    k.append("$");
	
    if(k.find('*') == string::npos)
    {
        search_and_print(k);
    	return;
    }

    std::stringstream test(k);
    string temp;
	
    std::vector<string> results;
	
    while (std::getline(test, temp, '*'))
    {
        results.push_back(temp);
    }

	if(results.size() > 2)
	{
        k = results[results.size() - 1] + results[0];

        traverse(k, results);
	}
    else
	{
		while (k[k.length() - 1] != '*')
		{
			k = k.substr(1, k.length()) + k.at(0);
		}

		k = k.substr(0, k.length() - 1);
		traverse(k, {});
	}
}