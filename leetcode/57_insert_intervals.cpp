
#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/*                                                                                              */
/************************************************************************************************/
// site: https://leetcode.cn/problems/insert-interval/
class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        // attention: this is a array(liked), so dont use erase or any same operations;
        vector<vector<int>> ret;
        size_t intput_size = intervals.size();
        int l = newInterval[0], r = newInterval[1];
        for (size_t i = 0; i < intput_size; i++)
        {
            if(intervals[i][1] < l)
            {
                ret.push_back(intervals[i]);
            }
            else if (intervals[i][0] > r)
            {
                ret.push_back({l, r});
                l = intervals[i][0], r = intervals[i][1];
            }
            else
            {
                l = l < intervals[i][0] ? l : intervals[i][0];
                r = r > intervals[i][1] ? r : intervals[i][1];
            }
        }
        ret.push_back({l, r});
        return ret;
    }
};

/************************************************************************************************/
/*                                                                                              */
/*                                                                                              */
/*                                         Test_Cases                                           */
/*                                                                                              */
/*                                                                                              */
/************************************************************************************************/
struct T_TEST_CASE
{
    int test_id;
    vector<vector<int>> intervals;
    vector<int> newInterval;
    vector<vector<int>> expect;
} g_atTestCases[]{
    {1, {{1, 3}, {6, 9}}, {2, 5}, {{1, 5}, {6, 9}}},
    {2, {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}}, {4, 8}, {{1, 2}, {3, 10}, {12, 16}}},
    {3, {}, {5, 7}, {{5, 7}}},
    {4, {{1, 5}}, {2, 3}, {{1, 5}}},
    {5, {{1, 5}}, {2, 7}, {{1, 7}}},
};

int main(int argc, char const *argv[])
{
    Solution s;
    int fail_cnt = 0;
    for (auto &test_case : g_atTestCases)
    {
        if(test_case.expect != s.insert(test_case.intervals, test_case.newInterval))
        {
            printf("Test failed! case : %u\n", test_case.test_id);
            fail_cnt ++;
        }
    }
    if(0 == fail_cnt)
    {
        printf("All test case pass!\n");
    }
    else
    {
        printf("Total %u case(s) failed!\n", fail_cnt);
    }
    return 0;
}
