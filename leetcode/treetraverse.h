//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_TREETRAVERSE_H
#define CPPSANDBOX_TREETRAVERSE_H


#include "../include/datastructure.h"

TreeNode* duplicateTree(TreeNode* root)
{
    if (root==NULL)
        return NULL;

    TreeNode* new_root = new TreeNode (root->value);
    new_root->leftP = duplicateTree(root->leftP);
    new_root->rightP = duplicateTree(root->rightP);

    return new_root;
}

void printDFS_preOrder (TreeNode* root)
{
    if (root==NULL)
        return;

    printTreeNode(root);
    printDFS_preOrder(root->leftP);
    printDFS_preOrder(root->rightP);
}

void printDFS_preOrder_stack (TreeNode* root)
{
    if (root==NULL)
        return;

    Tree_Stack tStack;
    tStack.push(root);

    while (!tStack.empty()) {
        const TreeNode* toPrint = tStack.top();
        tStack.pop();
        printTreeNode(toPrint);
        if(toPrint->rightP!=NULL)
            tStack.push(toPrint->rightP);
        if(toPrint->leftP!=NULL)
            tStack.push(toPrint->leftP);
    }
}

void printDFS_inOrder (TreeNode* root)
{
    if (root==NULL)
        return;

    printDFS_inOrder(root->leftP);
    printTreeNode(root);
    printDFS_inOrder(root->rightP);
}

void printDFS_inOrder_stack (const TreeNode* root)
{
    std::unordered_map<const TreeNode*, bool> popedNodes;

    if (root==NULL)
        return;

    Tree_Stack tStack;
    if(root->rightP!=NULL)
        tStack.push(root->rightP);
    tStack.push(root);
    if(root->leftP!=NULL)
        tStack.push(root->leftP);
    popedNodes.emplace(root, true);

    while (!tStack.empty()) {
        const TreeNode* toPrint = tStack.top();
        tStack.pop();
        if (popedNodes.find(toPrint) != popedNodes.end())
        {
            printTreeNode(toPrint);
        }
        else
        {
            if(toPrint->rightP!=NULL)
                tStack.push(toPrint->rightP);
            tStack.push(toPrint);
            popedNodes.emplace(toPrint, true);
            if(toPrint->leftP!=NULL)
                tStack.push(toPrint->leftP);
        }
    }
}

void printDFS_postOrder (TreeNode* root)
{
    if (root==NULL)
        return;

    printDFS_postOrder(root->leftP);
    printDFS_postOrder(root->rightP);
    printTreeNode(root);
}

void printBFS (TreeNode* root) {
    std::queue<TreeNode*> treenodes;

    if (root==NULL)
        return;

    treenodes.push(root);
    while(!treenodes.empty())
    {
        const TreeNode* toPrint = treenodes.front();
        treenodes.pop();
        printTreeNode(toPrint);
        if(toPrint->leftP!=NULL)
            treenodes.push(toPrint->leftP);
        if(toPrint->rightP!=NULL)
            treenodes.push(toPrint->rightP);
    }
}

void test_treeTraverse()
{
    TreeNode* root = constructTestTree2();

    printTree(root);
    printf("\n");
    printf("\n");

    printf("preOrder:\t");
    printDFS_preOrder(root);
    printf("\n");
    printf("preOrder stack:\t");
    printDFS_preOrder_stack(root);
    printf("\n");
    printf("inOrder:\t");
    printDFS_inOrder(root);
    printf("\n");
    printf("inOrder stack:\t");
    printDFS_inOrder_stack(root);
    printf("\n");
    printf("postOrder:\t");
    printDFS_postOrder(root);
    printf("\n");

    printf("BFS:\t");
    printBFS (root);
    printf("\n");

    printf("BFS:\t");
    TreeNode* another = duplicateTree(root);
    printBFS(another);
    freeTree(another);

    freeTree(root);
}

#endif //CPPSANDBOX_TREETRAVERSE_H
