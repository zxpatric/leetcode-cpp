//
// Created by on 10/23/2018.
// Idea is easy but boundary is tough
//

#ifndef UNTITLED_MEDIAN_H
#define UNTITLED_MEDIAN_H

#include <vector>
#include <math.h>
#include <assert.h>
#include <algorithm>

class Solution {
private:
    inline bool isEqual (double f1, double f2)
    {
        if (std::fabs(f1-f2)< 0.0000001) return true;
        else return false;
    }

    inline double median (const std::vector<int>& nums, int left, int right)
    {
        return (double)(nums[left] + nums[right])/2.0;
    }

    std::vector<int> recursiveSearch (const std::vector<int>& nums1, int n1LeftB, int n1RightB, int n1LeftI, int n1RightI,
                                      const std::vector<int>& nums2, int n2LeftB, int n2RightB, int n2LeftI, int n2RightI)
    {
        double m1 = median(nums1, n1LeftI, n1RightI);
        double m2 = median(nums2, n2LeftI, n2RightI);
        if (isEqual(m1, m2) || (n1LeftB==n1LeftI && n1RightB==n1RightI && n2LeftB==n2LeftI && n2RightB==n2RightI) ||
                (nums1[n1LeftI] <= nums2[n2LeftI] && nums2[n2RightI] <= nums1[n1RightI]) ||
                (nums2[n2LeftI] <= nums1[n1LeftI] && nums1[n1RightI] <= nums2[n2RightI]))
        {
            return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
        }
        else if (m1 < m2)
        {
            int dist2Left = n2LeftI - n2LeftB;
            int step2Left  = (dist2Left+1)/2;
            if (step2Left==0)
            {
                int width  = n2RightI - n2LeftI;
                if (width>0) // width==1 . Step half
                {
                    if (n1LeftI == n1RightI)
                    {
                        if (nums1[n1LeftI] >= nums2[n2LeftI] && nums1[n1LeftI] <= nums2[n2RightI])
                        {
                            return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                        }
                        else
                        {
                            return {nums1[n1LeftI], nums1[n1RightI+1], nums2[n2LeftI], nums2[n2LeftI]};
                        }
                    }
                    else
                    {
                        return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                    }
                }
                else
                {
                    return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                }
            }
            else if (step2Left==1)
            {
                if (n2RightI==n2LeftI)
                {
                    if (n1LeftI == n1RightI)
                    {
                        if (dist2Left<=1)
                            return {nums1[n1LeftI], nums1[n1RightI+1], nums2[n2LeftI-1], nums2[n2LeftI]};
                    }
                    else
                    {
                        if (nums1[n1RightI] >= nums2[n2LeftI] && nums1[n1LeftI] <= nums2[n2RightI])
                        {
                            return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                        }
                        else if (nums1[n1RightI]>= nums2[n2LeftI - 1] && nums1[n1RightI]<=nums2[n2LeftI])
                        {
                            return {nums1[n1LeftI + 1], nums1[n1RightI], nums2[n2LeftI - 1], nums2[n2LeftI]};
                        }
                    }
                }
            }


            n1LeftB = n1RightI;
//            n1RightB = n1RightB;
//            n2LeftB = n2LeftB;
            n2RightB = n2LeftI;

            n1LeftI = n1LeftI + step2Left;
            n1RightI = n1RightI + step2Left;
            n2LeftI = n2LeftI - step2Left;
            n2RightI = n2RightI - step2Left;
            return recursiveSearch (nums1, n1LeftB, n1RightB, n1LeftI, n1RightI, nums2, n2LeftB, n2RightB, n2LeftI, n2RightI);
        }
        else    //m1 > m2
        {
            int dist2Right = n2RightB - n2RightI;
            int step2Right = (dist2Right+1)/2;
            if (step2Right==0)
            {
                int width = n2RightI - n2LeftI;
                if (width>0) // width==1 . Step half
                {
                    if (n1LeftI == n1RightI)
                    {
                        if (nums1[n1LeftI] >= nums2[n2LeftI] && nums1[n1LeftI] <= nums2[n2RightI])
                        {
                            return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                        }
                        else
                        {
                            return {nums1[n1LeftI-1], nums1[n1RightI], nums2[n2RightI], nums2[n2RightI]};
                        }
                    }
                    else
                    {
                        return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                    }
                }
                else
                {
                    return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                }
            }
            else if (step2Right==1)
            {
                if (n2RightI==n2LeftI)
                {
                    if (n1LeftI == n1RightI)
                    {
                        if (dist2Right<=1)
                            return {nums1[n1LeftI-1], nums1[n1RightI], nums2[n2RightI], nums2[n2RightI+1]};
                    }
                    else
                    {
                        if (nums1[n1LeftI] <= nums2[n2RightI] && nums1[n1RightI] >= nums2[n2RightI])
                        {
                            return {nums1[n1LeftI], nums1[n1RightI], nums2[n2LeftI], nums2[n2RightI]};
                        }
                        else if (nums1[n1LeftI]>=nums2[n2RightI]&&nums1[n1LeftI]<=nums2[n2RightI+1])
                        {
                            return {nums1[n1LeftI], nums1[n1RightI-1], nums2[n2RightI], nums2[n2RightI+1]};
                        }
                    }
                }
            }

//            n1LeftB = n1LeftB;
            n1RightB = n1LeftI;
            n2LeftB = n2RightI;
//            n2RightB = n2RightB;

            n1LeftI = n1LeftI - step2Right;
            n1RightI = n1RightI - step2Right;
            n2LeftI = n2LeftI + step2Right;
            n2RightI = n2RightI + step2Right;
            return recursiveSearch (nums1, n1LeftB, n1RightB, n1LeftI, n1RightI, nums2, n2LeftB, n2RightB, n2LeftI, n2RightI);
        }

    }


