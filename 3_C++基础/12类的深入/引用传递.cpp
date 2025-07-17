#include <iostream>
using namespace std;

// 地址传递
void swap1(int *a, int *b)
{
    int tmp = 1;
    int *p_tmp = &tmp;
    *p_tmp = *a;
    *a = *b;
    *b = *p_tmp;
}

// 引用传递
void swap2(int &a, int &b)
{
    int tmp = 1;
    tmp = a;
    a = b;
    b = tmp;
}

// 值传递
void swap3(int a, int b)
{
    int tmp = 1;
    tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    int a = 3, b = 5;
    cout << "a =" << a << ", b = " << b << endl;
    swap2(a, b);
    cout << "a =" << a << ", b = " << b << endl;

    return 0;
}