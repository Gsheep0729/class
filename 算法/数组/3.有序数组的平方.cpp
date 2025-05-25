#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int k = nums.size() - 1;            // 结果数组填充指针
        vector<int> res(nums.size(), 0);    // 初始化结果数组
        for (int i = 0, j = nums.size() - 1; i <= j;) { // 双指针从两端向中间移动
            if (nums[i] * nums[i] < nums[j] * nums[j]) { 
                res[k--] = nums[j] * nums[j]; // 取右指针值平方，填充到末尾
                j--;                         // 右指针左移
            } else {
                res[k--] = nums[i] * nums[i]; // 取左指针值平方，填充到末尾
                i++;                         // 左指针右移
            }
        }
        return res;
    }
};

int main() {
    vector<int> nums = {-4, -1, 0, 3, 10};
    vector<int> res = Solution().sortedSquares(nums);
    for (int num : res) cout << num << " "; // 输出: 0 1 9 16 100
    return 0;
}