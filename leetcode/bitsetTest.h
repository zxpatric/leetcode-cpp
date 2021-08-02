//
// Created by ZhouP on 3/26/2019.
//

#ifndef CPPSANDBOX_BITSETTEST_H
#define CPPSANDBOX_BITSETTEST_H

#include <bitset>
#include <string>
#include <algorithm>

bool findBitSet (std::string s, int v)
{
    std::bitset<32> bv(v);
    std::string sbv = bv.to_string();
    sbv.erase(sbv.begin(), sbv.begin()+sbv.find('1'));
    return std::string::npos!=s.find(sbv);
}

void test_bitset ()
{
    std::string s = "0110";
    int value = 2;

    std::string sbv = std::bitset<32>(value).to_string();
    std::cout << sbv << "," << sbv[1] << sbv[30]<<  std::endl;
    sbv.erase(sbv.begin(), sbv.begin()+sbv.find('1'));
    printf("%s %s the binary format of value %d as %s\n", s.c_str(), findBitSet(s, value)? "contains": "doesn't contain", value, sbv.c_str());

    std::bitset<32> bv1(2);

    std::bitset<32> bv = bv1 ^ bv1;
//    bv1 = bv1.reset();
    std::cout << bv1.count() << ',' << bv1.size() << ',' << bv << ',' << bv.to_string() << std::endl;
    std::cout << bv1 << ',' << bv1.flip() << ','<< bv1.reset() << ','<< bv1.set(2) << std::endl;

    std::bitset<16> baz (std::string("10101111001"));
    std::cout << "baz: " << baz << '\n';
}

#endif //CPPSANDBOX_BITSETTEST_H
