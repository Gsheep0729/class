#include <iostream>
using namespace std;

int main()
{
    int a = 1;
    int b = 2;

    // const int *pa = &a;
    int const *pa = &a; // 常量指针
    // *pa = 2; // 不可以通过指针修改变量值
    pa = &b; // right 但可以让指针指向其他变量
    // *pa = 2;
    cout << *pa << endl;

    int *const p_a = &a; // 指针常量
    *p_a = 10;           // 可以通过指针修改变量值
    cout << a << endl;
    // p_a = &b; // error 不可以让指针指向其他变量
    return 0;
}
