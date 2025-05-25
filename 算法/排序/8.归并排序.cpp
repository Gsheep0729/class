/*
 * 归并排序
 * 基本思想：分治法，将数组递归分成两半，直到子数组长度为1，再合并两个有序子数组。
 * 时间复杂度：O(n log n)（所有情况）
 * 空间复杂度：O(n)（合并时需要临时数组）
 * 稳定性：稳定
 * 适用场景：需要稳定性的中等规模数据
 */
#include <iostream>
using namespace std;

/**
 * @brief 合并两个已排序的子数组为一个有序数组
 * 
 * @param arr 需要排序的数组
 * @param left 左子数组的起始索引
 * @param mid 左子数组的结束索引，mid+1是右子数组的起始索引
 * @param right 右子数组的结束索引
 */
void merge(int arr[], int left, int mid, int right)
{
    // 计算左子数组和右子数组的长度
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组来存储左子数组和右子数组
    int L[n1], R[n2];

    // 将左子数组复制到临时数组L中
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }

    // 将右子数组复制到临时数组R中
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    // 合并两个临时数组到原数组arr中
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    // 如果左子数组还有剩余元素，将其复制到原数组arr中
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    // 如果右子数组还有剩余元素，将其复制到原数组arr中
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

/**
 * @brief 递归地对数组进行归并排序
 * 
 * @param arr 需要排序的数组
 * @param left 数组的起始索引
 * @param right 数组的结束索引
 */
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // 计算中间索引
        int mid = left + (right - left) / 2;

        // 递归地对左子数组进行排序
        mergeSort(arr, left, mid);

        // 递归地对右子数组进行排序
        mergeSort(arr, mid + 1, right);

        // 合并两个已排序的子数组
        merge(arr, left, mid, right);
    }
}

// 验证示例
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}