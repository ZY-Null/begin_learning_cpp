#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/minimum-time-to-repair-cars/
class Solution
{
public:
    long long repairCars(vector<int> &ranks, int cars)
    {
        using LLI = long long;
        sort(ranks.begin(), ranks.end());
        // beware, in some platform, int overflow will not auto imporved to long long
        LLI min_time{0}, max_time{(((LONG_LONG_MAX / cars) / cars) > ranks.front()) ? (ranks.front() * static_cast<LLI>(cars) * static_cast<LLI>(cars)) : (LONG_LONG_MAX)};
        while(min_time != max_time)
        {
            LLI cur_time{(min_time + max_time) / 2};
            if(IsTimeValid(ranks,cars,cur_time))
            {
                max_time = cur_time;
            }
            else
            {
                min_time = cur_time + 1;
            }
        }
        return min_time;
    }
private:
    bool IsTimeValid(const vector<int> &ranks, const int &cars, const long long &time)
    {
        //  time = rank * num * num ===》》》 num = sqrt(time / rank)
        auto GetCarMax = [&time](const int &rank) -> int
                        { return static_cast<int>(sqrt(time / rank)); };
        int total_car = 0;
        for(const int &rank:ranks)
        {
            total_car += GetCarMax(rank);
            if(total_car >= cars)
            {
                return true;
            }
        }
        return false;
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
    int car_num;
    vector<int> rank;
};
static vector<T_TEST_CONTAINER<long long, T_TestCase>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, 16, {10, {4, 2, 3, 1}}});
    sg_vec_test_cases.push_back({1, 16, {6, {5, 1, 8}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.repairCars(test_case.input.rank, test_case.input.car_num);
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