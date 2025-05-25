#include <iostream>
using namespace std;

// int add(int a, int b)
// {
//     return a + b;
// }

template <typename T> // 模板函数声明
T add(T, T b);

template <typename T> // 模板头函数定义
T add(T a, T b)       // T只是一个名字,表示一种类型
{
    // 函数体;
    return a + b; // T类型的对象本身是可以相加的  自定义类型 重载+这个符号
}

template <typename T1, typename T2>
float sum(T1 a, T2 b, float c)
{
    return a + b + c; // T1、T2类型的对象本身是可以相加的，可以是不同类型，也可以是相同类型
}

int main()
{
    // cout << add<int>(1, 2) << endl; // 函数模板<>可以省略
    // cout << add(3, 2) << endl;

    // cout << add(string("abc"), string("def")) << endl;

    // cout << add<string>("abc", "def") << endl;

    // // cout << add(3, 2.1) << endl; // error 必须是相同类型
    // cout << add<int>(3, 2.1) << endl;
    // // cout << add<int>(3, string("abc")) << endl;

    // cout << sum(3, 2.1) << endl; // 5 5.1
    // // cout << sum(3, string("abc")) << endl;

    // cout << sum(3, 2) << endl;

    cout << sum(3, 2, 1.1f) << endl;

    return 0;
}