#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/minimum-degree-of-a-connected-trio-in-a-graph/
class Solution
{
public:
    // first test, time runout, shouldn't use this hash thing...
    // switch to array, this one passed!
    int minTrioDegree(int n, vector<vector<int>> &edges)
    {
        int ret = -1;
        vector<vector<int>> ess(n, vector<int>(n, -1));
        vector<int> e_num(n, 0);
        for (const vector<int> &edge : edges)
        {
            ess[edge[0] - 1][edge[1] - 1] = 1;
            ess[edge[1] - 1][edge[0] - 1] = 1;
            e_num[edge[0] - 1]++;
            e_num[edge[1] - 1]++;
        }
        auto IsConnected = [&ess](const int &i, const int &j) -> bool
        {
            if (i == j)
                return false;
            return ess[i][j] != -1;
        };

        for (const vector<int> &edge : edges)
        {
            const int &i = edge[0] - 1;
            const int &j = edge[1] - 1;
            for (int k = 0; k < n; k++)
            {
                if(IsConnected(i,k)&&IsConnected(j,k))
                {
                    int cnt = e_num[i] + e_num[j] + e_num[k] - 6;
                    if(0 == cnt)
                    {
                        return 0;
                    }
                    if(ret == -1 || ret > cnt)
                    {
                        ret = cnt;
                    }
                }
            }
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
    int degree;
};
struct T_TestCase
{
    int n;
    vector<vector<int>> edges;
};
static vector<T_TEST_CONTAINER<T_TestExpect, T_TestCase>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, {3}, {6, {{1, 2}, {1, 3}, {3, 2}, {4, 1}, {5, 2}, {3, 6}}}});
    sg_vec_test_cases.push_back({2, {0}, {7, {{1, 3}, {4, 1}, {4, 3}, {2, 5}, {5, 6}, {6, 7}, {7, 5}, {2, 6}}}});
    sg_vec_test_cases.push_back({3, {0}, {4, {{ 1, 2 }, { 4, 1 }, { 4, 2 }}}});
    sg_vec_test_cases.push_back({4, {7}, {17, {{12, 10}, {12, 16}, {4, 9}, {4, 6}, {14, 1}, {9, 2}, {17, 6}, {17, 12}, {8, 9}, {11, 14}, {13, 5}, {8, 15}, {13, 11}, {15, 11}, {15, 14}, {6, 8}, {12, 15}, {14, 12}, {9, 1}, {9, 10}, {10, 5}, {1, 11}, {2, 10}, {15, 1}, {7, 9}, {14, 2}, {4, 1}, {17, 7}, {3, 17}, {8, 1}, {17, 13}, {10, 13}, {8, 13}, {1, 7}, {2, 6}, {13, 6}, {7, 2}, {1, 16}, {6, 3}, {6, 9}, {16, 17}, {7, 14}}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.minTrioDegree(test_case.input.n, test_case.input.edges);
        if (ret != test_case.expect.degree)
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