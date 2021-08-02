//
// Created by ZhouP on 3/7/2019.
//

#ifndef CPPSANDBOX_REMOVEDUPLICATEINSORTED_H
#define CPPSANDBOX_REMOVEDUPLICATEINSORTED_H

#include "../include/datastructure.h"

//Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
//
//Example 1:
//
//Input: 1->2->3->3->4->4->5
//Output: 1->2->5
//Example 2:
//
//Input: 1->1->1->2->3
//Output: 2->3


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head==NULL || head->nextP==NULL)
            return head;

        ListNode* start = head;
        ListNode* next = start->nextP;

        while (next!=NULL)
        {
            if (start->val == next->val)
            {
                next = next->nextP;
                delete (start->nextP);
                start->nextP = next;
            }
            else
            {
                start = next;
                next = next->nextP;
            }
        }
        return head;
    }
};

void test_deleteDuplicates ()
{
    LinkNode* root = constructLinkedList ({1, 2, 3, 3, 4, 4, 5});

    printLinkedList(root);
    Solution s;
    root = s.deleteDuplicates(root);
    printLinkedList(root);

    freeLinkedList(root);
}

#endif //CPPSANDBOX_REMOVEDUPLICATEINSORTED_H
