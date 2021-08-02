//
// Created by ZhouP on 3/3/2019.
//

#ifndef CPP_LONGESTVALIDPARENTHESES_H
#define CPP_LONGESTVALIDPARENTHESES_H


#include <stack>

inline std::pair<int, int> getMaxPair(const std::vector<std::pair<int, int>>& pairs, std::vector<int>& indexs)
{
    int num = pairs.size();
    if (num <=0) return std::pair<int, int>(0, -1);


    std::vector<std::pair<int, int>> new_pairs;
    new_pairs.reserve(num);

    std::pair<int, int> pair = pairs[num - 1];
    for (int i = num - 2; i >=0 ; --i) {
        const std::pair<int, int>& p = pairs[i];
        if (p.first > pair. first && p.second < pair.second)
        {

        }
        else
        {
            if (indexs.end()!=std::find_if(indexs.begin(), indexs.end(), [=](auto& index){return index>p.second && index<pair.first;}))
//            if(true)
            {
                new_pairs.push_back(pair);
                pair.second = p.second;
                pair.first = p.first;
            }
            else
            {
                pair.first = p.first;
            }
        }
    }
    new_pairs.push_back(pair);

    return *std::max_element(new_pairs.begin(), new_pairs.end(), [=](auto &a, auto &b){return a.second - a.first < b.second - b.first;});

//    return pair;
};

int longestValidParentheses(std::string s) {
    int len = s.length();

    std::stack<int> leftBraceIndex;
    std::vector<std::vector<std::pair<int, int>>> pairss;
    pairss.reserve(1);
    pairss.push_back(std::vector<std::pair<int, int>>());
    std::vector<std::pair<int, int>> *pairsP = &pairss.back();

    // search for the first )
//    int index = s.find_first_of(')', 0);

    for (int i = 0; i<len; ++i)
    {
        if (s.at(i)=='(')
        {
            leftBraceIndex.push(i);
        }
        else if (s.at(i) == ')')
        {
            if (leftBraceIndex.empty())
            {
                // set the breaking here.
                pairss.push_back(std::vector<std::pair<int, int>>());
                pairsP = &pairss.back();
            } else{
                pairsP->push_back(std::pair<int, int>(leftBraceIndex.top(), i));
                leftBraceIndex.pop();
            }
        }
    }

//    int* end   = &leftBraceIndex.top() + 1;
//    int* begin = end - leftBraceIndex.size();
//    std::vector<int> stack_contents(begin, end);

    std::vector<int> stack_contents;
    stack_contents.reserve(leftBraceIndex.size());
    while(!leftBraceIndex.empty())
    {
        stack_contents.push_back(leftBraceIndex.top());
        leftBraceIndex.pop();
    }

    std::pair<int, int> max_pair(0, -1);
    for (const std::vector<std::pair<int, int>>& pairs : pairss) {
        // deal with pairs
        std::pair<int, int> pair = getMaxPair(pairs, stack_contents);
        if (pair.second - pair.first > max_pair.second - max_pair.first)
        {
            max_pair.first = pair.first;
            max_pair.second = pair.second;
        }
    }

    return max_pair.second - max_pair.first + 1;

}

//    printf("%d\n", longestValidParentheses("(()"));
//    printf("%d\n", longestValidParentheses(")()())"));
//    printf("%d\n", longestValidParentheses("()(()"));
//    printf("%d\n", longestValidParentheses(")(((((())))(((())()))()(()(()())())()))((())()(()))))()))))))(()()))((()))()(()()))()())))(()()))())()()(()(((()))))))((((()())))((()))))()()()"));
//    printf("%d\n", longestValidParentheses("(c)a((s(k)b(d))"));


#endif //CPP_LONGESTVALIDPARENTHESES_H
