#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/course-schedule-iii
class Solution
{
public:
    int scheduleCourse(vector<vector<int>> &courses)
    {
        Clear();
        std::sort(begin(courses), end(courses), [](const vector<int> &c1, const vector<int> &c2) -> bool
                  { return c1[1] < c2[1]; });
        int total = 0;
        for (const vector<int> c:courses)
        {
            const int &t{c[0]};
            const int &d{c[1]};
            if(t + total <= d)
            {
                total += t;
                Add(t);
            }
            else
            {
                if (!Empty())
                {
                    auto max_time = Head();
                    if(max_time > t)
                    {
                        total = total - max_time + t;
                        Pop();
                        Add(t);
                    }
                }
            }
        }
        return GetS();
    }
private:
    struct LN
    {
        int val;
        LN *next;
    };
    LN *r{nullptr};
    size_t _s{0};
    void Add(const int &val)
    {
        _add(val, r);
        _s++;
    }
    void _add(const int &val, LN *&p)
    {
        if(p == nullptr)
        {
            p = new LN{val, nullptr};
            return;
        }
        if(p->val > val)
        {
            return _add(val, p->next);
        }
        else
        {
            p = new LN{val, p};
            return;
        }
    }
    int Head() { return r->val; }
    void Pop() {
        auto root = r;
        r = r->next;
        delete root;
        _s--;
        return;
    }
    bool Empty(){
        return nullptr == r;
    }
    void Clear()
    {
        while(nullptr != r)
        {
            Pop();
        }
    }
    size_t GetS() { return _s; }
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
};
template <class T>
using VV = vector<vector<T>>;

static vector<T_TEST_CONTAINER<int, VV<int>>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, 3, {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}}});
    sg_vec_test_cases.push_back({2, 1, {{1, 2}}});
    sg_vec_test_cases.push_back({3, 0, {{3, 2}, {4, 3}}});
    sg_vec_test_cases.push_back({4, 2, {{ 5, 5 }, {4, 6}, {2, 6}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.scheduleCourse(test_case.input);
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