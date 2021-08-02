//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_CONVERTSORTEDTOBST_H
#define CPPSANDBOX_CONVERTSORTEDTOBST_H

#include "../include/datastructure.h"

TreeNode* internal_convertSortedToBST (const Ints &vs, int first, int last)
{
    if (first>last)
    {
        return NULL;
    }

    int middle = (first + last) / 2;
    TreeNode* root = new TreeNode(middle);
    root->leftP = internal_convertSortedToBST (vs, first, middle-1);
    root->rightP = internal_convertSortedToBST (vs, middle+1, last);
    return root;
}

TreeNode* convertSortedToBST (const Ints &vs)
{
    if (vs.size()==0)
        return NULL;
    else if (vs.size()==1)
        return new TreeNode(vs.front());
    else
    {
        return internal_convertSortedToBST(vs, 0, vs.size()-1);
    }
}

void test_convertSortedToBST()
{
    Ints values = {1,3, 4, 5, 6, 7, 9, 11, 14, 16, 18, 20};

    printVector(values);

    TreeNode* bst = convertSortedToBST(values);

    printTree(bst);
    freeTree(bst);
}

#endif //CPPSANDBOX_CONVERTSORTEDTOBST_H
