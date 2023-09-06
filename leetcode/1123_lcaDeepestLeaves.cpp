#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
TreeNode *_construct(const vector<int> &input, const int &cur = 0)
{
    TreeNode *ret = nullptr;
    if (cur < input.size())
    {
        if (-1 != input[cur])
        {
            ret = new TreeNode(input[cur]);
            int l_id = ((cur + 1) * 2) - 1;
            int r_id = ((cur + 1) * 2);
            ret->left = _construct(input, l_id);
            ret->right = _construct(input, r_id);
        }
    }
    return ret;
}

using PT = TreeNode *;
struct TCmp
{
    PT t;
    TCmp() = delete;
    TCmp(const TCmp &o) = delete;
    TCmp(const PT &p) : t{p} {}
};
bool operator==(const TCmp &t1, const TCmp &t2)
{
    const PT &p1 = t1.t;
    const PT &p2 = t2.t;
    bool b1 = (nullptr == p1);
    bool b2 = (nullptr == p2);
    if (b1 != b2)
    {
        return false;
    }
    if(b1)
    {
        return true;
    }
    if (p1->val != p2->val)
    {
        return false;
    }
    return (TCmp(p1->left) == TCmp(p2->left)) && (TCmp(p1->right) == TCmp(p2->right));
}
bool operator!=(const TCmp &t1, const TCmp &t2)
{
    return (!(t1 == t2));
}

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site: https://leetcode.cn/problems/lowest-common-ancestor-of-deepest-leaves
// site2:https://leetcode-cn.com/problems/smallest-subtree-with-all-the-deepest-nodes/
class Solution
{
public:
    using T = TreeNode;
    using TP = TreeNode *;
    struct T_CACHE
    {
        int deep;
        vector<TreeNode *> nodes;
    };
    int max_depth = 0;
    void _get_roads(TreeNode *p, vector<TreeNode *> &cur_road, const int &depth, vector<T_CACHE> &out)
    {
        if(p == nullptr)
        {
            return;
        }
        cur_road.push_back(p);
        if (nullptr == p->left && nullptr == p->right)
        {
            if(depth > max_depth)
            {
                max_depth = depth;
                out.clear();
            }
            if(depth == max_depth)
            {
                out.push_back(T_CACHE{depth, cur_road});
            }
        }
        else
        {
            _get_roads(p->left, cur_road, depth + 1, out);
            _get_roads(p->right, cur_road, depth + 1, out);
        }
        cur_road.pop_back();
        return;
    }
    vector<T_CACHE> GetLeafsRoads(TreeNode *r)
    {
        max_depth = 0;
        vector<T_CACHE>
            ret;
        vector<TreeNode *> ps;
        _get_roads(r, ps, 0, ret);
        return std::move(ret);
    }
    TreeNode *lcaDeepestLeaves(TreeNode *root)
    {
        vector<T_CACHE> roads = GetLeafsRoads(root);
        if(0 == roads.size())
        {
            return nullptr;
        }
        if (1 == roads.size())
        {
            return roads[0].nodes.back();
        }
        bool is_all_same = true;
        int size = roads[0].deep + 1;
        TreeNode *ret = nullptr;
        for (int i = 0; i < size; i++)
        {
            TreeNode *cur = roads[0].nodes[i];
            bool is_all_same = true;
            for(const auto &road:roads)
            {
                if (cur != road.nodes[i])
                {
                    is_all_same = false;
                }
            }
            if(!is_all_same)
            {
                break;
            }
            ret = cur;
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
};

constexpr int null{-1};

static vector<T_TEST_CONTAINER<TreeNode *, TreeNode *>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, _construct(vector<int>{2, 7, 4}), _construct(vector<int>{3, 5, 1, 6, 2, 0, 8, null, null, 7, 4})});
    sg_vec_test_cases.push_back({2, _construct(vector<int>{1}), _construct(vector<int>{1})});
    sg_vec_test_cases.push_back({2, _construct(vector<int>{2}), _construct(vector<int>{0, 1, 3, null, 2})});
    return;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = s.lcaDeepestLeaves(test_case.input);
        if (TCmp(ret) != TCmp(test_case.expect))
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