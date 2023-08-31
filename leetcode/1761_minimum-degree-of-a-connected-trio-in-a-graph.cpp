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
    int minTrioDegree(int n, vector<vector<int>> &edges)
    {
        int ret = -1;
        unordered_map<int, unordered_set<int>> edges_map;
        for(const vector<int> &edge:edges)
        {
            edges_map[edge[0]].emplace(edge[1]);
            edges_map[edge[1]].emplace(edge[0]);
        }
        auto IsPointConnected = [&edges_map](const int &i, const int &j) -> bool
        {
            auto it_0 = edges_map.find(i);
            if(edges_map.end() == it_0)
                return false;
            return it_0->second.end() != it_0->second.find(j);
        };

        for (const auto &edge : edges)
        {
            for (int i = 1; i <= n; i++)
            {
                if(i == edge[0] || i == edge[1])
                {
                    continue;
                }
                if (!(IsPointConnected(i, edge[0]) && IsPointConnected(i, edge[1])))
                {
                    continue;
                }
                int cnt = edges_map[i].size() + edges_map[edge[0]].size() + edges_map[edge[1]].size() - 6;
                if (ret == -1 || ret > cnt)
                {
                    ret = cnt;
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