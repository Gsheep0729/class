#include <iostream>
using namespace std;

int main()
{
    int a = 1;
    // 类型 &引用名 = 变量名;
    int &r_a = a; // r_a引用a,r_a就是a的别名

    int b = 2;
    r_a = b; // 不是修改引用绑定的变量 简单复制  a = b
    // &r_a = b; //&r_a表示r_a(a) 的地址  1 = 2  error
    // int &r_a = b;//重复定义  error
    // double &d = a;////引用类型和绑定的目标类型要一致

    cout << "&a = " << &a << ",a = " << a << endl;
    cout << "&r_a = " << &r_a << ",r_a = " << r_a << endl;
    cout << "&b = " << &b << ",b = " << b << endl;

    return 0;
}