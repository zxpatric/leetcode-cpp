//
// Created by ZhouP on 4/8/2019.
//

#ifndef CPPSANDBOX_COUNTPRIME_H
#define CPPSANDBOX_COUNTPRIME_H

#include "../include/datastructure.h"
#include <math.h>

bool isPrime (unsigned int n)
{
    if (n == 2)
        return true;
    else if (n%2==0)
        return false;
    else
    {
        unsigned int squrerootn = std::sqrt(n);
        for (int i = 3; i <= squrerootn; i += 2) {
            if (n%i==0)
                return false;
        }

        return true;
    }
}

bool isPrime (unsigned int v, UInts& primes)
{
    for (unsigned int p : primes)
    {
        if (v%p==0)
            return false;
    }
    primes.push_back(v);
    return true;
}

int countPrimes(unsigned int n) {

    if (n<2)
        return 0;

//    int count(0);
    UInts primes;
    primes.reserve(n-1);
    primes.push_back(2);
//    for (unsigned int i = 2; i <= n; ++i) {
//        if (isPrime(i))
    for (unsigned int i = 3; i <= n; ++i) {
        if (isPrime(i, primes))
        {
//            primes.push_back(i);
//            ++count;
        }
    }

    printVector(primes);

//    return count;
    return primes.size();
}

void test_countPrimes ()
{
    unsigned int value = 11;
    printf("There are %d prime numbers no more than %d", countPrimes(value), 10);
}

#endif //CPPSANDBOX_COUNTPRIME_H
