/*拷贝构造函数
拷贝构造函数是一个特殊的构造函数，用于创建一个新的对象，作为现有对象的副本。它通常用于：

1.对象复制：当对象被传递给函数（通过值传递）或作为返回值从函数返回时，拷贝构造函数会被调用。
2.对象初始化：使用另一个同类型的对象来初始化一个新对象时，也会调用拷贝构造函数。*/
#include <iostream>
using namespace std;

class A
{
public:
    A(int data = 0)//默认构造函数
    {
        cout << "A::A(int)" << endl;
        m_data = data;
    }
    // const:防止误修改 支持常对象
    // &：引用传递 不加&是值传递，形参是实参的备份（形参 = 实参  递归调用拷贝构造函数）
    //不加&：按值传递的拷贝构造函数，在创建对象副本时会陷入无限递归调用
    A(const A &that)//拷贝构造函数
    {
        cout << "A::A(const A&)" << endl;
        // 赋值
        m_data = that.m_data;
    }
    // 函数返回值右值 多调用一次拷贝构造完成（有可能会被优化）
    // 函数返回值加&：如果你返回的不是局部变量，就加&  不能返回局部变量的指针或引用
    A &operator=(const A &that)///拷贝赋值函数
    {
        cout << "拷贝赋值" << endl;
        m_data = that.m_data;
        // i3.operator=(i2)  i3

        return *this;
    }

    int m_data;
};

int main()
{
    A a1(1);     // 构造
    A a2 = A(2); // 构造，等同A a2(2);

    a1 = a2; // 拷贝赋值
    cout << a1.m_data << endl;
    cout << a2.m_data << endl;

    A a3 = a1; // 拷贝构造
    return 0;
}