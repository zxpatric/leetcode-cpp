//
// Created by ZhouP on 3/8/2019.
//

#ifndef CPPSANDBOX_MERGESORT_H
#define CPPSANDBOX_MERGESORT_H

#include "../include/datastructure.h"


//LinkNode* left_to_insert = left;
//left = left->nextP;
//
//// insert left into right and move last_right and current_right
//if(left_to_insert->val < last_right->val)
//{
//left_to_insert->nextP = last_right;
//last_right = left_to_insert;
//}
//else if


LinkNode* mergeTogether(LinkNode* leftP, LinkNode* rightP)
{
    LinkNode parent(std::numeric_limits<int>::min());

    LinkNode* root = &parent;

    while (leftP!=NULL && rightP!=NULL)
    {
        if (leftP->val <= rightP->val)
        {
            root->nextP = leftP;
            leftP = leftP->nextP;
        }
        else
        {
            root->nextP = rightP;
            rightP = rightP->nextP;
        }
        root = root->nextP;
    }

    if (leftP!=NULL)
    {
        root->nextP = leftP;
    }

    if (rightP!=NULL)
    {
        root->nextP = rightP;
    }

    return parent.nextP;
}

//
///* UTILITY FUNCTIONS */
///* MoveNode() function takes the
//node from the front of the source,
//and move it to the front of the dest.
//It is an error to call this with the
//source list empty.
//
//Before calling MoveNode():
//source == {1, 2, 3}
//dest == {1, 2, 3}
//
//Affter calling MoveNode():
//source == {2, 3}
//dest == {1, 1, 2, 3} */
//void MoveNode(Node** destRef, Node** sourceRef)
//{
//    /* the front source node */
//    Node* newNode = *sourceRef;
//    assert(newNode != NULL);
//
//    /* Advance the source pointer */
//    *sourceRef = newNode->next;
//
//    /* Link the old dest off the new node */
//    newNode->next = *destRef;
//
//    /* Move dest to point to the new node */
//    *destRef = newNode;
//}
//
///* Takes two lists sorted in increasing
//order, and splices their nodes together
//to make one big sorted list which
//is returned. */
//Node* SortedMerge(Node* a, Node* b)
//{
//    /* a dummy first node to hang the result on */
//    Node dummy;
//
//    /* tail points to the last result node */
//    Node* tail = &dummy;
//
//    /* so tail->next is the place to
//    add new nodes to the result. */
//    dummy.next = NULL;
//    while (1)
//    {
//        if (a == NULL)
//        {
//            /* if either list runs out, use the
//            other list */
//            tail->next = b;
//            break;
//        }
//        else if (b == NULL)
//        {
//            tail->next = a;
//            break;
//        }
//        if (a->data <= b->data)
//            MoveNode(&(tail->next), &a);
//        else
//            MoveNode(&(tail->next), &b);
//
//        tail = tail->next;
//    }
//    return(dummy.next);
//}


LinkNode* mergesort (LinkNode* root)
{
    if (root==NULL || root->nextP==NULL)
        return root;

    // get half
    LinkNode * half = root;
    LinkNode * end = root->nextP;

    while (end!=NULL)
    {
        end = end->nextP;
        if (end==NULL)
            break;
        end = end->nextP;
        half = half->nextP;
    }

    LinkNode * next_half = half->nextP;
    half->nextP = NULL;
    LinkNode * left = mergesort(root);
    LinkNode * right = mergesort(next_half);
    return mergeTogether (left, right);
}

void test_mergesort ()
{
    LinkNode* root = constructLinkedList ({0, 6, 4, 2, 2, 1, 9, 8});
    printLinkedList(root);
    root = mergesort(root);
    printLinkedList(root);
    freeLinkedList(root);
}

#endif //CPPSANDBOX_MERGESORT_H
