#include <bits/stdc++.h>
#include "../public/test_macro.h"
using namespace std;
#define CHECK_COND_RET_VAL(con, val) do{if(con)return val;}while(false)
#define CHECK_COND_RET_VOID(con) do{if(con)return;}while(false)
#define CHECK_COND_CONTINUE(con) if(con)continue;
#define CHECK_COND_BREAK(con) if(con)break;

/************************************************************************************************/
/*                                                                                              */
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/*                                                                                              */
/************************************************************************************************/
class Solution
{
public:
    // site: https://leetcode.cn/problems/merge-intervals/
    // version1 : time run out: vector is not list, erase will cost more time!
    vector<vector<int>> merge0(vector<vector<int>> &intervals)
    {
        if(0 == intervals.size()){
            return intervals;
        }
        auto IsNotCross = [](const vector<int> &r1, const vector<int> &r2) -> bool
        {
            CHECK_COND_RET_VAL((2 != r1.size()), false);
            CHECK_COND_RET_VAL((2 != r2.size()), false);
            CHECK_COND_RET_VAL((r1[0] > r1[1]), false);
            CHECK_COND_RET_VAL((r2[0] > r2[1]), false);
            return ((r2[1] < r1[0]) || (r1[1] < r2[0]));
        };
        auto MergeRange = [&IsNotCross](vector<int> &r1, const vector<int> &r2) -> bool
        {
            CHECK_COND_RET_VAL((IsNotCross(r1, r2)), false);
            r1[0] = r1[0] < r2[0] ? r1[0] : r2[0];
            r1[1] = r1[1] > r2[1] ? r1[1] : r2[1];
            return true;
        };
        bool repeat = true;
        while(repeat)
        {
            repeat = false;
            for (auto it = intervals.begin(); it != intervals.end(); ++it)
            {
                auto &r1 = *it;
                for (auto it2 = (it+1); it2 != intervals.end();)
                {
                    auto &r2 = *it2;
                    if (MergeRange(r1, r2))
                    {
                        repeat = true;
                        it2 = intervals.erase(it2);
                    }
                    else
                    {
                        it2++;
                    }
                }
            }
        }

        return intervals;
    }

    // delete erase operation, this one pass
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (0 == intervals.size())
        {
            return intervals;
        }
        std::sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) -> bool
                  { return a[0] < b[0]; });

        const auto input_size = intervals.size();
        vector<vector<int>> merged;
        merged.reserve(input_size);
        merged.push_back(intervals[0]);
        for (auto i = 1; i < input_size; i++)
        {
            if(merged.back()[1] < intervals[i][0])
            {
                merged.push_back(intervals[i]);
            }
            else
            {
                merged.back()[1] = merged.back()[1] > intervals[i][1] ? merged.back()[1] : intervals[i][1];
            }
        }
        merged.shrink_to_fit();
        return merged;
    }

    // example: pay attention to the relationship of each end after sort seperately
    vector<vector<int>> merge_example(vector<vector<int>> &intervals)
    {
        vector<vector<int>> res;
        int n = intervals.size();

        vector<int> L, R;
        for (int i = 0; i < n; i++)
        {
            L.push_back(intervals[i][0]);
            R.push_back(intervals[i][1]);
        }
        sort(L.begin(), L.end());
        sort(R.begin(), R.end());

        for (int i = 0, j = 0; i < n; i++)
        {
            if (i == n - 1 || L[i + 1] > R[i])
            {
                res.push_back({L[j], R[i]});
                j = i + 1;
            }
        }
        return res;
    }
};

/************************************************************************************************/
/*                                                                                              */
/*                                                                                              */
/*                                         Test_Cases                                           */
/*                                                                                              */
/*                                                                                              */
/************************************************************************************************/
struct
{
    int no;
    vector<vector<int>> input;
    vector<vector<int>> expect;
} g_test_examples[] =
    {
        {0, {}, {}},
        {1, {{1, 3}, {2, 6}, {8, 10}, {15, 18}}, {{1, 6}, {8, 10}, {15, 18}}},
        {2, {{1, 4}, {4, 5}}, {{1, 5}}},
};

int main(int argc, char const *argv[])
{
    Solution c{};
    for (auto &example : g_test_examples)
    {
        cout << "\033[32mbegin to run test No." << example.no << "!\033[0m" << endl;
        vector<vector<int>> output = c.merge(example.input);
        EXPECT_EQ(output, example.expect);
    }
    return 0;
}
