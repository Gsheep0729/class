#include <iostream>
using namespace std;

int main()
{
    // int arr[5] = {1, 2, 3, 4, 5};
    // // 基本类型迭代器在定义时有*
    // // iter < std::end(arr)  ok  但是这种就是典型的指针访问容器风格  从前往后访问   从后往前访问（反向迭代器）
    // for (int *iter = std::begin(arr); iter != std::end(arr); iter++)
    // {
    //     cout << *iter << endl;
    // }
    // // 指针访问
    // for (int *p = arr; p < arr + 5; p++)
    // {
    //     cout << *p << endl;
    // }

    string str = "abcdef";
    // 对象类型迭代器在定义时没有*
    // for (string::iterator iter_str = str.begin(); iter_str != str.end(); iter_str++)//ok
    // auto表示让编译器自动推测该变量类型
    // 普通迭代器
    for (auto iter_str = str.begin(); iter_str != str.end(); iter_str++)
    {
        // *iter_str += 1;
        // cout << *iter_str << endl;
        if (*iter_str == 'c')
        {
            iter_str = str.erase(iter_str);
            cout << *iter_str << endl;
            break;
        }
    }

    // // 常迭代器
    // for (string::const_iterator iter_str = str.cbegin(); iter_str != str.cend(); iter_str++)
    // {
    //     // *iter_str += 1;
    //     cout << *iter_str << endl;
    // }

    // // 反向迭代器 迭代器依然是++，保证前后访问风格一致
    // for (string::reverse_iterator iter_str = str.rbegin(); iter_str != str.rend(); iter_str++)
    // {
    //     // *iter_str += 1;
    //     cout << *iter_str << endl;
    // }

    // // 反向常量迭代器 迭代器依然是++，保证前后访问风格一致
    // for (string::const_reverse_iterator iter_str = str.crbegin(); iter_str != str.crend(); iter_str++)
    // {
    //     // *iter_str += 1;
    //     cout << *iter_str << endl;
    // }

    // auto a = 1; // int a = 1;   推测然后设置类型的步骤，一定程度上降低效率
    // cout << sizeof(a) << endl;

    // string str1 = "abcdefg";
    // str1.erase(2);
    // cout << str1 << endl;

    return 0;
}
