#include <iostream>
#include <array>

using namespace std;

int main()
{
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::array<int, 5> arr2(arr1);

    // 元素访问
    arr2[1] = 100;
    cout << arr2[1] << endl;
    cout << arr2.at(1) << endl; // 检查越界
    cout << arr2.back() << endl;
    cout << arr2.front() << endl;

    // 大小查询
    cout << arr2.size() << endl;

    // 迭代器
    for (std::array<int, 5>::iterator it = arr1.begin(); it != arr1.end(); it++)
    {
        // 使用迭代器it访问元素
        cout << *it << " ";
    }
    cout << endl;

    cout << (arr1 == arr2) << endl;
    return 0;
}