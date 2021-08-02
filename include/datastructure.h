//
// Created by ZhouP on 3/8/2019.
//

#ifndef CPPSANDBOX_DATASTRUCTURE_H
#define CPPSANDBOX_DATASTRUCTURE_H

#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>
#include <cstdarg>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <list>
#include <forward_list>


typedef std::vector<bool> Bools;
typedef std::vector<int> Ints;
typedef unsigned int UInt;
typedef std::vector<unsigned int> UInts;
typedef std::vector<long> Longs;
typedef std::vector<float> Floats;
typedef std::vector<double> Doubles;
typedef std::vector<std::string> Strings;

typedef std::pair<int,int> IntPair;
typedef std::set<int> UniqueInts;
typedef std::vector<IntPair> IntPairs;
typedef std::forward_list<int> FLInts;

Ints sorted_ints_rotated = {7, 8, 11, 1, 2, 4};
Ints sorted_ints = {1, 2, 4, 7, 8, 11};
Ints unsorted_ints = {5, 2, 4, 7, 11, 8, 6};
UInts unsorted_uints = {5, 2, 4, 7, 11, 8, 6};
Ints unsorted_intss = {5, 2, 4, 5, 7, 11, 2, 8, 6, 9, 11};
Ints very_unsorted_ints = {9, 8, 7, 6, 5, 4, 3, 2, 1};
Longs unsorted_longs = {5, 2, 4, 7, 11, 8, 6};

struct LinkNode
{
    LinkNode (int v): val(v), nextP(NULL){}

    int val;
    LinkNode* nextP;
};

typedef LinkNode ListNode;

void printLinkedList (LinkNode const *node)
{
//    std::cout<<"Linked list values:"<<std::endl;
    printf ("Linked list values:");
    while (node!=NULL)
    {
//        std::cout<<node->val<<',';
        printf ("%d, ", node->val);
        node = node->nextP;
    }
//    std::cout<<std::endl;
//    std::cout.flush();
    printf ("\n");
}

void freeLinkedList (LinkNode* node)
{
    LinkNode* toDelete;
    while (node!=NULL)
    {
        toDelete = node;
        node = node->nextP;
        delete(toDelete);
    }
}

LinkNode* constructLinkedList (Ints testdata)
{
    LinkNode parent(0);
    LinkNode* parentP = &parent;
    for (int v : testdata)
    {
        parentP->nextP = new LinkNode(v);
        parentP = parentP->nextP;
    }

    return parent.nextP;
}

typedef std::vector<LinkNode*> LinkedLists;


struct TreeNode
{
    TreeNode (int v): value(v), leftP(NULL), rightP(NULL) {}

    int value;
    TreeNode* leftP;
    TreeNode* rightP;
};

typedef std::stack<const TreeNode*> Tree_Stack;
typedef std::queue<const TreeNode*> Tree_Queue;

TreeNode* constructTestTree1()
{
    TreeNode* parent = new TreeNode(1);
    TreeNode* left = new TreeNode(2);
    TreeNode* right = new TreeNode(3);

    parent->leftP = left;
    parent->rightP = right;

    TreeNode* left_left = new TreeNode(4);
    TreeNode* left_right = new TreeNode(5);
    left->leftP = left_left;
    left->rightP = left_right;

    TreeNode* right_left = NULL;
    TreeNode* right_right = new TreeNode(7);
    right->leftP = right_left;
    right->rightP = right_right;

    return parent;
}


TreeNode* constructTestTree2()
{
    TreeNode* parent = new TreeNode(5);
    TreeNode* left = new TreeNode(4);
    TreeNode* right = new TreeNode(8);

    parent->leftP = left;
    parent->rightP = right;

    TreeNode* left_left = new TreeNode(3);
    TreeNode* left_right = new TreeNode(6);
    left->leftP = left_left;
    left->rightP = left_right;

    TreeNode* right_left = new TreeNode(7);
    TreeNode* right_right = new TreeNode(9);
    right->leftP = right_left;
    right->rightP = right_right;

    return parent;
}

