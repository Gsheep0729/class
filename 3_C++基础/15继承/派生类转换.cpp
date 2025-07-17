#include <iostream>
using namespace std;

class Base
{
public:
    Base(string str = "") : m_str(str)
    {
    }

    string getStr()
    {
        return m_str;
    }

private:
    string m_str;
};

class Derived : public Base
{
public:
    Derived(string str = "abc") : Base(str)
    {
    }

    void fun()
    {
    }
};

int main()
{
    // 派生类对象
    Derived d;
    cout << d.getStr() << endl;

    // 基类的引用可以绑定到派生类对象
    Base &r_b = d;

    // // 向下造型 error
    // Base b2;
    // Derived &r_d = b2;

    // 基类的指针可以指向派生类对象
    Base *p_b = &d;
    // 可以使用派生类对象初始化基类对象
    Base b(d);

    // 可以使用派生类对象给基类对象赋值
    Base b1;
    b1 = d;

    // 虽然绑定到了子类的对象，但是本质上还是基类类型
    //  r_b.fun();

    return 0;
}