#include <iostream>
using namespace std;

class Base
{
public:
    Base(void) : m_i(0)
    {
        cout << "Base::Base(void)" << endl;
    }
    int m_i;
};

class Derived : public Base
{
public:
    void foo(void) // 子类foo函数
    {
        cout << "Derived::foo" << endl;
    }
    // void foo(int i) // 子类foo函数
    // {
    //     cout << "Derived::foo" << endl;
    // }
    // // 将基类中的foo函数引入当前子类作用域  可形成有效重载
    // using Base::foo;
};

int main()
{
    Derived d;
    // d.foo();
    d.Base::foo();

    return 0;
}