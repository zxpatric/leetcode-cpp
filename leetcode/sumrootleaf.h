//
// Created by ZhouP on 3/11/2019.
//

#ifndef CPPSANDBOX_SUMROOTLEAF_H
#define CPPSANDBOX_SUMROOTLEAF_H


#include "../include/datastructure.h"

int internal_sum (TreeNode* root, int sum)
{
    sum = sum*10 + root->value;
    if (root->leftP==NULL && root->rightP==NULL) //a leaf. only leaf is conunted
        return sum;

    int left(0);
    if (root->leftP!=NULL)
        left = internal_sum (root->leftP, sum);

    int right(0);
    if (root->rightP!=NULL)
        right = internal_sum (root->rightP, sum);

    return left + right;
}

int sumRootToLeaf(TreeNode* root)
{
    return internal_sum (root, 0);
}

void test_sumRootToLeaf()
{
    TreeNode* root = constructTestTree1();
    printf ("12 + 13 = %d", sumRootToLeaf(root));
    freeTree(root);
}


#endif //CPPSANDBOX_SUMROOTLEAF_H
