//
// Created by ZhouP on 3/12/2019.
//

#ifndef CPPSANDBOX_MERGEKSORTED_H
#define CPPSANDBOX_MERGEKSORTED_H

#include "../include/datastructure.h"

#include <queue>

struct moreLinkNode {
    bool operator() (const ListNode* x, const ListNode* y) const {return x->val>y->val;}
};

LinkNode* mergeKSorted_HEAP(LinkedLists& lls)
{
    //use a heap??? how to construct a heap?

    // Build priority queue
    std::priority_queue<ListNode*, std::vector<ListNode*>, moreLinkNode> queue;

    for (LinkNode* ln : lls)
        queue.push(ln);

    ListNode dummy(0); // set dummy head
    ListNode* tail = &dummy;
    while (!queue.empty()) { // build next
        tail->nextP = queue.top();
        queue.pop();
        tail = tail->nextP;
        if (tail->nextP != NULL) queue.push(tail->nextP);
    }
    return dummy.nextP;
}

LinkNode* extractMin(LinkedLists& lls)
{
    LinkNode* theP = NULL;
    int index = 0;
    for(int i=0;i<lls.size();++i) {
        LinkNode *lnP = lls[i];
        if (theP == NULL)
        {
            theP = lnP;
            index = i;
        }
        else if (lnP->val < theP->val)
        {
            theP = lnP;
            index = i;
        }
    }

    LinkNode* theP_replace = theP->nextP;
    if (theP_replace)
    {
        lls[index]=theP_replace;
    }
    else
    {
        lls.erase(lls.begin()+index);
    }

    return theP;
}

LinkNode* mergeKSorted_BF(LinkedLists& lls)
{
    LinkNode dummy(-1);
    LinkNode* lastP = &dummy;

    while (lls.size()>0)
    {
        lastP->nextP = extractMin (lls);
        lastP = lastP->nextP;
    }

    return dummy.nextP;
}

LinkNode* mergeKSorted(LinkedLists& lls)
{
//    return mergeKSorted_BF (lls);
    return mergeKSorted_HEAP(lls);
}

void test_mergeKSorted() {
    LinkNode* ll1 = constructLinkedList ({3, 5, 8, 15, 28});
    LinkNode* ll2 = constructLinkedList ({2, 4, 9, 18});
    LinkNode* ll3 = constructLinkedList ({4, 6, 7, 19, 27, 32});

    LinkedLists lls;
    lls.reserve(3);
    lls.push_back(ll1);
    lls.push_back(ll2);
    lls.push_back(ll3);

    printLinkedList(ll1);
    printLinkedList(ll2);
    printLinkedList(ll3);

    LinkNode* mll = mergeKSorted(lls);
    printLinkedList(mll);


//    freeLinkedList(ll1);
//    freeLinkedList(ll2);
//    freeLinkedList(ll3);
    freeLinkedList(mll);
}

#endif //CPPSANDBOX_MERGEKSORTED_H
