#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "构造函数" << endl;
        throw -1; // 会导致程序崩溃
    }
    ~A()
    {
        cout << "析构函数" << endl;
        // throw -1; // 会导致程序崩溃
    }
    void fun() noexcept
    {

        cout << "成员函数" << endl;
        // throw - 1;//会导致程序崩溃
    }
};

int main()
{
    try
    {
        A a;
        a.fun();
    }

    catch (int n)
    {
        cout << "捕获到了异常" << endl;
    };
    cout << "main " << endl;
    return 0;
    return 0;
}