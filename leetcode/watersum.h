#include <vector>

class Solution {

private:
    static int count (const std::vector<int>& height, int start, int end)
    {
        if (start >= end)
            return 0;
        else
        {
            int sum = 0;
            int left = height[start];
            int right = height[end];

            int smaller = (left < right)? left:right;

            for (int i = start+1; i < end; ++i)
            {
                int value = height[i];
                sum += (smaller > value)? smaller-value:0;
            }
            return sum;
        }
    }
public:
    static int trap(std::vector<int>& height) {
        // search for local minimum
        int num = (int)height.size();
        if (num<=2)
            return 0;

        std::vector<bool> isLeft;
        isLeft.resize(num);
        if (height[0]>height[1])
            isLeft[0]=true;
        else
            isLeft[0]=false;
        std::vector<bool> isRight;
        isRight.resize(num);
        if (height[num-1]>height[num-2])
            isRight[num-1] = true;
        else
            isRight[num-1] = false;
        for (int i = 1; i<num-1;++i)
        {
            int value = height[i];
            isLeft[i] = false;
            isRight[i] = false;
            if (value>height[i-1])
                isRight[i] = true;
            if (value>height[i+1])
                isLeft[i] = true;

        }

        bool found_left = false;
        bool found_right = false;
        int start_index = 0;
        int end_index = 0;
        int sum=0;
        for (int i = 0; i<num;++i)
        {
            bool i_am_left = isLeft[i];
            bool i_am_right = isRight[i];
            if (i_am_right)
            {
                end_index = i;
                found_right = true;
            }

            if (i_am_left)
            {
                if(!found_left)
                {
                    found_left = true;
                    start_index = i;
                }
                else if (found_right)
                {
                    sum += count(height, start_index, end_index);
                    start_index = i;
                    found_left = true;
                    found_right = false;
                }
                else
                {

                }
            }

        }

        if (found_left && found_right)
            sum += count(height, start_index, end_index);

        return sum;
    }
};

//    std::vector<int> heights = {0,1,0,2,1,0,1,3,2,1,2,1};
//    printf("%d\n", trap(heights));


//    std::vector<int> input = {6,4,2,0,3,2,0,3,1,4,5,3,2,7,5,3,0,1,2,1,3,4,6,8,1,3};
//    std::vector<int> input = {0,1,0,2,1,0,1,3,2,1,2,1};
//    std::vector<int> input = {5,2,1,2,1,5};
//    std::cout << Solution::trap(input) << std::endl;
