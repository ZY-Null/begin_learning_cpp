#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/form-smallest-number-from-two-digit-arrays
class Solution
{
public:
    int minNumber(vector<int> &nums1, vector<int> &nums2)
    {
        int ret = 0;
        int nums[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int min1{10}, min2{10}, direct{10};
        for (const int &val : nums1)
        {
            nums[val]++;
            if(val < min1)
            {
                min1 = val;
            }
        }
        for (const int &val : nums2)
        {
            if(nums[val] == 1)
            {
                if(val < direct)
                {
                    direct = val;
                }
            }
            if (val < min2)
            {
                min2 = val;
            }
        }
        if(10 != direct)
        {
            return direct;
        }
        if(min1 < min2)
        {
            ret = min1 * 10 + min2;
        }
        else
        {
            ret = min2 * 10 + min1;
        }
        return ret;
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
struct T_TestExpect
{
};
struct T_TestCase
{
    vector<int> v1;
    vector<int> v2;
};
static vector<T_TEST_CONTAINER<int, T_TestCase>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, 15, {{4, 1, 3}, {5, 7}}});
    sg_vec_test_cases.push_back({2, 3, {{3, 5, 2, 6}, {3, 1, 7}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.minNumber(test_case.input.v1, test_case.input.v2);
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