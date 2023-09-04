#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site:https://leetcode.cn/problems/serialize-and-deserialize-bst/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
    using TN = TreeNode;
    string serialize(TreeNode *root)
    {
        return VecToStr(PreOrder(root));
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        vector<int> vec;
        StrToVec(data, vec);
        return RevPreOrder(vec);
    }
    TN *RevPreOrder(const vector<int> &PreOrder)
    {
        return _RevPreOrder(PreOrder);
    }

    vector<int> PreOrder(TN *r)
    {
        vector<int> pre_order;
        _PreOrder(r, pre_order);
        return pre_order;
    }
private:
    void PreOrder(TN *r, vector<int> &pre_order)
    {
        pre_order.clear();
        _PreOrder(r, pre_order);
        return;
    }
    string VecToStr(const vector<int> &vec)
    {
        // val range:[0,10000] = [0, 0x2710]
        string ret;
        stringstream ss;
        for(const int &val : vec)
        {
            ss << setw(4) << setfill('0') << setbase(16) << val;
        }
        ret = ss.str();
        ss.str("");
        return ret;
    }
    void StrToVec(const string &str, vector<int> &vec)
    {
        auto size = str.size();
        assert(0 == size % 4);
        auto num = size / 4;
        vec.clear();
        vec.reserve(num);
        for (int i = 0; i < num; i++)
        {
            vec.push_back(stoi(str.substr(i * 4, 4), 0, 16));
        }
        return;
    }

private:
    void _PreOrder(TN *p, vector<int> &container)
    {
        if(nullptr == p)
        {
            return;
        }
        container.push_back(p->val);
        _PreOrder(p->left, container);
        _PreOrder(p->right, container);
        return;
    }

    TN *_RevPreOrder(const vector<int> &container)
    {
        TN *ret = nullptr;
        if(container.empty()){
            return ret;
        }
        ret = new TN(container[0]);
        vector<int> l{}, r{};
        for(const int &val:container)
        {
            if(val > container[0])
            {
                r.push_back(val);
            }
            else if(val < container[0])
            {
                l.push_back(val);
            }
        }
        ret->left = _RevPreOrder(l);
        ret->right = _RevPreOrder(r);
        return ret;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;

/************************************************************************************************/
/*                                                                                              */
/*                                         Test_Cases                                           */
/*                                                                                              */
/************************************************************************************************/
template <class T_OUT, class T_INT>
struct T_TEST_CONTAINER
{
    int id;
    T_INT input;
};
// define your test case type here:
struct T_TestExpect
{
};
struct T_TestCase
{
};
static vector<T_TEST_CONTAINER<vector<int>, vector<int>>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    // add your test case below!
    sg_vec_test_cases.push_back({1, {2, 1, 3}});
    sg_vec_test_cases.push_back({2, { }});
    return;
}
using TN = TreeNode;
TN *_construct(const vector<int> &input, const int &cur)
{
    TN *ret = nullptr;
    if(cur < input.size())
    {
        if(-1 != input[cur])
        {
            ret = new TN(input[cur]);
            int l_id = ((cur + 1) * 2) - 1;
            int r_id = ((cur + 1) * 2);
            ret->left = _construct(input, l_id);
            ret->right = _construct(input, r_id);
        }
    }
    return ret;
}
void TestFunc()
{
    vector<int> input{41, 37, 44, 24, 39, 42, 48, 1, 35, 38, 40, -1, 43, 46, 49, 0, 2, 30, 36, -1, -1, -1, -1, -1, -1, 45, 47, -1, -1, -1, -1, -1, 4, 29, 32, -1, -1, -1, -1, -1, -1, 3, 9, 26, -1, 31, 34, -1, -1, 7, 11, 25, 27, -1, -1, 33, -1, 6, 8, 10, 16, -1, -1, -1, 28, -1, -1, 5, -1, -1, -1, -1, -1, 15, 19, -1, -1, -1, -1, 12, -1, 18, 20, -1, 13, 17, -1, -1, 22, -1, 14, -1, -1, 21, 23};
    TN *r = _construct(input, 0);
    Codec c;
    string s = c.serialize(r);
    TN *r_new = c.deserialize(s);
    int i = 0;
    i++;
}

int main(int argc, char const *argv[])
{
    InitTestCases();
    Codec coder, decoder;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        auto ret = decoder.PreOrder(decoder.deserialize(coder.serialize(coder.RevPreOrder(test_case.input))));
        if (ret != test_case.input)
        {
            all_test_ok = false;
            printf("test_case id:%d test failed! expect %d, actually:%d\n", test_case.id, test_case.input, ret);
        }
    }
    if (all_test_ok)
    {
        printf("all test_case running successfully!\n");
    }
    TestFunc();
    return 0;
}