    inline double findMedianBigMSmallN (const std::vector<int>& numsm, const std::vector<int>& numsn){
        int m = numsm.size();
        int n = numsn.size();

        assert (m>n && "m can't be less than n");

        // (m+n-1)/2   ~  (m+n)/2
        if (numsn.back() <= numsm[(m-n-1)/2])
        {
            return (double)(numsm[(m-n-1)/2]+numsm[(m-n)/2])/2.0;
        }
        else if (numsn.front()>=numsm[(m+n)/2])
        {

            return (double)(numsm[(m+n-1)/2]+numsm[(m+n)/2])/2.0;
        }
        else
        {
            std::vector<int> results = recursiveSearch (numsm, 0, m-1, (m-1)/2, m/2, numsn, 0, n-1, (n-1)/2, n/2);
            std::sort(results.begin(), results.end());
            return (double)(results[1] + results[2])/2.0;
        }
    }
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        if (m==0)
        {
            return (double)(nums2[(n-1)/2]+nums2[n/2])/2.0;
        }
        else if (n==0)
        {
            return (double)(nums1[(m-1)/2]+nums1[m/2])/2.0;
        }
        else
        if(m>n)
        {
            return findMedianBigMSmallN(nums1, nums2);
        }
        else if (m<n)
        {
            return findMedianBigMSmallN(nums2, nums1);
        }
        else
        {
            if (nums1.back() <= nums2.front())
            {
                return (double)(nums1.back()+nums2.front())/2.0;
            }
            else if (nums2.back() <= nums1.front())
            {

                return (double)(nums2.back()+nums1.front())/2.0;
            }
            else
            {
                std::vector<int> results = recursiveSearch (nums1, 0, m-1, (m-1)/2, m/2, nums2, 0, n-1, (n-1)/2, n/2);
                std::sort(results.begin(), results.end());
                return (double)(results[1] + results[2])/2.0;
            }
        }
    }

    int enhanced_moveSameOffset (const std::vector<int>& nums0, int& left0, int& right0, const std::vector<int>& nums1, int& left1, int& right1, double& median)
    {
        if (left1+2>=right1)
        {
            return -1;
        }

        int middle10 = (left1+right1) / 2;
        int middle11 = (left1+right1+1) / 2;
        double median1 = (double)(nums0[middle10] + nums0[middle11])/2.0;

        int middle00 = (left0+right0) / 2;
        int middle01 = (left0+right0+1) / 2;
        double median0 = (double)(nums0[middle00] + nums0[middle01])/2.0;

//        if (median0 == median1)
//        {
//            median = median0;
//            return 0;
//        }
//        else
            if (median0>median1)
        {
            left0 = left0;
            right0 = middle01;
            left1 = middle10;
            right1 = right1;
            return 1;
        }
        else
        {
            left0 = middle00;
            right0 = right0;
            left1 = left1;
            right1 = middle11;
            return 1;
        }
    }


    double enhanced_findMedianRecursive(const std::vector<int>& nums0, int left0, int right0, const std::vector<int>& nums1, int left1, int right1)
    {
        double median;
        int ret = enhanced_moveSameOffset(nums0, left0, right0, nums1, left1, right1, median);
        if (ret==0) // no more movement can be done to left1, clamp1, right1.
        {
            return median;
        }
        else if (ret > 0)
        {
            return enhanced_findMedianRecursive(nums0, left0, right0, nums1, left1, right1);
        }
        else
        {
            // look at range of left0, right0 and left1, right1
            std::vector<int> vs;
            vs.reserve(6);
            for (int i = left0; i <= right0; ++i)
                    vs.push_back(nums0[i]);
            for (int i = left1; i <= right1; ++i)
                    vs.push_back(nums1[i]);

            vs.push_back(10);
            int count = vs.size();
            std::sort(vs.begin(),vs.end());
            return (double)(vs[(count-1)/2] + vs[count/2]) / 2.0;
        }
    }

    double enhanced_findMedianSortedArrays(const std::vector<int>& nums0, const std::vector<int>& nums1)
    {
        // we can do many specific cases, but will skip them

        // we assume nums0.size() > nums1.size()

        int count0 = nums0.size();
        int count1 = nums1.size();

        if (count0 == count1)
        {
            int middle00 = (count0-1) / 2;
            int middle01 = count0 / 2;
            double median0 = (double)(nums0[middle00] + nums0[middle01])/2.0;

            int middle10 = (count1-1)/2;
            int middle11 = count1/2;
            double median1 = (double)(nums1[middle10] + nums1[middle11])/2.0;

            if (median0 == median1)
                return median1;
            else if (median0>median1)
                return enhanced_findMedianRecursive(nums0, middle01 + middle10 - count1 + 1, middle01, nums1, middle10, count1 - 1);
            else
                return enhanced_findMedianRecursive(nums0, middle00, middle00 + middle11, nums1, 0, middle11);
        }
        else
        {
            int left_median_index0 = (count0 - count1 - 1) / 2;
            int left_median_index1 = (count0 - count1) / 2;
            int right_median_index0 = (count0 + count1 - 1) / 2;
            int right_median_index1 = (count0 + count1) / 2;
            if (nums1[count1-1]<=nums0[left_median_index0])
            {
                return (double)(nums0[left_median_index0] + nums0[left_median_index1]) / 2.0;
            }
            else if (nums1[0]>=nums0[right_median_index1])
            {
                return (double)(nums0[right_median_index0] + nums0[right_median_index1]) / 2.0;
            }
            else
            {
                int middle00 = (count0-1) / 2;
                int middle01 = count0 / 2;
                double median0 = (double)(nums0[middle00] + nums0[middle01])/2.0;

                int middle10 = (count1-1)/2;
                int middle11 = count1/2;
                double median1 = (double)(nums1[middle10] + nums1[middle11])/2.0;

                if (median0 == median1)
                    return median1;
                else
                    {
                        count0 -= 1;
                        middle00 = (count0-1) / 2;
                        middle01 = count0 / 2;

                    if (median0 > median1)
                        return enhanced_findMedianRecursive(nums0, middle01 + middle10 - count1 + 1, middle01, nums1,
                                                            middle10, count1 - 1);
                    else
                        return enhanced_findMedianRecursive(nums0, middle00, middle00 + middle11, nums1, 0, middle11);
                }
            }
        }
    }

