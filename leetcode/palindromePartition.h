//
// Created by ZhouP on 4/2/2019.
//

#ifndef CPPSANDBOX_PALINDROMEPARTITION_H
#define CPPSANDBOX_PALINDROMEPARTITION_H

#include "../include/datastructure.h"

std::string getLongestPalindrome (std::string s, int start, int end)
{
    int count = s.length();
    if (start==0 || end == count-1)
        return s;
    else
    {
        while (start>0 && end < count-1)
        {
            if (s[start-1] == s[end+1])
            {
                --start;
                ++end;
            }
            else
            {
                break;
            }
        }

        return s.substr(start, end-start+1);
    }
}

std::string internal_findLongestPalindrome (std::string s)
{
    int count = s.length();
    if (count <= 1)
        return s;

    std::string max_sp = "";
    for (int i = 0; i < count-1; ++i) {
        if (s[i] == s[i+1])
        {
            std::string sp = getLongestPalindrome (s, i, i+1);
            if (sp.length() > max_sp.length())
            {
                max_sp = sp;
            }
        }
    }

    return max_sp;
}

void test_findLongestPalindrome()
{
    std::string s = "abbaaccaabde";
    std::cout << "Longest parlindrome of " << s << " is " << internal_findLongestPalindrome(s) << std::endl;
}



bool isPalindrome(std::string as)
{
    int len = as.length();
    int start = 0;
    int end = len - 1;
    while (start<=end)
    {
        if (as[start]==as[end])
        {
            ++start;
            --end;
        }
        else
        {
            return false;
        }
    }

    return true;
}

Strings combine (Strings ss1, Strings ss2)
{
    Strings sss;
    sss.reserve (ss1.size()*ss2.size());
    for (std::string as1 : ss1)
    {
        for(std::string as2 : ss2) {
            sss.push_back(as1 + "." + as2);
        }
    }

    return sss;
}

Strings entry_findLongestPalindrome (std::string s)
{
    Strings all_sps;
    int count = s.length();
    if (count == 1)
    {
        all_sps.push_back(s);
    }
    else
    {
        if (isPalindrome(s))
        {
            all_sps.push_back(s);
        }
        for (int i = 0; i < count-1; ++i) {
            std::string as = s.substr(0, i+1);
            std::string reminder = s.substr(i+1);
            Strings ips = combine (entry_findLongestPalindrome(as), entry_findLongestPalindrome(reminder));
            std::copy(ips.begin(), ips.end(), std::back_inserter(all_sps));
        }
    }
    return all_sps;
}

void test_palindromePartition()
{
    std::string s = "aabcdc";

    Strings ss = entry_findLongestPalindrome (s);

    std::set<std::string> ss_unique;
    for (std::string as : ss)
        ss_unique.emplace(as);

//    printVector(ss);
    std::for_each(ss_unique.begin(), ss_unique.end(), [](const std::string as){std::cout << as << std::endl;});
}



typedef std::vector<Strings> VStrings;

void partitionString(std::string s, int pos, VStrings& res, Strings& cut)
{
    int count = s.length();
    if (pos == count)
    {
        res.emplace_back(cut);
    }
    else
    {
        for (int i = pos; i <count; ++i) {
            std::string prefix = s.substr(pos, i-pos+1);        // if the prefix is a Palindrome, put it into the cut
            if(isPalindrome(prefix))
            {
                cut.push_back(prefix);
                partitionString(s, i+1, res, cut);
                cut.pop_back();
            }
        }
    }
}
void test_palindromePartition2()
{
    std::string s = "aabcdc";

    VStrings ss;
    Strings cut;
    partitionString (s, 0, ss, cut);

    std::for_each(ss.begin(), ss.end(), [](const Strings ss){printVector(ss);});
}

void test_palindrome()
{
//    return test_findLongestPalindrome();
//    return test_palindromePartition();
    test_palindromePartition2();
}


#endif //CPPSANDBOX_PALINDROMEPARTITION_H