TreeNode* constructTestTree3()
{
    TreeNode* parent = new TreeNode(5);
    TreeNode* left = new TreeNode(4);
    TreeNode* right = new TreeNode(6);

    parent->leftP = left;
    parent->rightP = right;

    TreeNode* left_left = new TreeNode(4);
    TreeNode* left_right = new TreeNode(5);
    left->leftP = left_left;
    left->rightP = left_right;

    TreeNode* right_left = NULL;
    TreeNode* right_right = new TreeNode(7);
    right->leftP = right_left;
    right->rightP = right_right;

    return parent;
}


TreeNode* constructTestTree4()
{
    TreeNode* parent = new TreeNode(5);
    TreeNode* left = new TreeNode(4);
    TreeNode* right = new TreeNode(4);

    parent->leftP = left;
    parent->rightP = right;

    TreeNode* left_left = new TreeNode(2);
    TreeNode* left_right = new TreeNode(3);
    left->leftP = left_left;
    left->rightP = left_right;

    TreeNode* right_left = new TreeNode(3);
    TreeNode* right_right = new TreeNode(2);
    right->leftP = right_left;
    right->rightP = right_right;

    return parent;
}

void printTreeNode (const TreeNode* root)
{
    if (root->value == std::numeric_limits<int>::max())
    {
        printf ("X,", root->value);
    }
    else
    {
        printf ("%d,", root->value);
    }
}

void printTree (const TreeNode* root)
{
    // print in the console auto-adapt as such as?
    //          1
    //      2      3
    //    4   5  X   7

    std::queue<const TreeNode*> treenodes_left;
    std::queue<const TreeNode*> treenodes_right;
    int level = 0;

    if (root==NULL)
        return;

    TreeNode empty(std::numeric_limits<int>::max());
    treenodes_left.push(root);
    while(!treenodes_left.empty() || !treenodes_right.empty())
    {
        if (!treenodes_left.empty())
        {
            while (!treenodes_left.empty())
            {
                const TreeNode* toPrint = treenodes_left.front();
                treenodes_left.pop();
                printTreeNode(toPrint); //printf("|");

                if(toPrint->leftP!=NULL || toPrint->rightP!=NULL)
                {
                    if(toPrint->leftP!=NULL)
                        treenodes_right.push(toPrint->leftP);
                    else
                        treenodes_right.push(&empty);
                    if(toPrint->rightP!=NULL)
                        treenodes_right.push(toPrint->rightP);
                    else
                        treenodes_right.push(&empty);
                }
            }
            printf ("\n");
            ++level;
        }
        else
        {
            while (!treenodes_right.empty())
            {
                const TreeNode* toPrint = treenodes_right.front();
                treenodes_right.pop();
                printTreeNode(toPrint);

                if(toPrint->leftP!=NULL || toPrint->rightP!=NULL)
                {
                    if (toPrint->leftP != NULL)
                        treenodes_left.push(toPrint->leftP);
                    else
                        treenodes_left.push(&empty);
                    if (toPrint->rightP != NULL)
                        treenodes_left.push(toPrint->rightP);
                    else
                        treenodes_left.push(&empty);
                }
            }
            printf ("\n");
            ++level;
        }
    }
    printf ("Tree's deepest level is %d\n", level);
}


void freeTree (TreeNode* root)
{
    if (root==NULL)
        return;

    if (root->leftP)
        freeTree(root->leftP);

    if (root->rightP)
        freeTree(root->rightP);

    delete root;
}

template<typename T>
void printVector(const std::vector<T> &values) {

    printf ("Vector values:");
    for (const T& val : values)
    {
//        if constexpr (std::is_same_v<T, int>) {
//            printf("%d, ", val);
//        }

        std::cout << val << ",";
    }
    printf ("\n");
}

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T> &values) {
  out << "Vector values:";
  for (const T& val : values)
  {
    out << val << ",";
  }
  out << std::endl;

  return out;
}


