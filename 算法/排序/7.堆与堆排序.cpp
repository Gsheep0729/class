/*
 * 堆排序
 * 基本思想：将无序数组调整为最大堆，逐个提取最大值并调整堆结构。
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(1)
 * 稳定性：不稳定
 * 适用场景：大规模数据，内存敏感场景
 */
#include <iostream>
using namespace std;

/**
 * @brief 维护堆的性质，确保以i为根的子树是一个最大堆。
 * 
 * @param arr 待维护的数组
 * @param n 数组的大小
 * @param i 当前子树的根节点索引
 */
void heapify(int arr[], int n, int i)
{
    int largest = i; // 初始化最大值为当前节点
    int left = 2 * i + 1; // 左子节点索引
    int right = 2 * i + 2; // 右子节点索引

    // 如果左子节点存在且大于当前最大值，则更新最大值
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    // 如果右子节点存在且大于当前最大值，则更新最大值
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    // 如果最大值不是当前节点，则交换并递归调整
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/**
 * @brief 使用堆排序算法对数组进行排序。
 * 
 * @param arr 待排序的数组
 * @param n 数组的大小
 */
void heapSort(int arr[], int n)
{
    // 建堆（从最后一个非叶子节点开始调整）
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // 逐个提取最大值
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]); // 将当前最大值移到数组末尾
        heapify(arr, i, 0); // 调整剩余部分为最大堆
    }
}

/**
 * @brief 验证堆排序算法的示例。
 * 
 * @return int 程序退出状态码
 */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}