#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int num = 1;                      // 填充数字
        int offset = 0;                   // 控制螺旋层数
        while (n - 2 * offset > 1) {      // 当剩余层数大于1时循环
            // 从左到右填充上边
            for (int j = offset; j < n - offset - 1; j++) 
                matrix[offset][j] = num++;
            // 从上到下填充右边
            for (int i = offset; i < n - offset - 1; i++) 
                matrix[i][n - offset - 1] = num++;
            // 从右到左填充下边
            for (int j = n - offset - 1; j > offset; j--) 
                matrix[n - offset - 1][j] = num++;
            // 从下到上填充左边
            for (int i = n - offset - 1; i > offset; i--) 
                matrix[i][offset] = num++;
            offset++; // 进入内层
        }
        if (n % 2 == 1) matrix[offset][offset] = num; // 奇数矩阵中心填充
        return matrix;
    }
};

int main() {
    vector<vector<int>> res = Solution().generateMatrix(3);
    for (auto& row : res) {
        for (int num : row) cout << num << " ";
        cout << endl;
    }
    // 输出:
    // 1 2 3
    // 8 9 4
    // 7 6 5
    return 0;
}