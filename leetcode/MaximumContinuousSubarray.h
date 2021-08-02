//
// Created by ZhouP on 3/6/2019.
//

#ifndef CPPSANDBOX_MAXIMUMCONTINUOUSSUBARRAY_H
#define CPPSANDBOX_MAXIMUMCONTINUOUSSUBARRAY_H

// The big sum subarray must be!!! A max sum from beginning - the minimum sum from beginning, very tricky!
// Think if it is not the minimum sum from beginning, then it won't be the big sum subarray
class Solution {
public:
    int maxSubArray(int A[], int n) {
        int sum = 0, min = 0, res = A[0];
        for(int i = 0; i < n; i++) {
            sum += A[i];
            if(sum - min > res) res = sum - min;
            if(sum < min) min = sum;
        }
        return res;
    }
};



/* This Divide and Conque method is also very tricky.
 * the idea is: for each sub array we calculate 4 values in O(1) time based on the return values of its two halves. The meaning of the values:

l: the sum of the sub array with largest sum starting from the first element
m: the sum of the sub array with largest sum
r: the sum of the sub array with largest sum ending at the last element
s: the sum of the whole array
 */

struct val {
    int l, m, r, s;
    val(int l, int m, int r, int s):l(l), m(m), r(r), s(s){}
};

class SolutionDQ {
public:
    val dac(int A[], int n) {
        if(n == 1) return val(A[0], A[0], A[0], A[0]);
        val v1 = dac(A, n / 2), v2 = dac(A + n / 2, n - n / 2);
        int l, m, r, s;
        l = max(v1.l, v1.s + v2.l);
        m = max(v1.r + v2.l, max(v1.m, v2.m));
        r = max(v2.r, v1.r + v2.s);
        s = v1.s + v2.s;
        return val(l, m, r, s);
    }
    int maxSubArray(int A[], int n) {
        val v = dac(A, n);
        return v.m;
    }
};

#endif //CPPSANDBOX_MAXIMUMCONTINUOUSSUBARRAY_H
