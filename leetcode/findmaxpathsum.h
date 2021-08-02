//
// Created by ZhouP on 3/23/2019.
//

#ifndef CPPSANDBOX_FINDMAXPATHSUM_H
#define CPPSANDBOX_FINDMAXPATHSUM_H

#include "../include/datastructure.h"

int internal_findmaxpathsumfromroot(const TreeNode* root)
{
    if (root==NULL)
        return 0;

    int v = root->value;
    int max_left = internal_findmaxpathsumfromroot (root->leftP);
    int max_right = internal_findmaxpathsumfromroot (root->rightP);

    return std::max(v+max_left, v+max_right);
}

int internal_findmaxpathsum(const TreeNode* root)
{
    if (root==NULL)
        return 0;

    int v = root->value;

    int include_root = v + internal_findmaxpathsumfromroot(root->leftP) + internal_findmaxpathsumfromroot(root->rightP);
    int max_left = internal_findmaxpathsum (root->leftP);
    int max_right = internal_findmaxpathsum (root->rightP);

    return std::max(include_root, std::max(max_left, max_right));
}
//
//int maxPathSumUtil(struct TreeNode *root, int &res)
//{
//  // Base cases
//  if (root==NULL) return 0;
//  if (!root->left && !root->right) return root->data;
//
//  // Find maximum sum in left and right subtree. Also
//  // find maximum root to leaf sums in left and right
//  // subtrees and store them in ls and rs
//  int ls = maxPathSumUtil(root->left, res);
//  int rs = maxPathSumUtil(root->right, res);
//
//
//  // If both left and right children exist
//  if (root->left && root->right)
//  {
//    // Update result if needed
//    res = max(res, ls + rs + root->data);
//
//    // Return maxium possible value for root being
//    // on one side
//    return max(ls, rs) + root->data;
//  }
//
//  // If any of the two children is empty, return
//  // root sum for root being on one side
//  return (!root->left)? rs + root->data:
//         ls + root->data;
//}

int findMaxPath(TreeNode* tn, int& current_max)
{
  if (tn == NULL)
    return 0;

  int left = findMaxPath(tn->leftP, current_max);
  int right = findMaxPath(tn->rightP, current_max);

  if (tn->leftP && tn->rightP || !tn->leftP && !tn->rightP)
  {
    current_max = std::max(current_max, left+right+tn->value);
    return std::max(left, right) + tn->value;
  }
  else if (tn->leftP)
  {
    current_max = std::max(current_max, left+tn->value);
    return left + tn->value;
  }
  else if (tn->rightP)
  {
    current_max = std::max(current_max, right+tn->value);
    return right + tn->value;
  }
  else
  {

  }
}

void test_findmaxpathsum ()
{
    TreeNode* tree1 = constructTestTree1();
    printTree(tree1);

  int treeMax(0);
  int pathMax = findMaxPath (tree1, treeMax);
//    printf("Max path sum is %d\n", internal_findmaxpathsum(tree1));

  std::cout << pathMax << "," << treeMax << std::endl;

    freeTree(tree1);
}

#endif //CPPSANDBOX_FINDMAXPATHSUM_H
