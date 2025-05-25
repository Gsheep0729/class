/*
 * 简单选择排序
 * 基本思想：每次从待排序序列中选择最小（或最大）元素，与序列首元素交换，逐步缩小未排序范围。
 * 时间复杂度：O(n?)（所有情况均需完整比较）
 * 空间复杂度：O(1)（原地排序）
 * 稳定性：不稳定
 * 适用场景：小数据，简单实现
 */
#include <iostream>
using namespace std;

/**
 * 使用选择排序算法对整数数组进行升序排序
 * @param arr 待排序的整型数组指针
 * @param n 数组的长度
 */
void selectionSort(int arr[], int n)
{
    // 外层循环遍历每个待排序位置
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        // 内层循环寻找未排序部分的最小元素索引
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        // 将找到的最小元素交换到当前位置
        swap(arr[i], arr[min_idx]);
    }
}

/**
 * 排序算法验证示例
 * 创建测试数组，执行排序并输出结果
 */
int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    selectionSort(arr, n);
    // 输出排序后的数组元素
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}