//
// Created by ZhouP on 3/11/2019.
//

#ifndef CPPSANDBOX_BINARYTREEITERATOR_H
#define CPPSANDBOX_BINARYTREEITERATOR_H


#include "../include/datastructure.h"
#include <stack>

class BTreeIterator
{
private:
    const TreeNode* m_root;
    std::stack<const TreeNode*> m_tns;
public:
    BTreeIterator (const TreeNode* root) : m_root(root)
    {
        reset ();
    }

    void reset ()
    {
        while(!m_tns.empty())
            m_tns.pop();
        m_tns.push(m_root);
    }

    bool hasNext() const
    {
        if (m_tns.empty())
            return false;
        else
            return true;
    }

    const TreeNode* next()
    {
        if (m_tns.empty())
            return NULL;
        else {
            const TreeNode *topP = m_tns.top();
            m_tns.pop();
            if (topP != NULL) {
                if (topP->rightP != NULL)
                    m_tns.push(topP->rightP);
                if (topP->leftP != NULL)
                    m_tns.push(topP->leftP);
            }
            return topP;
        }
    }
};


void test_BTreeIterator ()
{
    TreeNode* root = constructTree();
    BTreeIterator iter(root);

    while (iter.hasNext())
    {
        printTreeNode(iter.next());
    }

    freeTree(root);
}

#endif //CPPSANDBOX_BINARYTREEITERATOR_H
