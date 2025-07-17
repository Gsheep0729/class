#include <iostream>
using namespace std;

class A
{
public:
    A(int, int);

private:
    int m_private;

protected:
    int m_protected;

    friend void globalFun_friend(const A &that);
};

void globalFun(const A &that);

A::A(int data1 = 0, int data2 = 0) : m_private(data1), m_protected(data2)
{
    cout << "构造函数 " << endl;
    cout << "m_private = " << m_private << ", m_protected = " << m_protected << endl;
}

void globalFun(const A &that)
{
    cout << "全局函数 " << endl;
    // that.m_private;//error
    // that.m_protected;//error
}

void globalFun_friend(const A &that)
{
    cout << "友元函数 " << endl;
    cout << that.m_private << " " << that.m_protected << endl;
}

int main()
{
    A a(1, 2);
    globalFun(a);
    globalFun_friend(a);

    return 0;
}