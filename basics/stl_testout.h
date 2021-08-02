//
// Created by ZhouP on 3/18/2019.
//

#ifndef CPPSANDBOX_STL_TESTOUT_H
#define CPPSANDBOX_STL_TESTOUT_H

#include <stdio.h>
//#include <cstddef>
#include <algorithm>
#include <queue>
#include <functional>
#include <numeric>
#include <iostream>
#include <iterator>
#include <forward_list>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <bitset>
#include <unordered_set>
#include <sstream>

#include "../include/datastructure.h"

int f()
{
    static int i = 1;
    return i++;
}

class A
{
public:
    std::string m_value;
    Ints m_values;

    A (int n) : m_values(n, 1)
    {

    }
};

class AHash
{
public:
    size_t operator() (const A& a) const {
        return std::hash<std::string>()(a.m_value);
    }
};

void test_functional() {

}

void test_SingleLinkedList()
{
    std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
//    std::sort(fl.begin(), fl.end());          // std::sort requires random access iterators and so cannot be used with forward_list !!!
    printf ("Single linked list:\n");
    std::for_each(fl.begin(), fl.end(), [&](const int r){printf("%d,", r);});
    printf("\n");
    printf ("Single linked list sorted ascendent:\n");
    fl.sort();
    std::for_each(fl.begin(), fl.end(), [&](const int r){printf("%d,", r);});
    printf("\n");
    printf ("Single linked list sorted descendent:\n");
    fl.sort(std::greater<int>());
    std::for_each(fl.begin(), fl.end(), [&](const int r){printf("%d,", r);});
    printf("\n");
}

//template <typename T>
//std::ostream& operator<<(std::ostream& os, const IntPair& v)
//{
//    std::cout << v.first << "," << v.second;
//    return os;
//}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T, S>& v)
{
    os << "(";
    os << v.first << ", "
       << v.second << ")";
    return os;
}

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
//        if constexpr(std::is_same_v<T, IntPairs>)
//            std::cout << q.top().first << "," << q.top().second << " ";
//        else
            std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

void test_priorityQueue()
{
    std::priority_queue<IntPair, IntPairs> pq1;
    pq1.emplace(1, 10);
    pq1.emplace(4, 8);
    pq1.emplace(3, 12);
    print_queue(pq1);
    std::cout << pq1.top().first << "," << pq1.top().second << " ";
    pq1.pop();
    std::cout << pq1.top().first << "," << pq1.top().second << " ";

    IntPair aip(10, 11);
    std::cout << aip << std::endl;

//    std::array<int, 10> values= {1,8,5,6,3,4,0,9,7,2};
//    std::priority_queue<int> pq;
//    for(int n : values)
//        pq.push(n);
//    print_queue(pq);
//
//    std::priority_queue<int, std::vector<int>, std::greater<int> > pq2;
//
//    for(int n : values)
//        pq2.push(n);
//
//    print_queue(pq2);
//
//    // Using lambda to compare elements.
//    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1);};
//    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq3(cmp);
//
//    for(int n : values)
//        pq3.push(n);
//
//    print_queue(pq3);
//
//    std::cout << (2^1) << "," << (3^1) << std::endl;
}

void test_heap ()
{
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };

    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::make_heap(v.begin(), v.end(), std::less<int>());
    std::make_heap(v.begin(), v.end(), std::greater<int>());
//    auto comp = [](decltype(v) v1, decltype(v) v2) {return v1 < v2;};
//    std::make_heap(v.begin(), v.end(), comp);

    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::pop_heap(v.begin(), v.end());
    auto largest = v.back();
    v.pop_back();
    std::cout << "largest element: " << largest << '\n';

    std::cout << "after removing the largest element, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}

void test_set_multiset ()
{
    auto comp = [](int v1, int v2) {return v1 > v2;};
    std::set<int, decltype(comp)> aSet(comp);
//    std::set<int> aSet;

    std::vector<int> values { 3, 1, 4, 1, 5, 9 };
    for (int v : values)
    {
        aSet.emplace(v);
    }

//    *aSet.begin() = 10;

    printf ("A set:\n");
    std::for_each(aSet.begin(), aSet.end(), [&](const int r){printf("%d,", r);});
    printf("\n");
}

