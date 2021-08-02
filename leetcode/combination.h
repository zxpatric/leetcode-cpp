//
// Created by ZhouP on 3/6/2019.
//

#ifndef CPPSANDBOX_COMBINATION_H
#define CPPSANDBOX_COMBINATION_H

#include "../include/datastructure.h"
#include <sstream>


using namespace std;

int K = 3;

/// @brief An iterative algorithm to generate n choose k combinations
/// @param n - Vector of possible values that n be chosen from
/** @param valid - A check to see if a partial combination is valid
 * For a typical n choose k any partial combination is valid*/
///@param complete - A check to see if a given combination is fully vaild
/**@param stack - A variable that holds the current combination. The function
 * can be called again with the updated stack to get the next combination*/
template<typename T, typename A>
void n_choose_k(vector<T, A> *n, bool (*valid)(vector<typename vector<T, A>::iterator> stack),
                bool (*complete)(vector<typename vector<T, A>::iterator> stack),
                vector<typename vector<T, A>::iterator> *stack) {

    bool firstCall= true;

    //The first time this gets called we need to populate the stack
    //On subsequent calls the flag remains set so that the stack advances and doesn't return a duplicate combination
    if (stack->size() < 1) {
        stack->push_back(n->begin());
        firstCall= false;
    }

    //As soon as we find a complete combination fall through
    //complete in general means the combination is long enough(k) and that it is valid
    //for typical n choose k everything is valid
    while (!complete(*stack) || firstCall) {
        //If the last element is at the end of the n iterator or we've set the 2nd pass flag
        if (n->end() - stack->back() <= 1 || firstCall) {
            //iterate through the stack and either
            for (int i = 0; n->end() - stack->back() <= i + 1; i++) {
                //clear the stack and return if all possibilities have been exhausted
                if (stack->size() == 1) {
                    stack->clear();
                    return;
                }
                //or pop the last element of any stack that is a "conflict set"
                //that is any stack that couldn't possibly be complete
                //ie (1, 6, __) in (1,2,3,4,5,6) choose 3 as there is nothing
                //greater than 6 and the elements go in ascending order
                stack->pop_back();
            }
            //Advance to the next combination
            stack->back()++;

            //unset the flag and continue so we don't skip combinations
            if (firstCall) {
                firstCall= false;
                continue;
            }
        }


        //If the current partial combination(stack) is valid
        if (valid(*stack)) {
            stack->push_back(stack->back());
        }
        //And advance to the next combination
        stack->back()++;
    }
}


bool valid(vector<vector<int>::iterator>  stack){
    return true;
}

bool complete(vector<vector<int>::iterator>  stack){
    return stack.size() == K;
}

int printAllCombinations(vector<int> n ) {
    vector<vector<int>::iterator> stack;
    do {
        n_choose_k(&n, &valid, &complete, &stack);
        for (size_t i = 0; i < stack.size(); i++) {
            cout << *stack[i] << ", ";
        }
        cout << endl;
    } while (!stack.empty());

    return 0;
}

void printCombinations (Ints& values, int end, std::string prefix, const int k)
{
    if (k > end+1)
    {
        return;
    }
//    else if (k == end)
//    {
//        printf("%s", prefix.c_str());
//        for_each (values.begin(), values.begin()+end+1, [&](int v){printf("%d,", v);});
//        printf("\n");
//        return;
//    }
    else if (k == 1)
    {
        for_each (values.begin(), values.begin()+end+1, [&](int v){printf("%s%d\n", prefix.c_str(), v);});
        return;
    }

    //
    int m = *(values.begin()+end);
    printCombinations (values, end-1, prefix+std::to_string(m)+",", k-1);

    printCombinations (values, end-1, prefix, k);
}

class CombinationHelper
{
private:
    int m_k;
    std::vector<int> m_indexs;
    std::vector<int> m_values;
    int m_count;
    bool m_initialized;

    void initialize ()
    {
        for (int i = 0; i < m_k; ++i) {
            m_indexs[i] = i;
        }
    }

public:
    CombinationHelper(Ints& values, const int k) : m_values(values), m_k(k), m_indexs(m_k), m_count(values.size()), m_initialized(false)
    {
    }

    void reset()
    {
        m_initialized = false;
    }

    bool has_next() {
        if (!m_initialized)
            return true;

        //  3 out of [1  2 3 4 5]
        // last is [3 4 5]

        for (int i = 0; i < m_k; ++i) {
            if (m_indexs[i]!=m_count - m_k + i)
                return true;
        }
        return false;
    }

