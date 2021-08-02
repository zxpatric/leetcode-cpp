//
// Created by ZhouP on 4/8/2019.
//

#ifndef CPPSANDBOX_SERIALIZE_DESERIALIZE_BINARYTREE_H
#define CPPSANDBOX_SERIALIZE_DESERIALIZE_BINARYTREE_H


#include "../include/datastructure.h"

TreeNode* ds_binarytree (std::string& s)
{
    if (s=="None")
        return NULL;
    else
    {
        int index = s.find_first_of(',');
        std::string sv = s.substr(0, index);
        s = s.substr(index+1);

        if (sv=="None") {
            return NULL;
        }
        else
        {
            int value = std::stoi(sv);
            TreeNode *aTn = new TreeNode(value);
            aTn->leftP = ds_binarytree(s);
            aTn->rightP = ds_binarytree(s);
            return aTn;
        }
    }
}

std::string s_binarytree (TreeNode* tn)
{
    if (!tn)
        return "None";

    return std::to_string(tn->value)+","+s_binarytree(tn->leftP)+","+s_binarytree(tn->rightP);
}

std::string serialize_binarytree (TreeNode* tn)
{
  if (!tn)
    return "";

  TreeNode* tn_leftP = tn->leftP;
  TreeNode* tn_rightP = tn->rightP;

  if (tn_leftP!=NULL||tn_rightP!=NULL)
    return std::to_string(tn->value)+"?"+serialize_binarytree(tn->leftP)+serialize_binarytree(tn->rightP);
  else
    return std::to_string(tn->value)+":";
}

TreeNode* deserialize_binarytree (std::string& s)
{
  if (s.empty())
    return NULL;
  else
  {
    std::stack<std::pair<TreeNode*, bool>> stackTNs;
    TreeNode* root(NULL);
    do
    {
      auto iter = std::find_if(s.begin(), s.end(), [](const char c){return c=='?'||c==':';});
      int index = std::distance(s.begin(), iter);
      char flag = s[index];
      std::string sv = s.substr(0, index);
      s = s.substr(index+1);
      int value = atoi(sv.c_str());
      TreeNode* aNode = new TreeNode(value);

      if (flag == '?') {
        stackTNs.emplace (aNode, false);
      }
      else if (flag == ':')
      {
        TreeNode* left(NULL);
        bool isleaf;
        while (stackTNs.top().second){
//          [left, isleaf] = stackTNs.top();
          left = stackTNs.top().first;
          stackTNs.pop();
//          [root, isleaf] = stackTNs.top();
          root = stackTNs.top().first;
          stackTNs.pop();
          root->leftP = left;
          root->rightP = aNode;
          aNode = root;
        }
        stackTNs.emplace(aNode, true);
      }
    }while (!s.empty());

//    bool flag;
//    [root, flag] = stackTNs.top();
    root = stackTNs.top().first;
    stackTNs.pop();
    TreeNode* last = root;

    while (!stackTNs.empty())
    {
//      [root, flag] = stackTNs.top();
      bool isleaf;
      while (!stackTNs.empty() && stackTNs.top().second){
//          [left, isleaf] = stackTNs.top();
        TreeNode* left = stackTNs.top().first;
        stackTNs.pop();
//          [root, isleaf] = stackTNs.top();
        root = stackTNs.top().first;
        stackTNs.pop();
        root->leftP = left;
        root->rightP = last;
        last = root;
      }

      if (!stackTNs.empty()) {
        root = stackTNs.top().first;
        root->leftP = last;
        stackTNs.pop();
        last = root;
      }
    }
    return root;
  }
}

void test_s_ds_binarytree()
{
    TreeNode* tn = constructTestTree1 ();

    printTree(tn);

    std::string str = serialize_binarytree (tn);
    std::cout << str << std::endl;
    freeTree(tn);

    TreeNode* anotherTN = deserialize_binarytree(str);

    printTree(anotherTN);
    freeTree(anotherTN);
}

#endif //CPPSANDBOX_SERIALIZE_DESERIALIZE_BINARYTREE_H