template <typename T>
std::ostream& operator << (std::ostream& out, const std::forward_list<T> &values) {
  out << "Linked list values:";
  for (const T& val : values)
  {
    out << val << ",";
  }
  out << std::endl;
  return out;
}


class GraphNode;
typedef std::vector<GraphNode*> GNodes;
typedef std::queue<GraphNode*> QGNodes;
typedef std::stack<GraphNode*> SGNodes;
typedef std::unordered_map<GraphNode*, bool> HTGNodes;
typedef std::pair<GraphNode*, bool> NodePair;
typedef std::unordered_map<GraphNode*, GraphNode*> HSTwoGNodes;
typedef std::pair<GraphNode*, GraphNode*> TwoNodePair;
typedef std::unordered_multimap<int, TreeNode*> ValueNodes;

typedef std::unordered_set <GraphNode*> HSGNodes;       // shall use hash set instead of hash table
typedef std::unordered_set <int> HSInt;       // shall use hash set instead of hash table

class GraphNode {
public:
    int val;
    GNodes neighbors;

    GraphNode(int _val) : val(_val) {}

    GraphNode(int _val, std::vector<GraphNode*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }

    GraphNode(int _val, int count, ...) : val(_val)
    {
        va_list args;
        va_start(args, _val);
//        while(true)
        for(int i=0;i<count;++i)
        {
            try
            {
                GraphNode* node = va_arg(args, GraphNode*);
                if (node != NULL)
                {
                    neighbors.push_back(node);
                }
            }
            catch (...)
            {
//                break;
                continue;
            }
        }
        va_end(args);
    }

    void addNeighbor(int count, ...)
    {
        va_list args;
        va_start(args, count);
        for(int i=0;i<count;++i)
        {
            GraphNode* node = va_arg(args, GraphNode*);
            if (node != NULL)
            {
                neighbors.push_back(node);
            }
        }
        va_end(args);
    }

//    GNodes::iterator neighborIterator() {
//        return neighbors.begin();
//    }
};

GraphNode* constructTestGraph()
{
//    {"$id":"1","neighbors":[{
// "$id":"2","neighbors":[{"$ref":"1"},
// {"$id":"3","neighbors":[{"$ref":"2"},
// {"$id":"4","neighbors":[{"$ref":"3"},{"$ref":"1"}],"val":4}],"val":3}],"val":2},{"$ref":"4"}],"val":1}

    GraphNode *nodeP1 = new GraphNode(1);
    GraphNode *nodeP2 = new GraphNode(2);
    GraphNode *nodeP3 = new GraphNode(3);
    GraphNode *nodeP4 = new GraphNode(4);

    nodeP1->addNeighbor(1, nodeP2, nodeP4);
    nodeP2->addNeighbor(2, nodeP1, nodeP3);
    nodeP3->addNeighbor(3, nodeP2, nodeP4);
    nodeP4->addNeighbor(4, nodeP3, nodeP1);

    return nodeP2;
}

void printGraphBFS (GraphNode* gNode)
{
    HSGNodes hs_nodes;

    QGNodes queue_nodes;
    queue_nodes.push(gNode);
    hs_nodes.emplace(gNode);

    while (!queue_nodes.empty())
    {
        GraphNode* aNode = queue_nodes.front();
        queue_nodes.pop();
        printf("%d,", aNode->val);
//        auto iter = aNode->neighborIterator();
        for (GraphNode* gNode : aNode->neighbors)
        {
            if (hs_nodes.find(gNode) != hs_nodes.end())
                continue;
            else
            {
                hs_nodes.emplace(gNode);
                queue_nodes.push(gNode);
            }
        }
    }
    printf("\n");
}

