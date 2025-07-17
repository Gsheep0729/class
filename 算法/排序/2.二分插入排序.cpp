/*
 * 折半插入排序
 * 基本思想：使用二分查找确定插入位置，减少比较次数。
 * 时间复杂度：O(n?)（比较次数减少，移动次数不变）
 * 空间复杂度：O(1)
 * 稳定性：稳定
 * 适用场景：小规模或基本有序数据，减少比较次数
 */
#include <iostream>
using namespace std;

/**
 * 二分插入排序函数
 * 使用二分查找的方法来减少比较的次数，从而提高排序的效率
 * @param arr 需要排序的数组
 * @param n 数组的大小
 */
void binaryInsertionSort(int arr[], int n)
{
    // 从第二个元素开始遍历，因为第一个元素默认为有序
    for (int i = 1; i < n; i++)
    {
        // 当前需要插入的元素
        int key = arr[i];
        // 初始化二分查找的左右边界
        int left = 0;
        int right = i - 1;
        // 使用二分查找确定当前元素应该插入的位置
        while (left <= right)
        {
            // 计算中间位置
            int mid = left + (right - left) / 2;
            // 如果中间位置的元素大于当前元素，则当前元素应该插入到mid的左边
            if (arr[mid] > key)
            {
                right = mid - 1;
            }
            else
            {
                // 否则，当前元素应该插入到mid的右边
                left = mid + 1;
            }
        }
        // 将插入位置之后的元素向后移动一位，为当前元素腾出空间
        for (int j = i; j > left; j--)
        {
            arr[j] = arr[j - 1];
        }
        // 将当前元素插入到正确的位置
        arr[left] = key;
    }
}

// 验证示例
int main()
{
    // 初始化一个数组
    int arr[] = {37, 23, 45, 12, 89, 64};
    // 计算数组的大小
    int n = sizeof(arr) / sizeof(arr[0]);
    // 调用二分插入排序函数对数组进行排序
    binaryInsertionSort(arr, n);
    // 遍历排序后的数组并打印
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}