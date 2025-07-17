#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, a, b;
    cin >> n;
    vector<int> vec(n), p(n); // p为前缀和数组
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
        sum += vec[i];
        p[i] = sum;          // 计算前缀和
    }
    while (cin >> a >> b) {  // 循环读取区间
        int res = (a == 0) ? p[b] : p[b] - p[a - 1]; // 利用前缀和计算区间和
        cout << res << endl;
    }
    return 0;
}