void test_map_multimap()
{
    auto comp = [](int v1, int v2) {return v1 > v2;};
    std::multimap<int, int, decltype(comp)> gquiz1(comp);

    gquiz1.insert(std::pair <int, int> (1, 40));
    gquiz1.insert(std::pair <int, int> (2, 30));
    gquiz1.insert(std::pair <int, int> (3, 60));
    gquiz1.insert(std::pair <int, int> (4, 20));
    gquiz1.insert(std::pair <int, int> (5, 50));
    gquiz1.insert(std::pair <int, int> (6, 50));
//    gquiz1.insert(std::pair <int, int> (6, 10));
    gquiz1.emplace(6,10);

    // printing multimap gquiz1
    std::multimap <int, int> :: iterator itr;
    std::cout << "\nThe multimap gquiz1 is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr)
    {
        std::cout  <<  '\t' << itr->first
              <<  '\t' << itr->second << '\n';
    }
    std::cout << std::endl;

    // assigning the elements from gquiz1 to gquiz2
    std::multimap <int, int> gquiz2(gquiz1.begin(),gquiz1.end());

    // print all elements of the multimap gquiz2
    std::cout << "\nThe multimap gquiz2 after assign from gquiz1 is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        std::cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }
    std::cout << std::endl;

    // remove all elements up to element with value 30 in gquiz2
    std::cout << "\ngquiz2 after removal of elements less than key=3 : \n";
    std::cout << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        std::cout << '\t' << itr->first
             << '\t' << itr->second << '\n';
    }

    // remove all elements with key = 4
    int num;
    num = gquiz2.erase(4);
    std::cout << "\ngquiz2.erase(4) : ";
    std::cout << num << " removed \n" ;
    std::cout << "\tKEY\tELEMENT\n";

    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr)
    {
        std::cout << '\t' << itr->first << '\t' << itr->second << '\n';
    }

    std::cout << std::endl;

    //lower bound and upper bound for multimap gquiz1 key = 5
    std::cout << "gquiz1.lower_bound(5) : " << "\tKEY = ";
    std::cout << gquiz1.lower_bound(5)->first << '\t';
    std::cout << "\tELEMENT = " << gquiz1.lower_bound(5)->second << std::endl;
    std::cout << "gquiz1.upper_bound(5) : " << "\tKEY = ";
    std::cout << gquiz1.upper_bound(5)->first << '\t';
    std::cout << "\tELEMENT = " << gquiz1.upper_bound(5)->second << std::endl;
}


void test_deque()
{
//    As opposed to std::vector, the elements of a deque are not stored contiguously
    std::deque<int> d = {7, 5, 16, 8};

    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);

    // Iterate and print values of deque
    for(int n : d) {
        std::cout << n << '\n';
    }

    printf("Num %d is %d\n", 3, d[3]);
    d.pop_back();
    d.pop_front();
    printf("Num %d is %d\n", 3, d[3]);


//    std::queue<int> q = {2, 9, 34, 17};
    std::queue<int> q;
    q.push(45);
    printf("First pop of queue is %d\n", q.front());
    q.pop();
}

//#include <iterator>
//#include <ranges>
//void test_cpp20()
//{
//    std::vector<int> v = {7, 1, 4, 0, -1};
//    std::ranges::sort(v);
//}

#include <thread>
#include <list>

void func(int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "thread " << n << " ended" << '\n';
}
void test_vector()
{
   std::vector<std::thread> v;
    v.emplace_back(func, 1);
    v.emplace_back(func, 2);
    v.emplace_back(func, 3);
    std::list<std::thread> l;
    // copy() would not compile, because std::thread is noncopyable

    std::move(v.begin(), v.end(), std::back_inserter(l));
    for (auto& t : l) t.join();
}

int findTheBit(const std::bitset<32>& est, int low, int high)
{
    std::bitset<32> mask;
    if (low == high)
        return high;
    else if (low == high-1)
    {
        for (int i=low;i<32;++i)
            mask.set(i, true);
        mask&=est;
        if (mask.to_ulong()>0)
        {
            return low;
        }
        else
        {
            return high;
        }
    }

    int index = (low + high) / 2;
    for (int i=index;i<32;++i)
        mask.set(i, true);

    mask&=est;
    if (mask.to_ulong()>0)
    {
        return findTheBit(est, index, high);
    }
    else
    {
        return findTheBit(est, low, index);
    }
}

void test_bitset()
{
    int est_value = 65537;
    std::bitset<32> est = est_value;

    std::bitset<32> value;
    for (int i=16;i<32;++i)
        value.set(i, true);
    std::cout << value << std::endl;

    printf ("The highest bit of %d is %d\n", est_value, findTheBit(est, 0, 31));
}