void printGraphDFS (GraphNode* gNode)
{
    HSGNodes hs_nodes;

    SGNodes stack_nodes;
    stack_nodes.push(gNode);
    hs_nodes.emplace(gNode);

    while (!stack_nodes.empty())
    {
        GraphNode* aNode = stack_nodes.top();
        stack_nodes.pop();
        printf("%d,", aNode->val);
//        auto iter = aNode->neighborIterator();
        for (GraphNode* gNode : aNode->neighbors)
        {
            if (hs_nodes.find(gNode) != hs_nodes.end())
                continue;
            else
            {
                hs_nodes.emplace(gNode);
                stack_nodes.push(gNode);
            }
        }
    }
    printf("\n");
}

void internal_printGraphDFSRecursive (GraphNode* gNode, HSGNodes& hs_nodes)
{
    if (hs_nodes.find(gNode)!=hs_nodes.end())
    {
        return;
    }
    else
    {
        printf("%d,", gNode->val);
        hs_nodes.emplace(gNode);
    }

    for(GraphNode* childNode : gNode->neighbors)
    {
        internal_printGraphDFSRecursive (childNode, hs_nodes);
    }
}

void printGraphDFSRecursive (GraphNode* gNode)
{
    HSGNodes hs_nodes;
    internal_printGraphDFSRecursive(gNode, hs_nodes);
}

void printGraph(GraphNode* gNode)
{
    printf("Graph BFS:\t");printGraphBFS (gNode);printf("\n");
    printf("Graph DFS Stack:\t");printGraphDFS (gNode);printf("\n");
    printf("Graph DFS Recursive:\t");printGraphDFSRecursive (gNode);printf("\n");
}

void freeGraph(GraphNode* gNode)
{
    HTGNodes hs_nodes;

    QGNodes queue_nodes;
    queue_nodes.push(gNode);
    hs_nodes.emplace(gNode, true);

    while (!queue_nodes.empty())
    {
        GraphNode* aNode = queue_nodes.front();
        queue_nodes.pop();
//        auto iter = aNode->neighborIterator();
        for (GraphNode* gNode : aNode->neighbors)
        {
            if (hs_nodes.find(gNode) != hs_nodes.end())
                continue;
            else
            {
                hs_nodes.emplace(gNode, true);
                queue_nodes.push(gNode);
            }
        }
    }

    printf("Free Graph:\t");
    std::for_each(hs_nodes.begin(), hs_nodes.end(), [&](NodePair node_pair){printf("%d,", node_pair.first->val);delete node_pair.first;});
    printf("\n");
}


class TrieNode {
public:
    bool m_isWord;
    std::vector<TrieNode*> m_children;

    TrieNode () : m_isWord(false), m_children(26, NULL) {}
    virtual ~TrieNode ()
    {
        if (m_isWord)
            return;

        for (TrieNode* tn : m_children)
        {
            if (tn!=NULL)
                delete tn;
        }
    }
};

class Trie {
public:
    TrieNode* m_rootP;
    void insert(std::string word) {
        TrieNode* cur = m_rootP;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (cur->m_children[index] == NULL) {
                cur->m_children[index] = new TrieNode();
            }
            cur = cur->m_children[index];
            if (i == word.length() - 1)
                cur->m_isWord = true;
        }
    }

    bool search(std::string word) const {
        TrieNode* cur = m_rootP;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (cur->m_children[index] == NULL)
                return false;
            else {
                if (i == word.length() - 1)
                    return cur->m_children[index]->m_isWord;
                else {
                    cur = cur->m_children[index];
                }
            }
        }
        return false;
    }

    bool startsWith(std::string word) const {
        TrieNode* cur = m_rootP;
        for (int i = 0; i < word.length(); i++) {
            int index = word[i] - 'a';
            if (cur->m_children[index] == NULL) {
                return false;
            }
            cur = cur->m_children[index];
        }
        return true;
    }

    Trie ()
    {
        m_rootP = new TrieNode();
    }

    virtual ~Trie ()
    {
        delete m_rootP;
    }

};


#endif //CPPSANDBOX_DATASTRUCTURE_H
