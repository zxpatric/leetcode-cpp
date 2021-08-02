//
// Created by ZhouP on 4/4/2019.
//

#ifndef CPPSANDBOX_REGULAREXPRESSION_H
#define CPPSANDBOX_REGULAREXPRESSION_H

#include <string>

bool isMatch(std::string text, std::string pattern)
{
    if(pattern.empty())
        return text.empty();

    bool first_match = !text.empty() and (pattern[0] == text[0] | pattern[0] == '.');
    if(pattern.length()>=2 && pattern[1]=='*')
        return isMatch(text, pattern.substr(2)) || first_match && isMatch(text.substr(1), pattern);
    else
        return first_match && isMatch(text.substr(1), pattern.substr(1));
}

void test_regularExpressionMatch()
{
//    std::string s = "aa";
//    std::string p = "a";

//    std::string s = "aa";
//    std::string p = "a*";

    std::string s = "ab";
    std::string p = ".*";

    std::cout<< s << " matches " << p << " is " << std::boolalpha << isMatch(s, p) << std::endl;
}

#endif //CPPSANDBOX_REGULAREXPRESSION_H