struct IntEqual {
public:
    bool operator()(const int str1, const int & str2) const {
        return str1%2 == str2%2;
    }
};

void test_hashing()
{
    std::bitset<4> b1(1);
    std::bitset<4> b2(2);
    std::bitset<4> b3(b2);

    std::hash<std::bitset<4>> hash_fn;

    size_t h1 = hash_fn(b1);
    size_t h2 = hash_fn(b2);
    size_t h3 = hash_fn(b3);

    std::cout << h1 << '\n';
    std::cout << h2 << '\n';
    std::cout << h3 << '\n';

    //TODO_

    std::unordered_set<int, std::hash<int>, IntEqual> hsInts;
    hsInts.insert(19);
    hsInts.insert(14);
    hsInts.insert(16);
//    hsInts.insert(16);
    hsInts.insert(18);
    hsInts.insert(13);

//    hsInts.erase(19);

    auto iter = hsInts.find(12);
    std::cout << *iter << std::endl;

    auto iter_pair = hsInts.equal_range(2);
    printf("hash equal range ");
    std::for_each(iter_pair.first, iter_pair.second, [](int r){printf("%d,", r);});
    printf("\n");
    printf("hash set contains ");
    std::for_each(hsInts.begin(), hsInts.end(), [](int r){printf("%d,", r);});
    printf("\n");
}

void test_copy ()
{
    std::vector<int> v(10, 2);
//    std::vector<int> v(10);
    std::partial_sum(v.cbegin(), v.cend(), v.begin());
    std::cout << "Among the numbers: ";
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    if (std::all_of(v.cbegin(), v.cend(), [](int i){ return i % 2 == 0; })) {
        std::cout << "All numbers are even\n";
    }
    if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(),
                                                     std::placeholders::_1, 2))) {
        std::cout << "None of them are odd\n";
    }

    struct DivisibleBy
    {
        const int d;
        DivisibleBy(int n) : d(n) {}
        bool operator()(int n) const { return n % d == 0; }
    };

    if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
//    if (std::any_of(v.cbegin(), v.cend(), [](int i){ return i % 17 == 0; })) {
        std::cout << "At least one number is divisible by 7\n";
    }
    else
    {
        std::cout << "Not even one number is divisible by 17\n";
    }
}

template <typename Container>
bool in_quote(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}

void test_search()
{
    std::string str = "why waste time learning, when ignorance is instantaneous?";
    // str.find() can be used as well
    std::cout << std::boolalpha << in_quote(str, "learning") << '\n' << std::noboolalpha << in_quote(str, "lemming")  << '\n';
}

void test_partition()
{
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
    std::cout << "Original vector:\n    ";
    for(int elem : v) std::cout << elem << ' ';

    auto it = std::partition(v.begin(), v.end(), [](int i){return i % 2 == 0;});

    std::cout << "\nPartitioned vector:\n    ";
    std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
}

