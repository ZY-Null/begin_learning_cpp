#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/two-sum/
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> mnums, mnums_same;
        size_t len = nums.size();
        for (size_t i = 0; i < len; i++)
        {
            if(mnums.end() != mnums.find(nums[i]))
            {
                mnums_same.emplace(nums[i], i);
            }
            else
            {
                mnums.emplace(nums[i], i);
            }
        }
        for(const auto &p:mnums)
        {
            int j = target - p.first;
            if(p.first == j)
            {
                auto it = mnums_same.find(j);
                if(it != mnums_same.end())
                {
                    if (p.second < it->second)
                        return {p.second, it->second};
                    else
                        return {it->second, p.second};
                }
            }
            else
            {
                auto it = mnums.find(j);
                if (it != mnums.end())
                {
                    if (p.second < it->second)
                        return {p.second, it->second};
                    else
                        return {it->second, p.second};
                }
            }
        }
        return {0, 0};
    }
};
/************************************************************************************************/
/*                                                                                              */
/*                                         Test_Cases                                           */
/*                                                                                              */
/************************************************************************************************/
template <class T_OUT, class T_INT>
struct T_TEST_CONTAINER
{
    int id;
    T_OUT expect;
    T_INT input;
};
// define your test case type here:
struct T_Test
{
    int target;
    vector<int> nums;
};

static vector<T_TEST_CONTAINER<vector<int>, T_Test>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, {0, 1}, {9, {2, 7, 11, 15}}});
    sg_vec_test_cases.push_back({2, {1, 2}, {6, {3, 2, 4}}});
    sg_vec_test_cases.push_back({3, {0, 1}, {6, {3, 3}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.twoSum(test_case.input.nums, test_case.input.target);
        if (ret != test_case.expect)
        {
            all_test_ok = false;
            printf("test_case id:%d test failed! expect %d, actually:%d\n", test_case.id, test_case.expect, ret);
        }
    }
    if (all_test_ok)
    {
        printf("all test_case running successfully!\n");
    }
    return 0;
}