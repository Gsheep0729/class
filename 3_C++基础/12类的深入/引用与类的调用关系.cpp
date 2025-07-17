#include <iostream>
using namespace std;

class A
{
public:
    A(int i) : m_i(i) {}
    void print() const
    {
        cout << "m_i = " << m_i << endl;
    }
    void setValue(int i)
    {
        m_i = i;
    }

private:
    int m_i;
};

int main()
{
    // int a = 1;
    // int &r_a = a;
    // // int &r_a1 = 1;//error//普通引用只能引用变量
    // const int &r_a1 = 1;
    // // r_a1 = 10;//不能通过常引用修改引用的目标

    A a(10);
    A &r_a = a;
    a.setValue(20);
    a.print();
    r_a.setValue(30);
    r_a.print();

    const A ca(10);
    const A &r_ca = ca; // 常引用/常变量只能调用常函数
    // ca.setValue(20);//error
    ca.print();
    // r_ca.setValue(20);
    r_ca.print();

    return 0;
}