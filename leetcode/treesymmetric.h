//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_TREESYMMETRIC_H
#define CPPSANDBOX_TREESYMMETRIC_H

#include "../include/datastructure.h"

bool internal_isSubTreeSymmetric(TreeNode* left, TreeNode* right)
{
    if (left==NULL && right==NULL)
    {
        return true;
    }
    else if (left!=NULL && right!=NULL)
    {
        return left->value == right->value && internal_isSubTreeSymmetric (left->leftP, right->rightP) && internal_isSubTreeSymmetric (right->leftP, left->rightP);
    }
    else
    {
        return false;
    }
}

bool isTreeSymmetric_Recursive(TreeNode* root)
{
    if (root==NULL)
        return true;

    //compare root->left vs root->right
    return internal_isSubTreeSymmetric(root->leftP, root->rightP);
}

bool isTreeSymmetric_iterative(const TreeNode* root) {
    if (root==NULL)
        return true;

    Tree_Stack sLeft;
    Tree_Stack sRight;
    sLeft.push(root->leftP);
    sRight.push(root->rightP);

    const TreeNode* left(NULL);
    const TreeNode* right(NULL);

    while (!sLeft.empty()&&!sRight.empty())
    {
        left = sLeft.top();
        right = sRight.top();
        sLeft.pop();
        sRight.pop();

        if (left==NULL && right==NULL)
        {

        }
        else if (left!=NULL && right!=NULL && left->value == right->value)
        {
            // push order matters
            sLeft.push(left->leftP);
            sLeft.push(right->leftP);

            sRight.push(right->rightP);
            sRight.push(left->rightP);
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool isTreeSymmetric(TreeNode* root) {
//    return isTreeSymmetric_Recursive(root);
    return isTreeSymmetric_iterative(root);
}

void test_treeSymmetric()
{
    TreeNode* tree1 = constructTestTree1();
    printTree(tree1);

    TreeNode* tree2 = constructTestTree2();
    printTree(tree2);

    TreeNode* tree4 = constructTestTree4();
    printTree(tree4);

    printf("Tree 1 is %s\n", isTreeSymmetric(tree1)? "a symmetric tree" : " not a symmetric tree");
    printf("Tree 2 is %s\n", isTreeSymmetric(tree2)? "a symmetric tree" : " not a symmetric tree");
    printf("Tree 3 is %s\n", isTreeSymmetric(tree4)? "a symmetric tree" : " not a symmetric tree");

    freeTree(tree1);
    freeTree(tree2);
    freeTree(tree4);
}

#endif //CPPSANDBOX_TREESYMMETRIC_H
