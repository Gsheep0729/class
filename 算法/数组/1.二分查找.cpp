#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1; // 初始化左右指针
        while (left <= right) {                // 闭区间搜索
            int mid = left + (right - left) / 2; // 防溢出计算中点
            if (nums[mid] > target) {          // 目标在左半区
                right = mid - 1;                // 右指针左移
            } else if (nums[mid] < target) {   // 目标在右半区
                left = mid + 1;                 // 左指针右移
            } else {
                return mid;                     // 找到目标返回下标
            }
        }
        return -1; // 未找到返回-1
    }
};

int main() {
    vector<int> nums = {-1, 0, 3, 5, 9, 12};
    int target = 9;
    cout << Solution().search(nums, target) << endl; // 输出: 4
    return 0;
}