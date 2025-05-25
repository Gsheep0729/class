#include <iostream>
using namespace std;

class Base
{
public:
    virtual int cal(int x, int y)
    {
        return x + y;
    }
    void func()
    {
        // 指向子类对象的基类指针去调用该函数
        // this指向子类对象d
        // this类型：父类类型
        cout << this->Base::cal(1, 2) << endl;
    }
};
class Derived : public Base
{
public:
    int cal(int x, int y)
    {
        return x * y;
    }
};

int main()
{
    Derived d;
    d.func(); // 不加virtual3   1 + 2  加了virtual 2

    return 0;
}