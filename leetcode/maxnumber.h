//
// Created by ZhouP on 3/23/2019.
//

#ifndef CPPSANDBOX_MAXNUMBER_H
#define CPPSANDBOX_MAXNUMBER_H

#include "../include/datastructure.h"

std::string getmax (Ints values)
{
    std::sort(values.begin(), values.end(), [](const int v0, const int v1)
    {
//        return (v0 < v1)? true : false;

        std::string sv0 = std::to_string(v0);
        std::string sv1 = std::to_string(v1);

//        return strcmp(sv0.c_str(), sv1.c_str())<0;

        int index(0);
        while (index<sv0.length() && index<sv1.length())
        {
            if (sv0[index]>sv1[index])
                return true;
            else if (sv0[index]<sv1[index])
                return false;
            ++index;
        }

        if (sv1.length()>index)
        {
            return true;
        }
        else
        {
            return false;
        }
    });

    std::string ret;
    for (int v : values)
    {
        ret += std::to_string(v);
    }
    return ret;
}

void test_maxnumber()
{
    Ints values = {68, 90, 9, 2, 304};
    std::string s = getmax (values);
    printVector<decltype(values)::value_type>(values);
    printf ("max number can be %s", s.c_str());

//    printf("%d", strcmp("9", "290"));
}

#endif //CPPSANDBOX_MAXNUMBER_H
