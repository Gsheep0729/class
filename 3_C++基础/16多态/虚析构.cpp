#include <iostream>
using namespace std;

class Base
{
public:
    Base(void) : m_i(0)
    {
        cout << "Base::Base(void)" << endl;
    }
    virtual ~Base()
    {
        cout << "Base::~Base()" << endl;
    }
    int m_i;
};

class Derived : public Base
{
public:
    Derived(void)
    {
        cout << "Derived::Derived(void)" << endl;
        // 动态分配资源
        m_dynamicArray = new int[10];
    }
    ~Derived()
    {
        cout << "Derived::~Derived()" << endl;
        // 释放动态分配的资源
        delete[] m_dynamicArray;
    }
    int *m_dynamicArray; // 动态分配的整数数组
    int m_i1;
};

int main()
{
    Base *pb = new Derived; // 分配Derived对象

    delete pb; // 通过基类指针释放对象，但由于Derived的析构函数没有释放资源，发生内存泄露
    // 虚析构 调用子类析构

    return 0;
}