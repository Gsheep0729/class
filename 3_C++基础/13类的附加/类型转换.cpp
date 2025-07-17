#include <iostream>
using namespace std;

int main()
{
    char c = 'a';
    int a = 0;
    // 目标类型变量 = static_cast<目标类型>(源类型变量);
    // a = (int)c; // 等价
    a = static_cast<int>(c); // 静态
    cout << "a = " << a << endl;

    const int *p_a = &a;
    // *p_a = 10;//error 常量指针指向的值不能修改

    int *p_b = const_cast<int *>(p_a); // 常
    *p_b = 10;
    cout << "a = " << a << endl; // 10

    ////在指针和整形数之间进行转换
    // 请注意，这种用法很危险，如果你知道自己要做什么可以小心使用，如果不知道请不要随便使用。考虑使用static_cast
    int *p = reinterpret_cast<int *>(a); // 重解释
    cout << "p = " << p << endl;

    return 0;
}