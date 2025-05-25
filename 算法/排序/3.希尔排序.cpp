/*
 * 希尔排序
 * 基本思想：将序列按增量分组，对每组进行插入排序，逐步缩小增量直至1。
 * 时间复杂度：O(n log n) ~ O(n?)（取决于增量序列）
 * 空间复杂度：O(1)
 * 稳定性：不稳定
 * 适用场景：中等规模数据
 */
#include <iostream>
using namespace std;

/**
 * Shell排序函数
 *  arr 需要排序的数组
 *  n 数组的长度
 */
void shellSort(int arr[], int n)
{
    // 初始化间隔gap，从数组长度的一半开始
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // 从gap开始遍历数组
        for (int i = gap; i < n; i++)
        {
            // 保存当前元素到temp
            int temp = arr[i];
            // 初始化j为当前元素的索引
            int j;
            // 将大于temp的元素移动gap距离，直到找到temp的正确位置
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            // 将temp插入到找到的位置
            arr[j] = temp;
        }
    }
}

// 验证示例
int main()
{
    // 定义一个整型数组
    int arr[] = {23, 12, 45, 67, 89, 34, 56};
    // 计算数组长度
    int n = sizeof(arr) / sizeof(arr[0]);
    // 调用shellSort函数对数组进行排序
    shellSort(arr, n);
    // 遍历排序后的数组并打印
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}