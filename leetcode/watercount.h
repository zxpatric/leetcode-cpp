#include <vector>

class Solution {

private:

    static int do_count (const std::vector<int>& height, int start, int end)
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

    static int count (const std::vector<int>& height, int start, int end)
    {
        if (start >= end-1)
            return 0;
        else
        {
            int left = height[start];
            int right = height[end];

            int smaller = (left < right)? left:right;
            int index = -1;
            for (int i = start+1; i < end; ++i)
            {
                int value = height[i];
                if (value > smaller)
                {
                    index = i;
                    smaller = value;
                }
            }

            if (index > 0)
            {
                return count (height, start, index) + count(height, index, end);
            }
            else
            {
                return do_count (height, start, end);
            }
        }
    }
public:
    static int trap(std::vector<int>& height) {
        // search for local minimum
        int num = (int)height.size();
        if (num<=2)
            return 0;

        return count (height, 0, num-1);
    }
};