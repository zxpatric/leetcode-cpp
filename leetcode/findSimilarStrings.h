//
// Created by ZhouP on 3/21/2019.
//

#ifndef CPPSANDBOX_FINDSIMILARSTRINGS_H
#define CPPSANDBOX_FINDSIMILARSTRINGS_H

#include "../include/datastructure.h"

class StringHash
{
public:
    size_t operator() (const std::string str) const {
        std::string sort_str = str;
        std::sort(sort_str.begin(), sort_str.end());
        return std::hash<std::string>()(sort_str);
    }
};

class StringEqual
{
public:
    bool operator() (const std::string str1, const std::string str2) const
    {
        std::string sort_str1 = str1;
        std::sort(sort_str1.begin(), sort_str1.end());
        std::string sort_str2 = str2;
        std::sort(sort_str2.begin(), sort_str2.end());

        return sort_str1 == sort_str2;
    }
};


typedef std::unordered_set<std::string, StringHash, StringEqual> StringSimilarSet;
typedef std::unordered_multiset<std::string, StringHash, StringEqual> StringSimilarMSet;

void findSimilarStrings1 (Strings strs, std::vector<Strings>& strss)
{
    StringSimilarSet sss;
    StringSimilarMSet ssms;
    for (std::string s : strs)
    {
        sss.emplace(s);
        ssms.emplace(s);
    }

    int count = sss.size();
    strss.resize(count);

    int i(0);
    for (std::string s : sss)
    {
        auto iter_pair = ssms.equal_range(s);
//        std::for_each(iter_pair.first, iter_pair.second, [](std::string r){printf("%s,", r.c_str());});
//        printf("\n");
        std::copy(iter_pair.first, iter_pair.second, std::back_inserter(strss[i]));
        ++i;
    }
}

typedef std::unordered_multimap <std::string, std::string> SimilarStringMap;
typedef std::set <std::string> StringSet;

void findSimilarStrings (Strings strs, std::vector<Strings>& strss) {
    SimilarStringMap keyvalues;
    StringSet keys;
    for (std::string s : strs) {
        std::string sorts = s;
        std::sort(sorts.begin(),sorts.end());
        keyvalues.emplace(sorts, s);
        keys.emplace(sorts);
    }

    for (std::string ss: keys)
    {
        auto range = keyvalues.equal_range(ss);
        std::for_each(range.first, range.second, [](const std::pair<std::string,std::string> ss) {std::cout << ss.second << ",";});
        std::cout << std::endl;
        std::cout << "Hash value of " << ss << " is " << std::hash<std::string>{}(ss) << std::endl;
    }

    std::cout << "map size is " << sizeof(keyvalues) << std::endl;
    std::cout << "map buckets size is " << keyvalues.bucket_count() << std::endl;
    for (int i = 0; i < keyvalues.bucket_count(); ++i) {
        std::cout << "bucket size of " << i << " is " << keyvalues.bucket_size(i) << std::endl;
    }
}

void test_findSimilarStrings ()
{
    Strings strs = {"ate", "tea", "aet", "plan", "plna", "unist", "tsint"};

    std::vector<Strings> strss;
    findSimilarStrings (strs, strss);
    for_each (strss.begin(), strss.end(), [](Strings ss) {for_each (ss.begin(), ss.end(), [](std::string s){printf("%s,",s.c_str());});printf("\n");});
}

#endif //CPPSANDBOX_FINDSIMILARSTRINGS_H
