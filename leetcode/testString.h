//
// Created by ZhouP on 3/26/2019.
//

#ifndef CPPSANDBOX_TESTSTRING_H
#define CPPSANDBOX_TESTSTRING_H

#include <string>
#include <algorithm>
#include "../include/datastructure.h"

void testString()
{

}

void testSTLString()
{
    std::string ss = "hello world!";
    printf("%s\n", ss.c_str());

    ss.append("C++ belongs to ");
    printf("After append, %s\n", ss.c_str());

//    ss.append<int>(5, 0x2E);
//    Ints vs = unsorted_ints;

//    std::vector<std::string> strs = {"me", "you", "him"};
    std::string strs = "you, me, him";

//    ss.append<decltype(strs)::iterator>(strs.begin(), strs.end());
    ss.append<decltype(strs)::iterator>(strs.begin(), strs.end());
    printf("After append int, %s\n", ss.c_str());

    int index = 5;
    printf("String %s at %d is %c\n", ss.c_str(), index, ss.at(index));

    std::for_each(ss.cbegin(), ss.cend(), [](const char c){printf("%c");});
    printf("\n");

    ss.clear();
    printf("After clear, string is now %s\n", ss.c_str());

    printf("String compare %d\n", ss.compare(strs));


    char buffer[20];
    std::string str ("Test string...");
    std::size_t length = str.copy(buffer,6,5);
    buffer[length]=str.data()[str.length()];
    printf("Copied string is %s\n", buffer);

    char* str_data = str.data();
    str_data[1] = 'E';
    printf("Changed string is %s\n", str_data);
    printf("Last two chars are %c and %x\n", str_data[str.length()-1], str_data[str.length()]);

    auto new_str = str.erase(10);
    printf("Erased string left is %s\n", new_str.c_str());
    auto iter = str.erase(str.begin()+3, str.begin()+5);
    printf ("from iter to end is ");
    std::for_each(iter, str.end(), [](const char c){printf("%c");});
    printf("\n");
    printf ("but the str is %s\n", str.c_str());

    printf ("sub string 3-5 of str is %s\n", str.substr(3,5).c_str());


     str ="There are two needles in this haystack with needles.";
    std::string str2 ("needle");

    std::size_t found = str.find(str2);
    if (found!=std::string::npos)
        std::cout << "first 'needle' found at: " << found << '\n';

    found = str.rfind(str2);
    if (found!=std::string::npos)
        std::cout << "last 'needle' found at: " << found << '\n';

    str.replace(str.find(str2),str2.length(),"preposition");
    std::cout << str << '\n';


    str.resize(10);
    std::cout << str << '\n';

    str.resize(15, 'c');
    std::cout << str << '\n';

    std::cout << str.length() << "," << str.capacity() << "," << str.max_size() << '\n';

    str.insert(3, str2);
    std::cout << str << '\n';

    std::cout << std::boolalpha <<  std::all_of(str.begin(), str.end(), [](unsigned char c){ return std::isalpha(c); } ) << std::endl;
}

#endif //CPPSANDBOX_TESTSTRING_H
