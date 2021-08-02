//
// Created by ZhouP on 3/11/2019.
//

#ifndef CPPSANDBOX_REVERSEBITS_H
#define CPPSANDBOX_REVERSEBITS_H

#include <stdio.h>
#include <bitset>
#include <iostream>
#include <unordered_map>
#include <math.h>

int reverseBits (int value)
{
    int reverse = 0;

    int order_bit = 1;
    int reverse_bit = order_bit<<31;

    for (int i = 0; i < 32; ++i) {
        if (value & order_bit << i)
        {
            reverse |= order_bit << (31-i);
        }
    }
    return reverse;
}

std::unordered_map<int, int> reverse_map;

unsigned int reverseByte (int val)
{

    unsigned int reverse = 0;

    unsigned int order_bit = 1;
    unsigned int reverse_bit = order_bit<<7;

    // reverse the first 8 bits
    for (int i = 0; i < 8; ++i) {
        if (val & order_bit << i)
        {
            reverse |= reverse_bit >>i;
        }
    }

    return reverse;
}


//#define GET_REVERSE(b1, b1_rev) \
//    { \
//    auto iter = reverse_map.find(b1); \
//    if (iter!=reverse_map.end()) \
//        b1_rev = iter->second; \
//    else { \
//        b1_rev = reverseByte(b1); \
//        reverse_map.emplace(b1, b1_rev); \
//    } \
//    }

void GET_REVERSE(const unsigned int b1, unsigned int& b1_rev)
{
    auto iter = reverse_map.find(b1);
    if (iter!=reverse_map.end())
        b1_rev = iter->second;
    else {
        b1_rev = reverseByte(b1);
        reverse_map.emplace(b1, b1_rev);
    }
}

int reverseInt (int value)
{
    unsigned int byte_4 = std::pow(2, 8) -1;
    unsigned int byte_3 = std::pow(2, 16) -1;
    unsigned int byte_2 = std::pow(2, 24) -1;
    unsigned int byte_1 = std::pow(2, 32) -1;

    byte_1 -= byte_2;
    byte_2 -= byte_3;
    byte_3 -= byte_4;


//    unsigned int value = val;
    unsigned int b1 = (value & byte_1) >> 24;
    unsigned int b2 = (value & byte_2) >> 16;
    unsigned int b3 = (value & byte_3) >> 8;
    unsigned int b4 = (value & byte_4);

    unsigned int b1_rev;
    unsigned int b2_rev;
    unsigned int b3_rev;
    unsigned int b4_rev;

    GET_REVERSE (b1, b1_rev);
    GET_REVERSE (b2, b2_rev);
    GET_REVERSE (b3, b3_rev);
    GET_REVERSE (b4, b4_rev);

//    iter = reverse_map.find(b1);
//    if (iter!=reverse_map.end())
//    {
//        b1_rev = iter->second;
//    }
//    else
//    {
//        b1_rev = reverseByte(b1);
//        reverse_map.emplace(b1, b1_rev);
//    }

    return (b4_rev<<24)+(b3_rev<<16)+(b2_rev<<8)+b1_rev;
}


void test_reverseBits() {
    int order_bit = 1;
    unsigned int u_reverse_bit = order_bit << 31;
    printf("value %u \n", u_reverse_bit);
    u_reverse_bit = u_reverse_bit >> 31;
    printf("value %u \n", u_reverse_bit);

    int reverse_bit = order_bit << 31;
    printf("value %d \n", reverse_bit);
    reverse_bit = reverse_bit >> 31;
    printf("value %d \n", reverse_bit);

    std::bitset<32> sign(reverse_bit);
    std::cout << "sign value " << sign << std::endl;
    std::bitset<32> unsign(u_reverse_bit);
    std::cout << "unsign value " << unsign << std::endl;
    std::cout.flush();


    int val = 43261596;
    printf("original value %d \n", val);
    printf("reversed value %d \n", reverseBits(val));
    printf("reversed value %d \n", reverseInt(val));

    unsigned int byte_4 = std::pow(2, 8) -1;
    unsigned int byte_3 = std::pow(2, 16) -1;
    unsigned int byte_2 = std::pow(2, 24) -1;
    unsigned int byte_1 = std::pow(2, 32) -1;
    int val2 = 43261596 & (byte_1-byte_3) + (12<<8);
    printf("reversed value %d \n", reverseInt(val2));
    printf("reversed value %d \n", reverseBits(val2));
}


#endif //CPPSANDBOX_REVERSEBITS_H
