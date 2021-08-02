//
// Created by ZhouP on 4/8/2019.
//

#ifndef CPPSANDBOX_LOWESTCOMMONANCESTER_H
#define CPPSANDBOX_LOWESTCOMMONANCESTER_H


// TODO_PATRICK

#include "../include/datastructure.h"

bool recurseTree(TreeNode* currentNode, TreeNode* p, TreeNode* q, TreeNode* & ancestor)
{
    // If reached the end of a branch, return false.
    if (currentNode == NULL) {
        return false;
    }

    int mid(0);
    mid += (currentNode == p)? 1: 0;
    mid += (currentNode == q)? 1: 0;

    // Left Recursion. If left recursion returns true, set left = 1 else 0
    int left = recurseTree(currentNode->leftP, p, q, ancestor) ? 1 : 0;

    // Right Recursion
    int right = recurseTree(currentNode->rightP, p, q, ancestor) ? 1 : 0;

//    // If the current node is one of p or q
//    int mid = (currentNode == p || currentNode == q) ? 1 : 0;


    // If any two of the flags left, right or mid become True
    if (mid + left + right >= 2) {
        ancestor = currentNode;
    }

    // Return true if any one of the three bool values is True.
    return (mid + left + right > 0);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Traverse the tree
    TreeNode* ancestor = NULL;
    recurseTree(root, p, q, ancestor);
    return ancestor;
}

void test_findLowestCommonAncestor()
{
    TreeNode* tn = constructTestTree1();

    printTree(tn);

    TreeNode* tn4 = tn->leftP->leftP;
    TreeNode* tn5 = tn->leftP->rightP;

    std::cout << "common ancestor of " << tn4->value << ',' << tn5->value << " is " << lowestCommonAncestor(tn, tn4, tn5)->value << std::endl;

    freeTree(tn);
}

#endif //CPPSANDBOX_LOWESTCOMMONANCESTER_H
