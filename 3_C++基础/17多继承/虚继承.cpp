
#include <iostream>
using namespace std;

class Base
{
public:
    int value;
};

class Derived1 : virtual public Base
{
    // 类 100
};

class Derived2 : virtual public Base
{
    // 类 100
};

class FinalDerived : public Derived1, public Derived2
{
    // FinalDerived通过Derived1和Derived2两个路径继承了Base
    // Derived1 100 =    Derived2 100  加了之后在FinalDerived是唯一的
};

int main()
{
    FinalDerived fd;
    // 由于虚继承，FinalDerived 中只有一个 Base 子对象，因此不会有数据重复
    // 并且不会有访问 Base 成员时的二义性
    fd.value = 100;

    // fd.Derived1::value = 10;
    // fd.Derived2::value = 20;

    std::cout << "Value through Derived1: " << fd.Derived1::value << std::endl;
    std::cout << "Value through Derived2: " << fd.Derived2::value << std::endl;

    std::cout << &fd.Derived1::value << std::endl;
    std::cout << &fd.Derived2::value << std::endl;

    return 0;
}