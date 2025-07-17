/*
 * 基数排序
 * 基本思想：非比较排序，按数字的每一位（从低位到高位）进行分配和收集。
 * 时间复杂度：O(nk)（k为最大位数）
 * 空间复杂度：O(n + k)（依赖基数范围）
 * 稳定性：稳定
 * 适用场景：整数或定长字符串排序
 */
#include <iostream>
using namespace std;

/**
 * @brief 获取数组中的最大值
 * 
 * @param arr 输入的整数数组
 * @param n 数组的长度
 * @return int 数组中的最大值
 */
int getMax(int arr[], int n)
{
    int max_val = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    return max_val;
}

/**
 * @brief 对数组进行计数排序，基于某一位（个位、十位、百位等）进行排序
 * 
 * @param arr 输入的整数数组
 * @param n 数组的长度
 * @param exp 当前排序的位数，例如1表示个位，10表示十位，100表示百位等
 */
void countingSort(int arr[], int n, int exp)
{
    int output[n];
    int count[10] = {0};

    // 统计每个数字在当前位上的出现次数
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }

    // 将计数数组转换为累加数组，表示每个数字在输出数组中的位置
    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    // 根据累加数组将元素放入输出数组的正确位置
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将排序后的结果复制回原数组
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

/**
 * @brief 对数组进行基数排序
 * 
 * @param arr 输入的整数数组
 * @param n 数组的长度
 */
void radixSort(int arr[], int n)
{
    // 获取数组中的最大值，以确定需要排序的位数
    int max_val = getMax(arr, n);

    // 从个位开始，依次对每一位进行计数排序
    for (int exp = 1; max_val / exp > 0; exp *= 10)
    {
        countingSort(arr, n, exp);
    }
}

// 验证示例
int main()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    radixSort(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}