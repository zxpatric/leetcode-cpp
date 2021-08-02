//
// Created by ZhouP on 4/4/2019.
//

#ifndef CPPSANDBOX_REVERSEKNODES_H
#define CPPSANDBOX_REVERSEKNODES_H

#include "../include/datastructure.h"

ListNode* reverseKGroup(ListNode* head, int k) {
    std::stack<ListNode*> stackNodes;
//    stackNodes.reserve(k);

    ListNode* iter = head;
    if(k <= 1 || iter==NULL)
        return head;

    bool firstTime(true);
    ListNode* lastP(NULL);
    while(iter || stackNodes.size() == k)
    {
        if (stackNodes.size() < k)
        {
            stackNodes.push(iter);
            iter = iter->nextP;
        }
        else
        {
            ListNode* nodeP = stackNodes.top();
            stackNodes.pop();
            if (firstTime)
            {
                head = nodeP;
                firstTime = false;
            }
            else
            {
                lastP->nextP = nodeP;
            }
            ListNode* endP = nodeP->nextP;
            while(stackNodes.size()>0)
            {
                ListNode* next = stackNodes.top();
                stackNodes.pop();
                nodeP->nextP = next;
                nodeP = next;
            }
            nodeP->nextP = endP;
            lastP = nodeP;
        }
    }

    return head;
}

void test_reverseKNodes ()
{
    LinkNode* ln = constructLinkedList (unsorted_ints);
    printVector(unsorted_ints);
    LinkNode* rln = reverseKGroup(ln, 2);
    printLinkedList(rln);

    freeLinkedList(rln);
}

#endif //CPPSANDBOX_REVERSEKNODES_H
