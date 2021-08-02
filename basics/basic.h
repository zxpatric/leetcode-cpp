//
// Created by ZhouP on 3/8/2019.
//

#ifndef CPPSANDBOX_BASIC_H
#define CPPSANDBOX_BASIC_H

#include <stdio.h>
#include <stdlib.h>

void testConstPointer()
{
    // Read from right to left
    int x = 10;
    int const *p1 = &x;     // pointer pointing to const int
    int *const p2 = &x;     // const pointer (of) int (type)
    const int *p3 = &x;     // int pointer (which is) const

//    int* p4 = p1;       //error: invalid conversion from 'const int*' to 'int*' [-fpermissive]
//    *p4 = 5;
//
//    *p1 = 5;        // error: assignment of read-only location '* p1'
//
//    int y = 5;
//    p2 = &y;        // error: assignment of read-only variable 'p2'
//    *p3 = 8;        // assignment of read-only location '* p3'
//    p3 = p2;        // OK. The pointer is NOT const though the address it is pointing to IS!
//    *p2 = 5;        // OK. The pointer is const but not the address it is pointing to!
}

void testArray()
{
    int aa[2][2];

    aa[0][0]=0;
    aa[0][1]=1;

    aa[1][0]=2;
    aa[1][1]=3;

    int* pa = (int*)aa;

    printf("%d, %d, %d, %d", pa[0], pa[1], pa[2], pa[3]);
}

void testAtoiItoa()
{
    constexpr int a = 10;
    int i;
    char buffer [33];
    printf ("Enter a number: ");
    scanf ("%d",&i);
    itoa (i,buffer,a);
    printf ("decimal: %s\n",buffer);
    printf ("Again decimal is: %d\n", atoi(buffer));
    itoa (i,buffer,16);
    printf ("hexadecimal: %s\n",buffer);
    itoa (i,buffer,2);
    printf ("binary: %s\n",buffer);


}

#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <future>
//#include <exception>
#include <stdexcept>

int foo(int x)
{
    // do stuff...
    std::this_thread::sleep_for(std::chrono::seconds(1));
    throw(std::invalid_argument("error"));
    return x+1;
}

void byMove(std::promise<int> && p)
{
    // do stuff...
   int value = 0;
   p.set_value(value + 1);
}

void byReference(std::promise<int> & p)
{
    // do stuff...
    int value = 0;
    p.set_value(value + 1);
}

void test_thread()
{
    int x = 0;
//    std::thread first (foo, x);     // spawn new thread that calls foo()

//    std::pair<int, int> aPair(-1, -1);
//    std::thread second (bar,aPair);  // spawn new thread that calls bar(0)

    std::promise<int> p;
//    p.set_value(0);
    auto f = p.get_future();
//    std::thread second (byMove, std::move(p));  // spawn new thread that calls bar(0)
    std::thread second (byReference, std::ref(p));  // spawn new thread that calls bar(0)
    std::cout << "Value Now is : " << f.get() << std::endl;

    std::cout << "main, foo and bar now execute concurrently...\n";

    // synchronize threads:
//    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes

//    p.set_value(10);
//    try
//    {
////        std::cout << "Value After is : " << f.get() << std::endl;
//    std::cout << "Value After is : " << p.get_future().get() << std::endl;
//    }
//    catch (std::exception& e)
//    {
//        std::cout << "error message " << e.what() << std::endl;
//    }
//    catch (...)
//    {
//
//    }
    std::cout << "foo and bar completed.\n";

//    std::future<int> ret = std::async(&foo, 10);
//    try
//    {
//        std::cout << ret.get() << std::endl;
//    }
//    catch (std::invalid_argument& e)
//    {
//        std::cout << "error message " << e.what() << std::endl;
//    }
}

class TestC
{
public:
    int m_value;
public:
    TestC (int value):m_value(value){}
    virtual ~TestC(){}

    TestC& operator+ (const TestC& t)
    {
        m_value += t.m_value;
        return *this;
    }

    size_t operator() (const int value) const
    {
        return m_value + value;
    }
};

void test_class()
{
    TestC t1(2);
    TestC t2(3);

    TestC& t3 = t1+t2;

    printf("%d\n", t1(10));
}

void testCPPBasic()
{
//    testConstPointer();
//    testArray();
//    testAtoiItoa();
//    test_thread();
    test_class();
}

#endif //CPPSANDBOX_BASIC_H
