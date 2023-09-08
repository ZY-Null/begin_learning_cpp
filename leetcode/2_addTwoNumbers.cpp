#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/add-two-numbers/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
vector<int> ConverToVec(ListNode * head)
{
    vector<int> ret{};
    ListNode *cur = head;
    while(nullptr != cur)
    {
        ret.push_back(cur->val);
        cur = cur->next;
    }
    return std::move(ret);
}
ListNode *ConvertToNode(const vector<int> &src)
{
    if(src.empty())
    {
        return nullptr;
    }
    auto nums = src.size();
    ListNode *head = new ListNode(src.front());
    ListNode *cur = head;
    for (auto i = 1; i < nums; i++)
    {
        cur->next = new ListNode(src[i]);
        cur = cur->next;
    }
    return head;
}
void RecruitDelete(ListNode *head)
{
    if(nullptr != head)
    {
        RecruitDelete(head->next);
        delete head;
    }
    return;
}

class Solution
{
public:
    using PLN = ListNode *;
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        PLN n1 = l1, n2 = l2;
        PLN ret = new ListNode(0);
        PLN cur = ret;
        int bit{0};
        while (!((0 == bit) && (nullptr == n1) && (nullptr == n2)))
        {
            int val1{0}, val2{0};
            if (nullptr != n1)
            {
                val1 = n1->val;
                n1 = n1->next;
            }
            if (nullptr != n2)
            {
                val2 = n2->val;
                n2 = n2->next;
            }
            int cur_val = val1 + val2 + bit;
            bit = cur_val / 10;
            cur_val = cur_val % 10;
            cur->next = new ListNode(cur_val);
            cur = cur->next;
        }
        cur = ret;
        ret = ret->next;
        delete cur;
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
    vector<int> l1;
    vector<int> l2;
};
static vector<T_TEST_CONTAINER<vector<int>, T_TestCase>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, {7, 0, 8}, {{2, 4, 3}, {5, 6, 4}}});
    sg_vec_test_cases.push_back({2, {0}, {{0}, {0}}});
    sg_vec_test_cases.push_back({3, {8, 9, 9, 9, 0, 0, 0, 1}, {{9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}}});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ln1 = ConvertToNode(test_case.input.l1);
        auto ln2 = ConvertToNode(test_case.input.l2);
        auto ln3 = s.addTwoNumbers(ln1, ln2);
        auto ret = ConverToVec(ln3);
        RecruitDelete(ln1);
        RecruitDelete(ln2);
        RecruitDelete(ln3);
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