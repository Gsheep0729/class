#include <iostream>
using namespace std;

class A
{
public:
    A(int data = 0)
    {
        cout << "A::A(int)" << endl;
        m_data = data;
    }
    // const:防止误修改 支持常对象
    // &：引用传递 不加&是值传递，形参是实参的备份（形参 = 实参  递归调用拷贝构造函数）
    A(const A &that)
    {
        cout << "A::A(const A&)" << endl;
        // 赋值
        m_data = that.m_data;
    }

    int m_data;
};

class B
{
public:
    int m_i; // 基本类型的成员变量//对于基本类型的成员变量,直接复制
    A m_a;   // 类类型的成员变量(成员子对象)//对于类类型成员变量(成员子对象),会调用相应类的拷贝构造函数来初始化
};

int main()
{
    B b1;
    b1.m_i = 123;
    b1.m_a.m_data = 1234;

    B b2(b1);                                       // 调用B的拷贝构造
    cout << b1.m_i << "," << b1.m_a.m_data << endl; // 123,1234
    cout << b2.m_i << "," << b2.m_a.m_data << endl; // 123,1234
    return 0;
}