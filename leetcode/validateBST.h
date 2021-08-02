//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_VALIDATEBST_H
#define CPPSANDBOX_VALIDATEBST_H

#include "../include/datastructure.h"

bool internal_validateRightBST(TreeNode* root, int value);

bool internal_validateLeftBST(TreeNode* root, int value)
{
    if(root==NULL)
        return true;

    if ((root->leftP==NULL || (root->leftP->value <= root->value && root->leftP->value<=value)) && (root->rightP==NULL || root->rightP->value >= root->value && root->rightP->value<=value))
    {
        return internal_validateLeftBST(root->leftP, root->value) && internal_validateRightBST(root->rightP, root->value);
    }
    else
    {
        return false;
    }
}

bool internal_validateRightBST(TreeNode* root, int value)
{
    if(root==NULL)
        return true;

    if ((root->leftP==NULL || (root->leftP->value <= root->value && root->leftP->value>=value)) && (root->rightP==NULL || root->rightP->value >= root->value && root->rightP->value>=value))
    {
        return internal_validateLeftBST(root->leftP, root->value) && internal_validateRightBST(root->rightP, root->value);
    }
    else
    {
        return false;
    }
}

bool validateBST(TreeNode* root)
{
    if (root==NULL||root->leftP==NULL&&root->rightP==NULL)
    {
        return true;
    }
    else
    {
        int value = root->value;
        if ((root->leftP==NULL || root->leftP->value <= value) && (root->rightP==NULL || root->rightP->value >= value)) {
            return internal_validateLeftBST(root->leftP, value) && internal_validateRightBST(root->rightP, value);
        }
        else
        {
            return false;
        }
    }
}

void test_validateBST()
{
    // validate a tree is a binary search tree

    TreeNode* tree1 = constructTestTree1();
    printTree(tree1);

    TreeNode* tree2 = constructTestTree2();
    printTree(tree2);

    TreeNode* tree3 = constructTestTree3();
    printTree(tree3);

    printf("Tree 1 is %s\n", validateBST(tree1)? "a binary search tree" : " not a binary search tree");
    printf("Tree 2 is %s\n", validateBST(tree2)? "a binary search tree" : " not a binary search tree");
    printf("Tree 3 is %s\n", validateBST(tree3)? "a binary search tree" : " not a binary search tree");

    freeTree(tree1);
    freeTree(tree2);
    freeTree(tree3);
}

#endif //CPPSANDBOX_VALIDATEBST_H