//
//    int getKth(Ints nums1, int start1, int end1, Ints nums2, int start2, int end2, int k) {
//        int len1 = end1 - start1 + 1;
//        int len2 = end2 - start2 + 1;
//        //让 len1 的长度小于 len2，这样就能保证如果有数组空了，一定是 len1
//        if (len1 > len2) return getKth(nums2, start2, end2, nums1, start1, end1, k);
//
//        if (len1 == 0) return nums2[start2 + k - 1];
//
//        if (k == 1)
//        {
//            return std::min(nums1[start1], nums2[start2]);
//        }
//
//        int i = start1 + std::min(len1, k / 2) - 1;
//        int j = start2 + std::min(len2, k / 2) - 1;
//
//        if (nums1[i] > nums2[j]) {
//            return getKth(nums1, start1, end1, nums2, j + 1, end2, k - (j - start2 + 1));
//        }
//        else {
//            return getKth(nums1, i + 1, end1, nums2, start2, end2, k - (i - start1 + 1));
//        }
//    }

    int getKth(Ints& nums1, int start1, int end1, Ints& nums2, int start2, int end2, int k) {
        int len1 = end1 - start1 + 1;
        int len2 = end2 - start2 + 1;

        if (len1 > len2)
            return getKth (nums2, start2, end2, nums1, start1, end1, k);

        if (len1 == 0)
            return nums2[start2 + k - 1];

        if (k==1)
            return std::min(nums1[start1], nums2[start2]);

        int i = start1 + std::min(len1, k/2) - 1;
        int j = start2 + std::min(len2, k/2) - 1;

        if (nums1[i]>nums2[j])
        {
            return getKth(nums1, start1, end1, nums2, j+1, end2, k - (j - start2 +1));
        }
        else
        {
            return getKth(nums1, i+1, end1, nums2, start2, end2, k - (i - start1 +1));
        }
    }


    double mnfindMedianSortedArrays(Ints nums1, Ints nums2) {
        int n = nums1.size();
        int m = nums2.size();
        int left = (n + m + 1) / 2;
        int right = (n + m + 2) / 2;
        //将偶数和奇数的情况合并，如果是奇数，会求两次同样的 k 。
        return 0.5*(getKth(nums1, 0, n - 1, nums2, 0, m - 1, left) + getKth(nums1, 0, n - 1, nums2, 0, m - 1, right));
    }

    double mnMinfindMedianSortedArrays(Ints& A, Ints& B) {
        int m = A.size();
        int n = B.size();
        if (m > n) {
            return mnMinfindMedianSortedArrays(B,A); // 保证 m <= n
        }
        int iMin = 0, iMax = m;
        while (iMin <= iMax) {
            int i = (iMin + iMax) / 2;
            int j = (m + n + 1) / 2 - i;
            if (j != 0 && i != m && B[j-1] > A[i]){ // i 需要增大
                iMin = i + 1;
            }
            else if (i != 0 && j != n && A[i-1] > B[j]) { // i 需要减小
                iMax = i - 1;
            }
            else { // 达到要求，并且将边界条件列出来单独考虑
                int maxLeft = 0;
                if (i == 0) { maxLeft = B[j-1]; }
                else if (j == 0) { maxLeft = A[i-1]; }      //only possible when m == n
                else { maxLeft = std::max(A[i-1], B[j-1]); }
                if ( (m + n) % 2 == 1 ) { return maxLeft; } // 奇数的话不需要考虑右半部分

                int minRight = 0;
                if (i == m) { minRight = B[j]; }
                else if (j == n) { minRight = A[i]; }   //only possible when m == n
                else { minRight = std::min(B[j], A[i]); }

                return (maxLeft + minRight) / 2.0; //如果是偶数的话返回结果
            }
        }
        return 0.0;
    }


