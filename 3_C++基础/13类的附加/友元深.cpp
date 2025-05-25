#include <iostream>
#include <cstring>

using namespace std;

class A
{
public:
    A(int, int);
    friend void globalFun_friend(const A &that); // 全局
    void memberFun();

private:
    int m_private;

protected:
    int m_protected;
};

void globalFun(const A &that);

void A::memberFun()
{
    cout << "成员函数 " << endl;
    cout << "m_private = " << m_private << ", m_protected = " << m_protected << endl;
}
A::A(int data1 = 0, int data2 = 0) : m_private(data1), m_protected(data2)
{
    cout << "构造函数 " << endl;
    cout << "m_private = " << m_private << ", m_protected = " << m_protected << endl;
}

void globalFun_friend(const A &that) //  全局 不能加A::
{
    cout << "友元函数 " << endl;
    cout << "m_private = " << that.m_private << ", m_protected = " << that.m_protected << endl;
}

void globalFun(const A &that) // 非友元函数，私有成员不对其开放
{
    cout << "全局函数 " << endl;
    // cout << "m_private = " << that.m_private << ", m_protected = " << that.m_protected << endl;
}

int main()
{
    A a(1, 2);
    cout << endl;
    a.memberFun(); // 成员函数调用
    cout << endl;

    globalFun_friend(a); // 友元函数调用
    cout << endl;
    globalFun(a); // 普通全局函数

    return 0;
}
