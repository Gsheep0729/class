#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, m, total = 0;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    // 输入并计算总价值
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            total += grid[i][j];
        }
    }

    vector<int> row_sum(n, 0), col_sum(m, 0);
    // 计算每行总和
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) row_sum[i] += grid[i][j];
    // 计算每列总和
    for (int j = 0; j < m; j++) 
        for (int i = 0; i < n; i++) col_sum[j] += grid[i][j];

    int res = INT_MAX, sum = 0;
    // 遍历所有横向切割点
    for (int i = 0; i < n; i++) {
        sum += row_sum[i];
        res = min(res, abs(total - 2 * sum)); // 计算差值并更新最小值
    }

    sum = 0;
    // 遍历所有纵向切割点
    for (int j = 0; j < m; j++) {
        sum += col_sum[j];
        res = min(res, abs(total - 2 * sum));
    }

    cout << res << endl;
    return 0;
}