void test_whatever_you_want()
{
//    Ints vs = sorted_ints;
//    int value = 7;
//
////    auto iter = std::upper_bound(vs.begin(), vs.end(), value);
//    auto iter = std::lower_bound(vs.begin(), vs.end(), value);
//    printVector(vs);
//    printf ("%d Position in is %d", value, std::distance(vs.begin(), iter));
//
//    std::forward_list<int> fls1;
//    std::forward_list<int> fls2;
//    fls1.merge(fls2);
//
//    std::list<int> ls;
//
//    std::queue<int> q;
//    q.push(1);
//
//    std::priority_queue<int> pq;
//    pq.push(1);
//    pq.pop();
//
//    std::string s ("hello wor  ld!");
//////    std::remove_if(s.begin(), s.end(), std::isspace);
//    std::cout << s << std::endl;
//    auto end_iter = std::remove_if(s.begin(), s.end(), [](const char c) {return std::isspace(c);});
//    std::cout << s << std::endl;
//    std::cout << std::endl << s << " length:" << s.length() << " end of sequence: " << std::distance(s.begin(), end_iter) << std::endl;
//    s.erase(end_iter, s.end());
//    std::cout << s << std::endl;
//
//    printVector(sorted_ints);
//    auto a_end_iter = std::remove_if(sorted_ints.begin(), sorted_ints.end(), [=](const int i) {return i==value || i==2;});
//    printVector(sorted_ints);
//    sorted_ints.erase(a_end_iter, sorted_ints.end());
//    printVector(sorted_ints);

//    std::cout << strcmp("amy", "david") << std::endl;
//    std::cout << strcmp("jones", "smith") << std::endl;

//    std::vector<int> ts = {2, 5, 8, 3, 6, 7};
////    std::sort(ts.begin(), ts.end(), [](const int a, const int b) {return a > b;});
//    std::sort(ts.begin(), ts.end());
//
//    printVector(ts);
//
//    auto iter = std::upper_bound(ts.begin(), ts.end(), 4);
//    std::rotate (ts.begin(), iter, ts.end());
//    printVector(ts);
//
//    auto a_iter = std::remove (ts.begin(), ts.end(), 7);
//    ts.erase(a_iter, ts.end());
//    printVector(ts);
//
//    std::vector<std::pair<time_t, double>> vec; // must be sorted!
//
//    double target = 1.3;
//
//    auto it = std::lower_bound(vec.begin(), vec.end(), target,
//                               [](std::pair<int, double> const & x, double d)
//                               { return x.second < d; });
//
//    time_t aa;
//    time_t bb;
//
//    auto ait = std::lower_bound(vec.begin(), vec.end(), aa,
//                               [](std::pair<time_t, double> const & x, time_t d)
//                               { return x.first < d; });
//
//
//    bool k = aa<bb;

//    typedef std::pair<time_t, int> TimeValue;
//    std::vector<TimeValue> m_timedValues;
//    auto a_iter = std::lower_bound(m_timedValues.begin(), m_timedValues.end(), a, [](TimeValue const& tv, time_t t){t<=tv.first;});

//    std::unordered_map<std::pair<int,int>, int> map1;
//    std::map<std::pair<int,int>, int> map2;
//    std::map<A, int> map2;

//    std::unordered_map<A, int> map1;      This will have syntax error!!!
//    std::unordered_map<A, int, AHash> map1;
//    std::unordered_set<A> set1;
//    std::set<A> set2;
//
//    std::string s = "Hello World!";
//    std::replace(s.begin(), s.end(), 'o', 'O');
//
//    std::cout << s << std::endl;

//    A aA(51010);
//    printVector(aA.m_values);

//    std::forward_list<int> values1 = {4,1,8,4,5};
//    std::forward_list<int> values2 = {5,0,1,8,4,5};
//
//    std::stack<int> values1_stack;
//    std::stack<int> values2_stack;
//
//    for(auto iter = values1.begin(); iter != values1.cend(); ++iter)
//    {
//        values1_stack.push(*iter);
//    }
//
//    for(auto iter = values2.begin(); iter != values2.cend(); ++iter)
//    {
//        values2_stack.push(*iter);
//    }
//
//    std::stack<int> values_stack;
//    while(!values1_stack.empty()&&!values2_stack.empty())
//    {
//        int v1 = values1_stack.top();
//
//        int v2 = values2_stack.top();
//
//        if(v1!=v2)
//            break;
//        else
//        {
//            values_stack.push(v1);
//            values1_stack.pop();
//            values2_stack.pop();
//        }
//    }
//
//    if (values_stack.empty())
//        std::cout << "no overlap" << std::endl;
//    else
//        std::cout << values_stack.top() << std::endl;

//    std::cout << *() << std::endl;


//  std::forward_list<int> lls = {4, 2, 5};
//  std::cout << lls << std::endl;
//  lls.reverse();
//  std::cout << lls << std::endl;
//
//  Ints values = sorted_ints;
//  std::cout << values;

//  std::map<int, std::string> testMap;
//  testMap.emplace(0, "hello");
//  testMap.emplace(1, "world");
//
//  for (auto & [k, v] : testMap)
//  {
//    std::cout << k << "," << v << std::endl;
//  }
//
//  std::vector<std::pair<int, std::string>> vPairs;
//  vPairs.emplace_back(0, "hello");
//  vPairs.emplace_back(1, "world");
//
//  for (auto & [k, v] : vPairs)
//  {
//    std::cout << k << "," << v << std::endl;
//  }
//
////  auto [k, v] = vPairs.front();
////  int k;
////  std::string v;
//  auto [k, v] = vPairs.front();
//  std::cout << k << "," << v << std::endl;
//
//  if (auto [k, v] = vPairs.back(); k>0)
//    std::cout << k << "," << v << std::endl;

//  int index(0);
//  do
//  {
//    auto [kk, vv] = vPairs[index++];
//    std::cout << kk << "," << vv << std::endl;
//    if (kk > 0)
//      break;
//  }
//  while (true);
//  int index = 0;
//  for (auto [kk, vv] = vPairs[index]; kk <=0 ; ++index, [kk, vv] = vPairs[index]) {
//  }
}

