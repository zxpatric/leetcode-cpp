//
// Created by ZhouP on 4/5/2019.
//

#ifndef CPPSANDBOX_PRINTVETICAL_H
#define CPPSANDBOX_PRINTVETICAL_H

#include "../include/datastructure.h"

void collectNodeInfo (TreeNode* root, int value, ValueNodes& mapValueNodes)
{
    mapValueNodes.emplace (value, root);
    if (root->leftP!=NULL)
        collectNodeInfo (root->leftP, value-1, mapValueNodes);
    if (root->rightP!=NULL)
        collectNodeInfo (root->rightP, value+1, mapValueNodes);
}

void printTreeVertical (TreeNode* root)
{
    ValueNodes mapValueNodes;
    collectNodeInfo (root, 0, mapValueNodes);

    Ints keys;
    keys.reserve(mapValueNodes.size());
    std::for_each(mapValueNodes.begin(), mapValueNodes.end(), [&](auto key_value){if(keys.end()==std::find(keys.begin(), keys.end(), key_value.first))keys.push_back(key_value.first);});
    std::sort(keys.begin(), keys.end());

    for (int key : keys)
    {
        auto iter = mapValueNodes.equal_range(key);
        std::for_each(iter.first, iter.second, [](auto key_value) {printf("%d, ", key_value.second->value);});
        printf("\n");
    }
}


void findMinMax(TreeNode *node, int *min, int *max, int hd)
{
    // Base case
    if (node == NULL) return;

    // Update min and max
    if (hd < *min)  *min = hd;
    else if (hd > *max) *max = hd;

    // Recur for left and right subtrees
    findMinMax(node->leftP, min, max, hd-1);
    findMinMax(node->rightP, min, max, hd+1);
}

// A utility function to print all nodes on a given line_no.
// hd is horizontal distance of current node with respect to root.
void printVerticalLine(TreeNode *node, int line_no, int hd)
{
    // Base case
    if (node == NULL) return;

    // If this node is on the given line number
    if (hd == line_no)
        std::cout << node->value << " ";

    // Recur for left and right subtrees
    printVerticalLine(node->leftP, line_no, hd-1);
    printVerticalLine(node->rightP, line_no, hd+1);
}

// The main function that prints a given binary tree in
// vertical order
void printInVerticalOrder(TreeNode *root)
{
    // Find min and max distances with resepect to root
    int min = 0, max = 0;
    findMinMax(root, &min, &max, 0);

    // Iterate through all possible vertical lines starting
    // from the leftmost line and print nodes line by line
    for (int line_no = min; line_no <= max; line_no++)
    {
        printVerticalLine(root, line_no, 0);
        std::cout << std::endl;
    }
}


void test_printBinaryTreeVertical()
{
    TreeNode* root = constructTestTree1();
    printTree(root);

//    printTreeVertical(root);
    printInVerticalOrder (root);

    // you may count the range first. For example [-2, 2], then traverse through the tree to collect node associated with specific value

    freeTree(root);
}

#endif //CPPSANDBOX_PRINTVETICAL_H
