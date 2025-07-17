#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int rear = 0; // 慢指针，指向有效数组末尾
        for (int front = 0; front < nums.size(); front++) { // 快指针遍历数组
            if (nums[front] != val) {        // 保留非目标值
                nums[rear++] = nums[front];  // 赋值并移动慢指针
            }
        }
        return rear; // 返回新数组长度
    }
};

int main() {
    vector<int> nums = {3, 2, 2, 3};
    int val = 3;
    int len = Solution().removeElement(nums, val);
    cout << len << endl; // 输出: 2
    for (int i = 0; i < len; i++) cout << nums[i] << " "; // 输出: 2 2
    return 0;
}