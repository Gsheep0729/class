#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0, min_len = INT_MAX, sum = 0; // 滑动窗口法
        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];           // 扩展右边界
            while (sum >= target) {       // 满足条件时收缩左边界
                min_len = min(min_len, right - left + 1); // 更新最小长度
                sum -= nums[left++];      // 左指针右移并更新窗口和
            }
        }
        return min_len == INT_MAX ? 0 : min_len; // 处理无解情况
    }
};

int main() {
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;
    cout << Solution().minSubArrayLen(target, nums) << endl; // 输出: 2
    return 0;
}