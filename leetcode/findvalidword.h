//
// Created by ZhouP on 3/16/2019.
//

#ifndef CPPSANDBOX_FINDVALIDWORD_H
#define CPPSANDBOX_FINDVALIDWORD_H


//Trie
//
//Trie is an efficient data structure for searching words in dictionaries, search complexity with Trie is linear in terms of word (or key) length to be searched. If we store keys in binary search tree, a well balanced BST will need time proportional to M * log N, where M is maximum string length and N is number of keys in tree. Using trie, we can search the key in O(M) time. So it is much faster than BST.
//
//Hashing also provides word search in O(n) time on average. But the advantages of Trie are there are no collisions (like hashing) so worst case time complexity is O(n). Also, the most important thing is Prefix Search. With Trie, we can find all words beginning with a prefix (This is not possible with Hashing). The only problem with Tries is they require a lot of extra space.

//The most common use of Tries is to implement dictionaries due to prefix search capability. Tries are also well suited for implementing approximate matching algorithms, including those used in spell checking. It is also used for searching Contact from Mobile Contact list OR Phone Directory.


// C++ program to print all valid words that
// are possible using character of array
#include<bits/stdc++.h>
using namespace std;

// Converts key current character into index
// use only 'a' through 'z'
#define char_int(c) ((int)c - (int)'a')

//converts current integer into character
#define int_to_char(c) ((char)c + (char)'a')

// Alphabet size
#define SIZE (26)

// trie Node
struct TrieNode
{
    TrieNode *Child[SIZE];

    // isLeaf is true if the node represents
    // end of a word
    bool leaf;
};

// Returns new trie node (initialized to NULLs)
TrieNode *getNode()
{
    TrieNode * newNode = new TrieNode;
    newNode->leaf = false;
    for (int i =0 ; i< SIZE ; i++)
        newNode->Child[i] = NULL;
    return newNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(TrieNode *root, char *Key)
{
    int n = strlen(Key);
    TrieNode * pChild = root;

    for (int i=0; i<n; i++)
    {
        int index = char_int(Key[i]);

        if (pChild->Child[index] == NULL)
            pChild->Child[index] = getNode();

        pChild = pChild->Child[index];
    }

    // make last node as leaf node
    pChild->leaf = true;
}

// A recursive function to print all possible valid
// words present in array
void searchWord(TrieNode *root, bool Hash[], string str)
{
    // if we found word in trie / dictionary
    if (root->leaf == true)
        cout << str << endl ;

    // traverse all child's of current root
    for (int K =0; K < SIZE; K++)
    {
        if (Hash[K] == true && root->Child[K] != NULL )
        {
            // add current character
            char c = int_to_char(K);

            // Recursively search reaming character of word
            // in trie
            searchWord(root->Child[K], Hash, str + c);
        }
    }
}

// Prints all words present in dictionary.
void PrintAllWords(char Arr[], TrieNode *root, int n)
{
    // create a 'has' array that will store all present
    // character in Arr[]
    bool Hash[SIZE];

    for (int i = 0 ; i < n; i++)
        Hash[char_int(Arr[i])] = true;

    // tempary node
    TrieNode *pChild = root ;

    // string to hold output words
    string str = "";

    // Traverse all matrix elements. There are only 26
    // character possible in char array
    for (int i = 0 ; i < SIZE ; i++)
    {
        // we start searching for word in dictionary
        // if we found a character which is child
        // of Trie root
        if (Hash[i] == true && pChild->Child[i] )
        {
            str = str+(char)int_to_char(i);
            searchWord(pChild->Child[i], Hash, str);
            str = "";
        }
    }
}

//Driver program to test above function
int test_findvalidword()
{
    // Let the given dictionary be following
    char Dict[][20] = {"go", "bat", "me", "eat",
                       "goal", "boy", "run"} ;

    // Root Node of Trie
    TrieNode *root = getNode();

    // insert all words of dictionary into trie
    int n = sizeof(Dict)/sizeof(Dict[0]);
    for (int i=0; i<n; i++)
        insert(root, Dict[i]);

    char arr[] = {'e', 'o', 'b', 'a', 'm', 'g', 'l'} ;
    int N = sizeof(arr)/sizeof(arr[0]);

    PrintAllWords(arr, root, N);

    return 0;
}


#endif //CPPSANDBOX_FINDVALIDWORD_H
