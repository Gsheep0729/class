/*析构函数用于：

1.释放资源：如果对象在生命周期中分配了动态内存、文件句柄、网络连接等资源，析构函数应该负责释放这些资源，以避免资源泄漏。
2.执行清理操作：除了释放资源，析构函数还可以执行任何必要的清理操作，比如关闭文件、解除锁定等。*/
#include <iostream>
#include <stdlib.h>
using namespace std;

class A
{
public:
    A(const int data)
    {
        cout << "A的构造函数" << endl;
        // 为指针申请空间
        m_data = new int(data);
    }

    ~A()
    {
        cout << "A的析构函数" << endl;
        delete m_data;
        m_data = NULL;
    }

private:
    int *m_data;
};

int main()
{
    // A a(10);

    // 堆区对象 new调用构造
    A *a = new A(10);

    // delete调用析构
    delete a;
    a = NULL;

    return 0;
}