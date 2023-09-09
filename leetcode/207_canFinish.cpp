
#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/course-schedule/
constexpr int UNVISITED{0}, CAUTION{1}, IGNORE{-1};
class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> course_rel(numCourses, vector<int>(numCourses, 0));
        vector<int> visited(numCourses, UNVISITED);
        for (const vector<int> &pre : prerequisites)
        {
            course_rel[pre[0]][pre[1]] = 1;
        }
        for (const vector<int> pair : prerequisites)
        {
            if (!SearchOne(visited, pair[0], course_rel))
            {
                return false;
            }
        }
        return true;
    }

private:
    bool SearchOne(vector<int> &visited, const int &cur, const vector<vector<int>> &course_rel)
    {
        if (IGNORE == visited[cur])
        {
            return true;
        }
        if (CAUTION == visited[cur])
        {
            return false;
        }
        visited[cur] = CAUTION;
        auto max = course_rel[cur].size();
        for (auto i = 0; i < max; i++)
        {
            if (0 == course_rel[cur][i])
            {
                continue;
            }
            if (!SearchOne(visited, i, course_rel))
            {
                return false;
            }
        }
        visited[cur] = IGNORE;
        return true;
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
    int nums;
    vector<vector<int>> prerequisites;
};
static vector<T_TEST_CONTAINER<bool, T_TestCase>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, true, {2, {{1, 0}}}});
    sg_vec_test_cases.push_back({1, false, {2, {{1, 0}, {0, 1}}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.canFinish(test_case.input.nums, test_case.input.prerequisites);
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