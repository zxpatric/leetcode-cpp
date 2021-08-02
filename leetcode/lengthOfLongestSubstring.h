//
// Created by ZhouP on 3/4/2019.
//

#ifndef CPPSANDBOX_LENGTHOFLONGESTSUBSTRING_H
#define CPPSANDBOX_LENGTHOFLONGESTSUBSTRING_H

#include "../include/datastructure.h"

#include <string>

/* find out from each position how far a unique string can be going forward
 * valid_index is always pointing to the position that no duplication is happening yet
 * current array of 255 positions record where the conflict is happening for this alphabet
 * lens array is recording how far a unique string can be going forward
 * finally get the maximum of lens array is the final result
 *
 */

class SolutionMindTwist {
public:
    int lengthOfLongestSubstring(std::string s) {
        int len = s.length();
        if (len<=1)
        {
            return len;
        }
        unsigned int current[255];
        memset(current, 0, 255*sizeof(unsigned int));
        //    unsigned int* lens = new unsigned int[len];
        int valid_index  = 0;
        std::vector<int> lens;
        for (int i = 0; i < len; ++i) {
            lens.push_back(0);
            const char c = s[i];
            int index = (int)(c-'\0');
            if (current[index]>valid_index)
            {
                for(int j=valid_index; j<current[index];++j)
                {
                    lens[j] = i-j;
                }

                valid_index = current[index];
            }

            current[index]=i+1;
            lens[i] = len - i;
        }

        return *std::max_element(lens.begin(), lens.end());
    }
};


class SolutionExtraSpace{
public:
    int lengthOfLongestSubstring(std::string s) {
        int len = s.length();

        std::vector<char> longest;
        longest.reserve(len);

        int valid_index = 0;
        int max = 0;
        int mid_length = 0;
        for (int i = 0; i < len; ++i) {
            char c = s[i];
            auto iter=std::find(longest.begin() + valid_index, longest.end(), c);
            if (longest.end()!=iter)
            {
                valid_index = std::distance(longest.begin(), iter)+1;
            }
            longest.push_back (c);

            mid_length = longest.size() - valid_index;
            if (max < mid_length)
            {
                max = mid_length;
            }
        }

        return max;
    }
};


int lengthOfLongestSubstring(std::string s) {
    int len = s.length();
    if (len < 2)
        return len;

    int valid_index = 0;
    int max = 0;
    int mid_length = 0;
    for (int i = 1; i < len; ++i) {
        char c = s[i];
        auto iter_end =  s.begin()+i;
        // create the sliding window between valid_index and i
        auto iter=std::find(s.begin() + valid_index, s.begin()+i, c);
        if (iter_end!=iter)
        {
            // if found, move the left pointer to one after the finding place
            valid_index = std::distance(s.begin(), iter)+1;
        }

        mid_length = i - valid_index+1;
        if (max < mid_length)
        {
            max = mid_length;
        }
    }

    return max;
}

#include <unordered_map>
#include <set>
#include <map>
typedef std::unordered_multimap<char, int> CharIntHTable;
typedef std::set<char> CharSet;
typedef std::map<char, int> CharIntMap;


void use_map_lengthOfLongestSubstring (std::string s)
{
    CharIntMap ciMap;
    int count = s.length();
    int start = 0;
    int max_length = 0;
    int max_first_index(0);
    int max_last_index(0);
    for (int i = 0; i < count; ++i)
    {
        char c = s[i];
        auto iter = ciMap.find(c);
        if (iter!=ciMap.end())
        {
            start = std::max(start, iter->second + 1);
        }
        if (max_length < i-start+1)
        {
            max_length = i-start+1;
            max_first_index = start;
            max_last_index = i;
        }
        ciMap.emplace(c, i);
    }

    std::string sub;
    std::copy(s.begin()+max_first_index, s.begin()+max_last_index+1, std::back_inserter(sub));
    std::cout << sub << " is of max length " << max_length << " in " << s << std::endl;
}


void use_multimap_lengthOfLongestSubstring (std::string s)
{
    // doesn't work!!!
    CharIntHTable ciMap;
    CharSet cSet;
    int count = s.length();
    for (int i = 0; i < count; ++i)
    {
        ciMap.emplace(s[i], i);
        cSet.emplace(s[i]);
    }

    int max_length(0);
    int max_first_index(0);
    int max_last_index(0);
    Ints poss;
    for (const char c:cSet)
    {
        auto iter_pair = ciMap.equal_range(c);
//        std::copy(iter_pair.first, iter_pair.second, std::back_inserter(poss));
        std::for_each(iter_pair.first, iter_pair.second, [&](auto a_iter){poss.emplace_back(a_iter.second);});
        std::sort(poss.begin(), poss.end());
        //0  -> poss -> count-1

        if (max_length < poss[0]+1)
        {
            max_length = poss[0]+1;
            max_first_index = 0;
            max_last_index = poss[0];
        }

        int last = 0;
        int i = 1;
        for (; i < poss.size(); ++i) {
            if (max_length < poss[i]-poss[last]+1)
            {
                max_length = poss[i]-poss[last]+1;
                max_first_index = poss[last]+1;
                max_last_index = poss[i];
            }
            last = i;
        }

        --i;
        if (max_length < count-poss[i])
        {
            max_length = count-poss[i];
            max_first_index = poss[i];
            max_last_index = count-1;
        }
    }

    std::string sub;
    std::copy(s.begin()+max_first_index, s.begin()+max_last_index+1, std::back_inserter(sub));
    std::cout << sub << " is of max length " << max_length << " in " << s << std::endl;
}


void test_lengthOfLongestSubstring ()
{
//    lengthOfLongestSubstring(s);
//    CharIntHTable icMap;
//    icMap.emplace('c', 2);
//    icMap.emplace('c', 6);
//
//    auto iter_pair = icMap.equal_range('c');
//    std::for_each(iter_pair.first, iter_pair.second, [](auto an_iter){printf("%d,", an_iter.second);});

    std::string s("abccdba");
//    return use_multimap_lengthOfLongestSubstring (s);
    return use_map_lengthOfLongestSubstring(s);
}

#endif //CPPSANDBOX_LENGTHOFLONGESTSUBSTRING_H
