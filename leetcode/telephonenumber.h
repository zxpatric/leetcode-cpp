//
// Created by ZhouP on 4/4/2019.
//

#ifndef CPPSANDBOX_TELEPHONENUMBER_H
#define CPPSANDBOX_TELEPHONENUMBER_H

#include "../include/datastructure.h"

std::vector<Strings> phones ={{"a", "b", "c"},
        {"d", "e", "f"},
        {"g", "h", "i"},
        {"j", "k", "l"},
        {"m", "n", "o"},
        {"p", "q", "r", "s"},
        {"t", "u", "v"},
        {"w", "x", "y", "z"}};


Strings combine (const Strings& prefix, const Strings& postfix)
{
    Strings strs;
    strs.reserve(prefix.size()*postfix.size());
    for (std::string sf : prefix)
    {
        for (std::string sb : postfix)
        {
            strs.push_back(sf+sb);
        }
    }

    return strs;
}

Strings letterCombinations(std::string digits) {

    if (digits.length()==1)
        return phones[digits[0]-'2'];
//    std::vector<string> strs;
//    int count = digits.length();
//    for (int i = 0; i < count; ++i) {
//        strs = combine(digits[0], );
//    }

    if (digits[0]=='0' || digits[0]=='1')
    {
        return letterCombinations(digits.substr(1));
    }
    else
    {
        return combine(phones[digits[0]-'2'], letterCombinations(digits.substr(1)));
    }
}

void test_telephonenumber()
{
    std::string digits = "237";
    Strings strs = letterCombinations(digits);
    printVector(strs);
}

#endif //CPPSANDBOX_TELEPHONENUMBER_H
