#include <bits/stdc++.h>
using namespace std;

/************************************************************************************************/
/*                                                                                              */
/*                                         sulotions                                            */
/*                                                                                              */
/************************************************************************************************/
// site: https://leetcode.cn/problems/binary-trees-with-factors/
class Solution
{
public:
    int numFactoredBinaryTrees(vector<int> &arr)
    {
        // i tried that dynamic schedual thing, but still not understand...
        unordered_map<int, int> nums_cnt;
        std::sort(arr.begin(), arr.end());
        for (const int &i : arr)
        {
            nums_cnt.emplace(i, 1);
        }
        int ret{0};
        for (const int &i : arr)
        {
            int up = static_cast<int>(sqrt(static_cast<double>(i))) + 1;
            for (int x = 2; x < up; x++)
            {
                if (i % x == 0)
                {
                    int y = i / x;
                    if ((nums_cnt.end() != nums_cnt.find(x)) && (nums_cnt.end() != nums_cnt.find(y)))
                    {
                        int is_2_if_not_same = (x != y) ? 2 : 1;
                        nums_cnt[i] += (((((long long int)nums_cnt[x] * (long long int)nums_cnt[y]) % (1000000007)) * is_2_if_not_same) % (1000000007));
                        nums_cnt[i] = nums_cnt[i] % (1000000007);
                    }
                }
            }
            ret += nums_cnt[i];
            ret = ret % (1000000007);
        }
        return ret;
    }
};
/* 
02, 03, 06, 18, 54
01, 01, 03, 
 */

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
static vector<T_TEST_CONTAINER<int, vector<int>>> sg_vec_test_cases;
void InitTestCases()
{
    sg_vec_test_cases.clear();
    sg_vec_test_cases.push_back({1, 3, {2, 4}});
    sg_vec_test_cases.push_back({2, 7, {2, 4, 5, 10}});
    return;
}

int main(int argc, char const *argv[])
{
    Solution s;
    bool all_test_ok{true};
    for (auto &test_case : sg_vec_test_cases)
    {
        int ret = s.numFactoredBinaryTrees(test_case.input);
        if(ret != test_case.expect)
        {
            all_test_ok = false;
            printf("test_case id:%d test failed! expect %d, actually:%d\n", test_case.id, test_case.expect, ret);
        }
    }
    if(all_test_ok)
    {
        printf("all test_case running successfully!\n");
    }
    return 0;
}