    Ints next()
    {
        if (!m_initialized) {
            initialize();
            m_initialized = true;
        }
        else if (has_next())
        {
            //  3 out of [1  2 3 4 5]
            // [1 4 5]  ->
            // [2 4 5]  ->
            // [2 3 4]

//                    1,2,3,
//                    1,2,4,
//                    1,2,5,
//                    1,3,4,
//                    1,3,5,
//                    1,4,5,
//                    2,3,4,
//                    2,3,5,
//                    2,4,5,
//                    3,4,5,

            // m_indexs go to next
            for (int i = m_k-1; i >= 0; --i) {
                if (m_indexs[i]!=m_count - m_k + i)
                {
                    m_indexs[i]++;
                    for (int j = i+1; j < m_k; ++j) {
                        m_indexs[j] = m_indexs[i] + j - i;
                    }
                    break;
                }
            }
        }
        else
            throw std::logic_error("no next");

        Ints vs;
        vs.reserve(m_k);
        for (int index : m_indexs) {
            vs.push_back(m_values[index]);
        }

        //
        return vs;
    }
};

void printCombinations (Ints& values, const int k)
{
    CombinationHelper ch (values, k);

    do
    {
        Ints vs = ch.next();
        for_each (vs.begin(), vs.end(), [&](int v){printf("%d,", v);});
        printf("\n");
    }
    while (ch.has_next());
}

//void printPermutations (Ints& values, const int k)
//{
//    CombinationHelper ch (values, k);
//
//    do
//    {
//        Ints vs = ch.next();
//        do
//        {
//            for_each (vs.begin(), vs.end(), [&](int v){printf("%d,", v);});
//            printf("\n");
//        }
//        while (std::next_permutation(vs.begin(), vs.end()));
//    }
//    while (ch.has_next());
//}



class PermutationHelper
{
private:
    std::vector<int> m_values;
    bool m_initialized;

    void initialize ()
    {
        std::sort(m_values.begin(), m_values.end());
    }

public:
    PermutationHelper(const Ints& values) : m_values(values), m_initialized(false)
    {

    }

    void reset()
    {
        m_initialized = false;
    }

    bool has_next() {
        if (!m_initialized)
            return true;

        // if every number is greater than next, then it is the last
        for (int i = 0; i < m_values.size()-1; ++i) {
            if(m_values[i] < m_values[i+1])
                return true;
        }

        return false;
    }

    Ints next()
    {
        if (!m_initialized)
        {
            m_initialized = true;
        }
        else if (has_next())
        {
            //next permutation
            //NextPermutation
            int index = -1;
            for (int i = 0; i < m_values.size()-1; ++i) {
                if(m_values[i] < m_values[i+1])
                    index = i;
            }

            // 45321  -> 41235  ->
            // 51234


            // 45132 -> 45123 ->
            // 45213

            std::sort(m_values.begin()+index+1, m_values.end());
            auto iter = std::upper_bound(m_values.begin()+index+1, m_values.end(), *(m_values.begin()+index));
            std::iter_swap(m_values.begin()+index, iter);
//            std::sort(m_values.begin()+index+1, m_values.end());
        }
        else
            throw std::logic_error("no next");

        return m_values;
    }
};

void printPermutations (Ints& values, const int k)
{
    CombinationHelper ch (values, k);

    do
    {
        PermutationHelper ph (ch.next());
        do
        {
            Ints vs = ph.next();
            for_each (vs.begin(), vs.end(), [&](int v){printf("%d,", v);});
            printf("\n");
        }
        while (ph.has_next());
    }
    while (ch.has_next());
}

void test_combination_permutation ()
{
//    Ints values = {1, 3, 2, 5, 3, 6};
//    Ints values = {1, 2, 3};
//    printAllCombinations(values);
//    printCombinations (values, values.size()-1, "", K);
//    printPermutations (values, K);

    Ints values = {1, 2, 3, 4, 5};
    printCombinations (values, K);

//    printVector<decltype(values)::value_type>(values);
//    auto low_iter = std::lower_bound(values.begin(), values.end(), 2);
//    printf("lower bound is at position %d\n", std::distance(values.begin(), low_iter));
//    printVector<decltype(values)::value_type>(values);
//    auto high_iter = std::upper_bound(values.begin(), values.end(), 4);
//    printf("higher bound is at position %d\n", std::distance(values.begin(), high_iter));
}


#endif //CPPSANDBOX_COMBINATION_H
