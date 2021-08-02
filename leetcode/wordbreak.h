//
// Created by ZhouP on 4/17/2019.
//

#ifndef CPPSANDBOX_WORDBREAK_H
#define CPPSANDBOX_WORDBREAK_H


//The intuition behind this approach is that the given problem (ss) can be divided into subproblems s1s1 and s2s2. If these subproblems individually satisfy the required conditions, the complete problem, ss also satisfies the same. e.g. "\text{catsanddog}catsanddog" can be split into two substrings "\text{catsand}catsand", "\text{dog}dog". The subproblem "\text{catsand}catsand" can be further divided into "\text{cats}cats","\text{and}and", which individually are a part of the dictionary making "\text{catsand}catsand" satisfy the condition. Going further backwards, "\text{catsand}catsand", "\text{dog}dog" also satisfy the required criteria individually leading to the complete string "\text{catsanddog}catsanddog" also to satisfy the criteria.
//
//Now, we'll move onto the process of \text{dp}dp array formation. We make use of \text{dp}dp array (in the form of a linked list) of size n+1n+1, where nn is the length of the given string. \text{dp}[k]dp[k] is used to store every possible sentence having all valid dictionary words using the substring s[0:k-1]s[0:k−1]. We also use two index pointers ii and jj, where ii refers to the length of the substring (s's
//′
//) considered currently starting from the beginning, and jj refers to the index partitioning the current substring (s's
//′
//) into smaller substrings s'(0,j)s
//′
//(0,j) and s'(j+1,i)s
//′
//(j+1,i). To fill in the \text{dp}dp array, we initialize the element \text{dp}[0]dp[0] as an empty string, since no sentence can be formed using a word of size 0. We consider substrings of all possible lengths starting from the beginning by making use of index ii. For every such substring, we partition the string into two further substrings s1's1
//′
//and s2's2
//′
//in all possible ways using the index jj ( Note that the ii now refers to the ending index of s2's2
//′
//). Now, to fill in the entry \text{dp}[i]dp[i], we check if the \text{dp}[j]dp[j] contains a non-empty string i.e. if some valid sentence can be formed using s1's1
//′
//. If so, we further check if s2's2
//′
//is present in the dictionary. If both the conditions are satified, we append the substring s2's2
//′
//to every possible sentence that can be formed up to the index jj (which is already stored in d[j]d[j]). These newly formed sentences are stored in \text{dp}[i]dp[i]. Finally the element \text{dp}[n]dp[n] (nn refers to the length of the given string ss) gives all possible valid sentences using the complete string ss.


//Time complexity : O(n^3)O(n
//3
//). Two loops are required to fill \text{dp}dp array and one loop for appending a list .
//
//Space complexity : O(n^3)O(n
//3
//). Length of \text{dp}dp array is nn and each value of \text{dp}dp array contains a list of string i.e. n^2n
//2
//space.


public class Solution {
public List<String> wordBreak(String s, Set<String> wordDict) {
        LinkedList<String>[] dp = new LinkedList[s.length() + 1];
        LinkedList<String> initial = new LinkedList<>();
        initial.add("");
        dp[0] = initial;
        for (int i = 1; i <= s.length(); i++) {
            LinkedList<String> list = new LinkedList<>();
            for (int j = 0; j < i; j++) {
                if (dp[j].size() > 0 && wordDict.contains(s.substring(j, i))) {
                    for (String l : dp[j]) {
                        list.add(l + (l.equals("") ? "" : " ") + s.substring(j, i));
                    }
                }
            }
            dp[i] = list;
        }
        return dp[s.length()];
    }
}

#endif //CPPSANDBOX_WORDBREAK_H
