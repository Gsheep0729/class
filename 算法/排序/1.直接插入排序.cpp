/*
 * 直接插入排序
 * 基本思想：将待排序元素逐个插入到已排序序列的适当位置，逐步构建有序序列。
 * 时间复杂度：O(n?)（最好情况O(n)，最坏情况O(n?)）
 * 空间复杂度：O(1)（原地排序）
 * 稳定性：稳定
 * 适用场景：小规模或基本有序数据
 */
#include <iostream>
using namespace std;

/**
 * 插入排序函数
 * arr 需要排序的数组
 * n 数组的大小
 */
void insertionSort(int arr[], int n)
{
    // 从第二个元素开始遍历，因为第一个元素默认已排序
    for (int i = 1; i < n; i++)
    {
        // 将当前元素存储为键值
        int key = arr[i];
        // 初始化j为当前元素的前一个位置
        int j = i - 1;
        // 向前移动元素，直到找到键值的正确插入位置
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];//若当前元素大于键值，将当前元素向后移动一位
            j--;// 继续向前移动
        }
        // 将键值插入到正确的位置
        arr[j + 1] = key;
    }
}

// 验证示例
int main()
{
    // 定义一个待排序的数组
    int arr[] = {12, 11, 13, 5, 6};
    // 计算数组大小
    int n = sizeof(arr) / sizeof(arr[0]);
    // 调用插入排序函数对数组进行排序
    insertionSort(arr, n);
    // 遍历并打印排序后的数组
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}