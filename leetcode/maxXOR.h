//
// Created by ZhouP on 4/15/2019.
//

#ifndef CPPSANDBOX_MAXXOR_H
#define CPPSANDBOX_MAXXOR_H

// build the Trie (binary tree) toward the binary representation of all numbers


#include "../include/datastructure.h"


//struct TrieNode{
//    int val;
//    TrieNode *left;
//    TrieNode *right;
//    TrieNode(int x) : val(x), left(NULL), right(NULL) {}
//};
//class Solution {
//public:
//
//    int findMaximumXOR(vector<int>& nums) {
//        TrieNode* root = new TrieNode(0);
//
//
//        //建树
//        TrieNode* curNode = root;
//        for(int i = 0; i < nums.size(); i++){
//            for(int j = 31; j >= 0; j--) {
//                int tmp = nums[i] & (1 << j);
//                if(tmp == 0){
//                    if(!curNode->right){
//                        curNode->right = new TrieNode(0);
//                    }
//                    curNode = curNode->right;
//                }else{
//                    if(!curNode->left){
//                        curNode->left = new TrieNode(1);
//                    }
//                    curNode = curNode->left;
//                }
//                //cout << curNode->val;
//            }
//            //cout << endl;
//            curNode = root;
//        }
//
//        //匹配最大异或值
//        int max = 0;
//        for(int i = 0; i < nums.size(); i++){
//            int res = 0;
//            for(int j = 31; j >= 0; j--){
//                int tmp = nums[i] & (1 << j);
//                //cout << (1 << j) << "\t" << tmp << endl;
//                if(curNode->left && curNode->right){
//                    if(tmp == 0){
//                        curNode = curNode->left;
//                    }else {
//                        curNode = curNode->right;
//                    }
//                }else {
//                    curNode = curNode->left == NULL ? curNode->right:curNode->left;
//                }
//                res += tmp ^ (curNode->val << j);
//                //cout << curNode->val;
//            }
//            curNode = root;
//            //cout << endl;
//            max = max > res?max:res;
//        }
//
//        return max;
//    }
//};

int findMaxXOR(const Ints& values, int& v0, int& v1)
{
    return 0;
}

void test_findMaxXOR()
{
    Ints values = {3,10,5,25,2,8};

    printVector(values);

    int v0(0), v1(0);
    std::cout << " maximum XOR is " << findMaxXOR(values, v0, v1) << " between " << v0 << " and " << v1 << std::endl;
}

#endif //CPPSANDBOX_MAXXOR_H
