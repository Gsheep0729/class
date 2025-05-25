
#include <iostream>
#include <easyx.h>
using namespace std;

class Base
{
public:
    int value;
    Base(int data) : value(data)
    {
        cout << "(含参版本)公共基类Base" << ",size = "
             << sizeof(Base) << endl;
    }
    Base() : value(100)
    {
        cout << "(无参版本)公共基类Base" << ",size = "
             << sizeof(Base) << endl;
    }
};

class Derived1 : virtual public Base
{
public:
    // 类 100
    Derived1(int data) : Base(data)
    {
        cout << "中间Derived1类" << ",size = "
             << sizeof(Derived1) << endl;
    }
    Derived1() /*: Base(data)*/
    {
        cout << "---中间Derived1类" << ",size = "
             << sizeof(Derived1) << endl;
    }

    void fun()
    {
        cout << "11111 " << endl;
    }
};

class Derived2 : virtual public Base
{
public:
    // 类 100
    Derived2(int data) /*: Base(data)*/
    {
        cout << "中间Derived2类" << ",size = "
             << sizeof(Derived2) << endl;
    }
};

class FinalDerived : public Derived1, public Derived2
{
public:
    // FinalDerived通过Derived1和Derived2两个路径继承了Base
    // Derived1 100 =    Derived2 100  加了之后在FinalDerived是唯一的

    FinalDerived(int data) : Derived1(data), Derived2(data), Base(data)
    {
        cout << "汇聚FinalDerived类" << ",size = "
             << sizeof(FinalDerived) << endl;
    }
};

int main()
{
    FinalDerived fd(10); // Base只会被初始化一次，且由FinalDerived的构造函数控制
    // // 由于虚继承，FinalDerived 中只有一个 Base 子对象，因此不会有数据重复
    // // 并且不会有访问 Base 成员时的二义性
    // fd.value = 100;

    // // fd.Derived1::value = 10;
    // // fd.Derived2::value = 20;

    // std::cout << "Value through Derived1: " << fd.Derived1::value << std::endl;
    // std::cout << "Value through Derived2: " << fd.Derived2::value << std::endl;

    // std::cout << &fd.Derived1::value << std::endl;
    // std::cout << &fd.Derived2::value << std::endl;

    // std::cout << sizeof(Base) << std::endl;         // 4  4
    // std::cout << sizeof(Derived1) << std::endl;     // 16 4  int 4  + *p 8
    // std::cout << sizeof(Derived2) << std::endl;     // 16 4
    // std::cout << sizeof(FinalDerived) << std::endl; // 24 8

    // Derived1 d(20);
    // d.fun();

    return 0;
}