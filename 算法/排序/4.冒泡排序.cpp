/*
 * 冒泡排序
 * 基本思想：重复交换相邻逆序元素，将最大元素“冒泡”到末尾。
 * 优化：若某次遍历无交换，提前终止。
 * 时间复杂度：O(n?)（最好情况O(n)）
 * 空间复杂度：O(1)
 * 稳定性：稳定
 * 适用场景：小数据，简单实现
 */
#include <iostream> // 引入标准输入输出流库
using namespace std; // 使用标准命名空间

// 定义分区函数，用于将数组分为两部分：小于基准值的部分和大于等于基准值的部分
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // 选择最后一个元素作为基准值
    int i = low - 1;       // 初始化i为low-1，用于标记小于基准值的区域
    for (int j = low; j < high; j++) // 遍历数组中的每个元素（除了基准值）
    {
        if (arr[j] < pivot) // 如果当前元素小于基准值
        {
            i++;                      // 将i向前移动一位
            swap(arr[i], arr[j]);     // 交换arr[i]和arr[j]，确保小于基准值的元素在左侧
        }
    }
    swap(arr[i + 1], arr[high]); // 将基准值放到正确的位置（分区点）
    return i + 1;                // 返回基准值的索引
}

// 定义快速排序函数，递归地对数组进行排序
void quickSort(int arr[], int low, int high)
{
    if (low < high) // 如果low小于high，则继续递归
    {
        int pi = partition(arr, low, high); // 调用partition函数获取分区点
        quickSort(arr, low, pi - 1);        // 对左半部分递归排序
        quickSort(arr, pi + 1, high);      // 对右半部分递归排序
    }
}

// 验证示例
int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5}; // 定义待排序数组
    int n = sizeof(arr) / sizeof(arr[0]); // 计算数组长度
    quickSort(arr, 0, n - 1);             // 调用快速排序函数对数组进行排序
    for (int i = 0; i < n; i++)          // 遍历排序后的数组并输出
    {
        cout << arr[i] << " "; // 输出每个元素
    }
    return 0; // 程序正常结束
}