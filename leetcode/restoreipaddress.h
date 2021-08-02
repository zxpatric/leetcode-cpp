//
// Created by ZhouP on 3/23/2019.
//

//TODO_

#ifndef CPPSANDBOX_RESTOREIPADDRESS_H
#define CPPSANDBOX_RESTOREIPADDRESS_H

#include "../include/datastructure.h"

bool isValid(std::string as)
{
    int len = as.length();
    if (len>0 && len <= 3)
    {
        try
        {
            int v = stoi(as);
            if (v>=0 && v<256)
                return true;
        }
        catch (...)
        {
            return false;
        }
    }

    return false;
}

Strings combine (std::string s, Strings ss)
{
    Strings sss;
    sss.reserve (ss.size());
    for (std::string as : ss)
    {
        sss.push_back(s + "." + as);
    }

    return sss;
}

Strings internal_storeipaddress (std::string s, int num)
{
    Strings all_ips;
    if (num==1)
    {
        if (isValid(s))
        {
            all_ips.push_back(s);
        }
    }
    else
    {
        int count = s.length();
        for (int i = 0; i < count; ++i)
        {
            std::string as = s.substr(0, i+1);
            if (isValid(as))
            {
                std::string reminder = s.substr(i+1);
                Strings ips = combine (as, internal_storeipaddress(reminder, num-1));
                std::copy(ips.begin(), ips.end(), std::back_inserter(all_ips));
            }
        }
    }
    return all_ips;
}

Strings entry_storeipaddress (std::string s)
{
    // analysis the all possible ip combination


    Strings all_ips;
    return  (s, 4);

}

void test_storeipaddress ()
{
    std::string s = "25525511135";

    Strings ss = internal_storeipaddress (s, 4);

    printVector(ss);
}

#endif //CPPSANDBOX_RESTOREIPADDRESS_H
