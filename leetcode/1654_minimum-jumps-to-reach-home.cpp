#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/minimum-jumps-to-reach-home/
class Solution
{
public:
    int minimumJumps(vector<int> &forbidden, int a, int b, int x)
    {
        // i cant solve it! i'll learn the answer...
        unordered_set<int> forb;
        for(const int &i:forbidden)
        {
            forb.emplace(i);
        }
        auto IsForbid = [&forb](const int &val)
                        { return forb.end() != forb.find(val); };
        int cnt = 1;
        int cur_pos = a;
        bool leftable = true;
        int after_left_distence{0};
        while(cur_pos != x)
        {
            if(cur_pos > x && leftable)
            {
                int new_pos = cur_pos - b;
                if (!((IsForbid(new_pos)) || (new_pos < 0)))
                {
                    cur_pos = new_pos;
                    cnt ++;
                    if(cur_pos > x)
                    {
                        int diff = cur_pos - x;
                        if(after_left_distence != 0)
                        {
                            if(diff > after_left_distence)
                            {
                                return -1;
                            }
                        }
                        after_left_distence = diff;
                    }
                }
                leftable = false;
            }
            else
            {
                int new_pos = cur_pos + a;
                if(IsForbid(new_pos))
                {
                    return -1;
                }
                cur_pos = new_pos;
                cnt++;
            }
        }
        return cnt;
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
struct T_INPUT
{
    int a;
    int b;
    int x;
    vector<int> forbidden;
};
// define your test case type here:
static vector<T_TEST_CONTAINER<int, T_INPUT>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, 3, {3, 15, 9, {14, 4, 18, 1, 15}}});
    sg_vec_test_cases.push_back({2, -1, {15, 13, 11, {8, 3, 16, 6, 12, 20}}});
    sg_vec_test_cases.push_back({3, 2, {16, 9, 7, {1, 6, 2, 14, 5, 17, 4}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        int ret = s.minimumJumps(test_case.input.forbidden, test_case.input.a, test_case.input.b, test_case.input.x);
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