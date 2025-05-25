#include <iostream>
using namespace std;

// 单例模式:饿汉式
class Singleton
{
public:
    // 3)通过静态成员函数获取单例对象
    // 如果不返回引用，则会有临时变量的产生，调用拷贝构造函数，而拷贝构造函数又被禁用了
    static Singleton &getInstance()
    {
        return s_instance;
    }

    void print(void)
    {
        cout << m_data << endl;
    }

private:
    // 1. 构造函数私有化  删除拷贝构造函数
    Singleton(int data = 0) : m_data(data)
    {
        cout << "创建单例对象" << endl;
    }

    // = delete表示删除该函数
    Singleton(const Singleton &) = delete;

    // 2)通过静态成员变量维护唯一的对象
    static Singleton s_instance; // 不属于类，类不用分配内存  对象不是在这里创建的，这里只是声明

private:
    int m_data;
};

// 1.Singleton该变量的类型  2.Singleton表示s_instance时类里面的成员
Singleton Singleton::s_instance(12345); // 对象在这里创建

// class A
// {
//     string str;
//     // A a;//error     为什么不可以？ 因为类型没有定义完整，没办法分配内存
// };

int main()
{
    cout << "main开始执行" << endl;

    // 如果不定义为引用，则会调用构造函数生成新对象，但是构造函数被私有化了。
    Singleton &s1 = Singleton::getInstance(); // 拷贝构造
    Singleton &s2 = Singleton::getInstance(); // 拷贝构造

    cout << "&s1 = " << &s1 << endl;
    cout << "&s2 = " << &s2 << endl;

    s1.print();
    s2.print();

    return 0;
}