void minimumBribes(std::vector<int> q) {
    int count = q.size();
    int times = 0;
    std::vector<int> bribes(count, 0);
    for (int i = 0; i < count; ++i) {
        int value = i+1;
        if (q[i] == value) {

        }
        else
        {
            auto iter = std::find(q.begin() + i, q.end(), value);
            int dist = std::distance(q.begin() + i, iter);
            std::rotate(q.begin() + i, iter, iter + 1);
            std::rotate(bribes.begin() + i, bribes.begin()+i+dist, bribes.begin()+i+dist + 1);
            std::for_each(bribes.begin() + i + 1, bribes.begin() + i + 1 + dist,
                          [&](int &i) { ++i; });
            times += dist;
        }

        if (bribes[i]>2) {
            std::cout << "Too chaotic" << std::endl;
            return;
        }
    }
    std::cout << times << std::endl;
}

void test_rotate()
{
    Ints values = {1,2,3,4,5,6,7};
    int step = 3;

    printVector(values);
    int count = values.size();
//    std::rotate(values.begin(), values.begin() + count - step, values.end());

    Ints swap;
    swap.reserve(step);
    std::copy(values.begin() + count - step, values.end(), std::back_inserter(swap));
//    swap.resize(step);
//    std::copy(values.begin() + count - step, values.end(), swap.begin());
    std::cout << "swap:"; printVector(swap);
    std::copy(values.begin(), values.begin() + count - step, values.begin()+step);
    std::copy(swap.begin(), swap.end(), values.begin());

    printVector(values);
}

#pragma pack(push, 1)
class SB
{
private:
    bool member1_;
    int  member2_;
public:
    std::vector<int> member3_;
    char* member4_;

    SB ()
    {
        std::cout << "Constructor" << std::endl;
    }

    ~SB ()
    {
        std::cout << "Destructor" << std::endl;
    }

    SB(const SB& sb)     {
        this->member3_ = sb.member3_;
        std::cout << "Copy Constructor" << std::endl;
    }

    SB& operator= (const SB& sb)
    {
        this->member3_ = sb.member3_;
        std::cout << "Assignment" << std::endl;
        return *this;
    }

    SB(SB&& sb)
    {
        this->member3_ = std::move(sb.member3_);
//        this->member3_ = sb.member3_;
        std::cout << "Move Constructor" << std::endl;
    }

    SB& operator= (SB&& sb)
    {
        this->member3_ = std::move(sb.member3_);
//        this->member3_ = sb.member3_;
        std::cout << "Move Assignment" << std::endl;
        return *this;
    }
};
#pragma pack(pop)

typedef std::vector<SB> SBS;

SB returnSB ()
{
    return SB();
}

void test_move_constructor()
{
    SB sb;
    SB sb1;
    SB sb2;
//    SBS sbs;
    sb.member3_.resize(4);
    std::cout << &sb.member3_ << std::endl;
    SB sbm = std::move(sb);
    std::cout << sbm.member3_.size() << ',' << sb.member3_.size() << std::endl;
    std::cout << &sbm.member3_ << ',' << &sb.member3_ << std::endl;
    SB sbm1 = std::move(sb1);

//    std::cout << &sb << std::endl;
//    std::cout << &sb1 << std::endl;
//    std::cout << &sb2 << std::endl;
//
//    std::cout << &sbm << std::endl;
//    std::cout << &sbm1 << std::endl;

//    sbs.push_back(sb);
//    sbs.emplace_back(sb);
//    sbs.push_back(std::move(sb));
//    sbs.push_back(sb1);
}

void test_stl()
{
//    test_functional();
//    test_priorityQueue();
//    test_heap();
//    test_set_multiset ();
//    test_map_multimap ();
//    test_deque();

//    test_cpp20();
//    test_bitset();

//    test_copy();
//    test_search();

//    test_hashing();

//    test_partition();
//    test_whatever_you_want ();

//    test_rotate();

    test_move_constructor();

//    minimumBribes ({2, 5, 1, 3, 4});
//    minimumBribes ({2, 1, 5, 3, 4});
}

#endif //CPPSANDBOX_STL_TESTOUT_H
