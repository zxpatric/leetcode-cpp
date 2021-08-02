//
// Created by ZhouP on 4/14/2019.
//

#ifndef CPPSANDBOX_POWEROF_H
#define CPPSANDBOX_POWEROF_H

#include <iostream>
#include <bitset>

bool isPowerOfThree (unsigned int a)
{
    //keep mode?? This is really a meaningless question.
}

bool isPowerOfTwo (unsigned int a)
{
    std::bitset<32> ba(a);
    return ba.count()==1;
}

void test_powerof ()
{
    int value = 2;
    std::cout << value << " is power of 2 is " << std::boolalpha << isPowerOfTwo(value)<< std::endl;

    value = 5;
    std::cout << value << " is power of 2 is " << std::boolalpha << isPowerOfTwo(value)<< std::endl;
}

#endif //CPPSANDBOX_POWEROF_H
