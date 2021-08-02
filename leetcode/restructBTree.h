//
// Created by ZhouP on 3/7/2019.
//

#ifndef CPPSANDBOX_RESTRUCTBTREE_H
#define CPPSANDBOX_RESTRUCTBTREE_H

#include "../include/datastructure.h"

//105. Construct Binary Tree from Preorder and Inorder Traversal
//https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

//TreeNode *buildTree(const Ints &preorder, const Ints &inorder) {
//    return create(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
//}
//Ints pre = {5,4,3,6,8,7,9};
//Ints in = {3,4,6,5,7,8,9};


TreeNode* createFromPreOrderAndInOrder(const Ints& preorder, const Ints& inorder, int ps, int pe, int is, int ie){
    if(ps > pe){
        return NULL;
    }
    TreeNode* node = new TreeNode(preorder[ps]);
    int pos (-1);
    for(int i = is; i <= ie; i++){
        if(inorder[i] == node->value){
            pos = i;
            break;
        }
    }

    if (pos<0)
        return NULL;
    else
        pos -= is;      // make it an absolute offset
//    node->leftP = createFromPreOrderAndInOrder(preorder, inorder, ps + 1, ps + pos - is, is, pos - 1);
//    node->rightP = createFromPreOrderAndInOrder(preorder, inorder, pe - ie + pos + 1, pe, pos + 1, ie);
    node->leftP = createFromPreOrderAndInOrder(preorder, inorder, ps + 1, ps + pos, is, is + pos - 1);
    node->rightP = createFromPreOrderAndInOrder(preorder, inorder, ps + pos + 1, pe, is + pos + 1, ie);
    return node;
}


//Ints in = {3,4,6,5,7,8,9};
//Ints post = {3,6,4,7,9,8,5};
//106. Construct Binary Tree from Inorder and Postorder Traversal
//https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
TreeNode* createFromInOrderAndPostOrder(const Ints& inorder, const Ints& postorder, int is, int ie, int ps, int pe){
    if(ps > pe || is>ie){
        return NULL;
    }
    TreeNode* node = new TreeNode(postorder[pe]);
    int pos(-1);
    for(int i = is; i <= ie; i++){
        if(inorder[i] == node->value){
            pos = i;
            break;
        }
    }

    if (pos<0)
        return NULL;
    else
        pos -= is;      // make it an absolute offset

    node->leftP = createFromInOrderAndPostOrder(inorder, postorder, is, is + pos - 1, ps, ps+pos - 1);
    node->rightP = createFromInOrderAndPostOrder(inorder, postorder, is + pos + 1, ie, ps + pos, pe-1);
    return node;
}



////107. Construct Binary Tree from Preorder and Postorder Traversal
//Ints pre =  {5,4,3,6,8,7,9};
//Ints post =   {3,6,4,7,9,8,5};
TreeNode* createFromPreOrderAndPostOrder(const Ints& preorder, const Ints& postorder, int ps, int pe, int ts, int te){
    if(ps > pe){
        return nullptr;
    } else if (ps==pe)
    {
        if (preorder[ps]==postorder[ts])
            return new TreeNode(preorder[ps]);
        else
            return NULL;
    }

    TreeNode* node = new TreeNode(preorder[ps]);
    int value = preorder[ps+1];
    int pos(-1);
    for(int i = ts; i <= te; i++){
        if(postorder[i] == value){
            pos = i;
            break;
        }
    }
    if (pos<0)
        return NULL;
    else
        pos -= ts;      // make it an absolute offset


    node->leftP = createFromPreOrderAndPostOrder(preorder, postorder, ps + 1, ps + pos+1, ts, ts+pos);
    node->rightP = createFromPreOrderAndPostOrder(preorder, postorder, ps + pos + 2, pe, ts + pos+1, te-1);
    return node;
}

Ints pre = {5,4,3,6,8,7,9};
Ints in = {3,4,6,5,7,8,9};
Ints post = {3,6,4,7,9,8,5};

void test_create()
{
    TreeNode* root = constructTestTree2();
    printTree(root);

    int start = 0;
    int end = pre.size()-1;

    printf("preOrder + inOrder:\n");
    TreeNode* preP = createFromPreOrderAndInOrder (pre, in, start, end, start, end);
    printTree(preP);
    freeTree(preP);

    printf("inOrder + postOrder:\n");
    TreeNode* inP = createFromInOrderAndPostOrder (in, post, start, end, start, end);
    printTree(inP);
    freeTree(inP);

    printf("preOrder + postOrder:\n");
    TreeNode* postP = createFromPreOrderAndPostOrder (pre, post, start, end, start, end);
    printTree(postP);
    freeTree(postP);

    freeTree(root);
}

//preorder = [3,9,20,15,7]
//inorder = [9,3,15,20,7]
//postorder = [9,15,7,20,3]

#endif //CPPSANDBOX_RESTRUCTBTREE_H
