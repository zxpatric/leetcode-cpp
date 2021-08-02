//
// Created by ZhouP on 3/5/2019.
//

#ifndef CPPSANDBOX_QUICKSORT_H
#define CPPSANDBOX_QUICKSORT_H

#include <stdexcept>
#include "../datastructure.h"

void swap (std::vector<int>& vs, int left, int right)
{
    if (left==right) return;
    int s = vs[left];
    vs[left] = vs[right];
    vs[right] = s;
}

int partition (std::vector<int>& vs, int first, int last)
{
    int pivot = vs[last];

    for (int j = first; j < last; j++)
    {
        if(vs[j]<pivot)
        {
            swap(vs, first, j);
            ++first;
        }
    }
    swap(vs, last, first);
    return first;
}

void internal_quick_sort(std::vector<int>& vs, int first, int last)
{
    if (last - 1 <= first)
        return;

    int index = partition (vs, first, last);

    internal_quick_sort (vs, first, index-1);
    internal_quick_sort (vs, index+1, last);
}

void quick_sort(const std::vector<int> &values, std::vector<int>& results) {
    results = values;
    int len = results.size();
    if (len<2)
        return;

    internal_quick_sort(results, 0, len-1);
}

int internal_quick_select (std::vector<int> &values, int first, int last, int kth)
{
    if (first == last)
    {
        if (last!=kth)
            throw std::runtime_error("algorithm runtime errors");
        else
            return values[last];
    }

    int partition_index = partition (values, first, last);
    if (partition_index == kth)
        return values[partition_index];
    else if (kth < partition_index)
        return internal_quick_select (values, first, partition_index-1, kth);
    else
        return internal_quick_select (values, partition_index+1, last, kth);
}

int quick_select (const Ints &values, int kth)
{
    int num = values.size();
    if (kth<0 || kth>=num)
        throw std::logic_error("input parameter errors");

    Ints lvalues = values;
    return internal_quick_select(lvalues, 0, num-1, kth);
}


void stl_quick_sort (std::vector<int> &values, int first, int last)
{
    if (first>=last)
    {
        return;
    }

    auto iter = std::partition (values.begin() + first, values.begin()+last, [&](int v){return v < values[last];});
    int middle = std::distance(values.begin(), iter);
    std::iter_swap(iter, values.begin()+last);
    stl_quick_sort (values, first, middle-1);
    stl_quick_sort (values, middle+1, last);
}

void test_stl_quick_sort (std::vector<long>& values)
{
//    stl_quick_sort (values, 0, (int)values.size()-1);
//    std::sort(values.begin(), values.end(), [](const int a, const int b){return a < b;});
//    std::sort(values.begin(), values.end(), std::less<int>());
    typedef std::remove_reference<decltype(values)>::type VT;

    std::qsort(&values.front(), values.size(), sizeof(VT::value_type), [](const void* p0, const void* p1)
    {
        const VT::value_type* pi0 = static_cast<const VT::value_type*> (p0);
        const VT::value_type* pi1 = static_cast<const VT::value_type*> (p1);
//        return *pi0 < *pi1;
                if(*pi0 < *pi1) return -1;
                if(*pi0 > *pi1) return 1;
                return 0;
    });

    int a = 11;
    auto iter = std::bsearch(&a, &values.front(), values.size(), sizeof(VT::value_type), [](const void* p0, const void* p1)
    {
        const VT::value_type* pi0 = static_cast<const VT::value_type*> (p0);
        const VT::value_type* pi1 = static_cast<const VT::value_type*> (p1);
//        return *pi0 < *pi1;
        if(*pi0 < *pi1) return -1;
        if(*pi0 > *pi1) return 1;
        return 0;
    });

    printf ("%ld value is %ld\n",  static_cast<VT::value_type*>(iter) - static_cast<VT::value_type*>(&values.front()), *static_cast<const VT::value_type*> (iter));
}

void test_quickss ()
{
//    Ints values = {};   //{1};
    Longs values = unsorted_longs;
//    Ints values = unsorted_intss;
    printf("\nunsorted ");

    typedef std::remove_reference<decltype(values)>::type VT;
    printVector<VT::value_type> (values);
    test_stl_quick_sort(values);
    printf("\nquick sorted ");
    printVector<VT::value_type> (values);
    printf("\n");

    int a(5), b(6);
    printf("%d is greater than %d is %d\n", a, b, std::greater<int>()(a, b));
    printf("%d is less than %d is %d\n", a, b, std::less<int>()(a, b));
}

#endif //CPPSANDBOX_QUICKSORT_H
