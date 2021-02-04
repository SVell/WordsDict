
// The main function that inserts a new key in this B-Tree 
#include "BTree.h"

#include <sstream>
#include <cstddef>

void BTree::insert(string k)
{
    // If tree is empty 
    if (root == NULL)
    {
        // Allocate memory for root 
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insert key 
        root->n = 1;  // Update number of keys in root 
    }
    else // If tree is not empty 
    {
        // If root is full, then tree grows in height 
        if (root->n == 2 * t - 1)
        {
            // Allocate memory for new root 
            BTreeNode* s = new BTreeNode(t, false);

            // Make old root as child of new root 
            s->C[0] = root;

            // Split the old root and move 1 key to the new root 
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root 
            root = s;
        }
        else  // If root is not full, call insertNonFull for root 
            root->insertNonFull(k);
    }
}

// A utility function to insert a new key in this node 
// The assumption is, the node must be non-full when this 
// function is called 
void BTreeNode::insertNonFull(string k)
{
    // Initialize index as index of rightmost element 
    int i = n - 1;

    // If this is a leaf node 
    if (leaf == true)
    {
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location 
        keys[i + 1] = k;
        n = n + 1;
    }
    else // If this node is not leaf 
    {
        // Find the child which is going to have the new key 
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full 
        if (C[i + 1]->n == 2 * t - 1)
        {
            // If the child is full, then split it 
            splitChild(i + 1, C[i + 1]);

            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node 
// Note that y must be full when this function is called 
void BTreeNode::splitChild(int i, BTreeNode* y)
{
    // Create a new node which is going to store (t-1) keys 
    // of y 
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z 
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z 
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    // Reduce the number of keys in y 
    y->n = t - 1;

    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // Link the new child to this node 
    C[i + 1] = z;

    // A key of y will move to this node. Find the location of 
    // new key and move all greater keys one space ahead 
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy the middle key of y to this node 
    keys[i] = y->keys[t - 1];

    // Increment count of keys in this node 
    n = n + 1;
}

void BTree::search_and_print(string k)
{
    BTreeNode* p = search(k);

	if(p == nullptr) return;

    for (int i = 0; i < p->n; ++i)
    {
        std::cout << p->keys[i] << std::endl;
    }
}

void BTree::search_jocker(string k)
{
    k.append("$");

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
	}
    else
    {
        while (k[k.length() - 1] != '*')
        {
            k = k.substr(1, k.length()) + k.at(0);
        }

        k = k.substr(0, k.length() - 1);
    }
	
	
    std::cout << k << std::endl;
    traverse(k, results);
}