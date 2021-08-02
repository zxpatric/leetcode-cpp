// This is a good example of using hash table to store information for quick dynamic time

#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <exception>
#include <future>

std::pair<int, int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map <int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        auto iter = map.find(complement);
        if (iter!=map.end()) {
            return std::pair<int, int>(iter->second, i);
        }
        map.emplace(nums[i], i);
    }
    throw std::logic_error("No two sum solution");
}


void test_twoSum () {
    std::vector<int> nums = {1, 2, 4, 4};
    int sum = 8;
    try {
        std::pair<int, int> pair = twoSum(nums, sum);
        std::cout << "Matching pair is :" << pair.first << "," << pair.second << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}


void findMatch1 (const std::vector<int>& nums, const int target, std::promise<std::unordered_map<int, int>>& aMap_promoise, std::promise<std::pair<int, int>>& aPair_promise)
{
    std::unordered_map<int, int> aMap;
    std::pair<int, int> aPair(-1, -1);
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        auto iter = aMap.find(complement);
        if (iter!=aMap.end()) {
            aPair = std::pair<int, int>(i, iter->second);
        }
        aMap.emplace(nums[i], i);
    }

    aMap_promoise.set_value (aMap);
    aPair_promise.set_value (aPair);
}

std::pair<int, int>  findMatch2 (const std::vector<int>& nums, const int target, const std::unordered_map<int, int>& aMap)
{
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        auto iter = aMap.find(complement);
        if (iter!=aMap.end()) {
            return std::pair<int, int>(i, iter->second);
        }
    }

    throw std::invalid_argument("No match found");
}

bool isValidPair (const std::pair<int, int>& pair)
{
    if (pair.first < 0 || pair.second < 0 || pair.first==pair.second)
        return false;

    return true;
}

void test_twoSum_multithread() {
    int sum = 39;
    std::vector<int> nums = {1, 2, 4, 5, 3, 9, 6, 8, 11, 18, 14, 17, 20, 27, 23, 30};
    int half_size = nums.size() /2 ;
    std::vector<int> nums1(nums.begin(), nums.begin()+half_size);
    std::vector<int> nums2(nums.begin()+half_size, nums.end());

//    std::vector<int> nums1 = {1, 2, 4, 5, 3, 9, 6, 8};
//    std::vector<int> nums2 = {11, 18, 14, 17, 20, 27, 23, 30};

//    std::unordered_map<int, int> map1;
//    std::unordered_map<int, int> map2;
//    std::pair<int, int> pair1(-1, -1);
//    std::pair<int, int> pair2(-1, -1);

    std::promise<std::unordered_map<int, int>> map1_promise;
    std::promise<std::unordered_map<int, int>> map2_promise;
    std::promise<std::pair<int, int>> pair1_promise;
    std::promise<std::pair<int, int>> pair2_promise;

    std::thread first(findMatch1, nums1, sum, std::ref(map1_promise), std::ref(pair1_promise));
    std::thread second(findMatch1, nums2, sum, std::ref(map2_promise), std::ref(pair2_promise));

    auto pair1_future = pair1_promise.get_future();
    auto pair2_future = pair2_promise.get_future();

    first.join();
    second.join();

//    auto pairF1 = std::async (std::launch::async, &findMatch1, nums1, sum, map1);
//    auto pairF2 = std::async (std::launch::async, &findMatch1, nums2, sum, map2);
//
//    try
//    {
//        std::pair<int, int> pair1 = pairF1.get();
//        std::cout << pair1.first << "," << pair1.second << std::endl;
//        return;
//    }
//    catch (std::invalid_argument e)
//    {
//
//    }
//
//    try
//    {
//        std::pair<int, int> pair2 = pairF2.get();
//        std::cout << pair2.first << "," << pair2.second << std::endl;
//        return;
//    }
//    catch (std::invalid_argument e)
//    {
//
//    }


    std::pair<int, int> pair1 = pair1_future.get();
    std::pair<int, int> pair2 = pair2_future.get();
    if (!isValidPair(pair1) && !isValidPair(pair2)) {
        auto map1_future = map1_promise.get_future();
        auto map2_future = map2_promise.get_future();

        std::unordered_map<int, int> map1 = map1_future.get();
        std::unordered_map<int, int> map2 = map2_future.get();

        auto pairF1 = std::async (std::launch::async, &findMatch2, nums1, sum, map2);
        auto pairF2 = std::async (std::launch::async, &findMatch2, nums2, sum, map1);

        try
        {
            std::pair<int, int> pair1 = pairF1.get();
            std::cout << pair1.first << "," << pair1.second+half_size << std::endl;
            return;
        }
        catch (std::invalid_argument e)
        {

        }

        try
        {
            std::pair<int, int> pair2 = pairF2.get();
            std::cout << pair2.first+half_size << "," << pair2.second << std::endl;
            return;
        }
        catch (std::invalid_argument e)
        {

        }

    }
    if (isValidPair(pair1))
    {
        std::cout << pair1.first << "," << pair1.second << std::endl;
    }
    if(isValidPair(pair2)) {
        std::cout << pair2.first+half_size << "," << pair2.second+half_size << std::endl;
    }
}

//
//std::vector<int>  nums= {2, 7, 11, 15};
//int target = 27;
//std::pair<int, int> result = Solution::twoSum(nums, target);
//std::cout<<result.first << ","<<result.second << std::endl;