private:
    int m_extraLarge;
    bool m_01;
};

void test_findMedian(){
    Solution solution;
//    std::vector<int> num1 = {1, 4, 5};
//    std::vector<int> num2 = {2, 3, 6};
//    std::vector<int> num1 = {1, 2, 8};
//    std::vector<int> num2 = {4, 5, 6};
//    std::vector<int> num1 = {0, 1, 2, 7};
//    std::vector<int> num2 = {3, 4, 5, 6, 7};
//    std::vector<int> num1 = {1,3};
//    std::vector<int> num2 = {2,4,5};
//    std::vector<int> num1 = {};
//    std::vector<int> num2 = {2,4};
//    std::vector<int> num1 = {1,5};
//    std::vector<int> num2 = {2,3,4,6};
//        std::vector<int> num1 = {1,2,4};
    std::vector<int> num1 = {2, 3,5,6,7, 9, 10};
    std::vector<int> num2 = {0,1, 4, 8};
//    std::vector<int> num2 = {3,4,6,7};
//    std::vector<int> num1 = {2,5,6,7, 9};
//    std::vector<int> num2 = {1,3,4};
//    std::vector<int> num1 = {1, 2, 6, 7};
//    std::vector<int> num2 = {3, 4, 5, 8};
//    std::vector<int> num1 = {1,2,3,4,7};
//    std::vector<int> num2 = {5,6,8,9,10};

    //    double median = solution.findMedianSortedArrays(num1, num2);
//    printf("median is %f\n", median);

    printVector(num1);
    printVector(num2);
//    std::cout << "meidan is " << solution.enhanced_findMedianSortedArrays(num1, num2) << std::endl;
//    std::cout << "meidan is " << solution.mnfindMedianSortedArrays(num1, num2) << std::endl;
    std::cout << "meidan is " << solution.mnMinfindMedianSortedArrays(num1, num2) << std::endl;
}

#endif //UNTITLED_MEDIAN_H
