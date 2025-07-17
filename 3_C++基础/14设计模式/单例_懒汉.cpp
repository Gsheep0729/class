#include <iostream>
using namespace std;

// 单例模式:懒汉式

class Singleton
{
public:
    // 3)通过静态成员函数获取单例对象
    static Singleton &getInstance()
    {
        if (s_instance == NULL)
        {
            // 创建对象
            s_instance = new Singleton(54321);
        }
        // 增加计数
        s_count++;
        // 返回对象
        return *s_instance;
    }

    // 单例可以被多个人同时使用,应该是最后一个使用者负责回收
    void release(void)
    {
        if (s_count > 0)
        {
            // 减少计数
            s_count--;
        }

        if (s_count == 0)
        {
            delete s_instance;
            s_instance = NULL;
        }
    }

    void print(void)
    {
        cout << m_data << endl;
    }

private:
    // 1)私有化构造函数
    Singleton(int data = 0) : m_data(data)
    {
        cout << "创建单例对象" << endl;
    }
    ~Singleton()
    {
        cout << "单例对象被销毁了" << endl;
    }

    Singleton(const Singleton &) = delete;

    // 2)通过静态成员变量维护唯一的对象
    static Singleton *s_instance; // 指针可以指向空
    // 计数,用于记录使用单例对象的人数
    static int s_count;

private:
    int m_data;
};

Singleton *Singleton::s_instance = NULL;
int Singleton::s_count = 0;

int main()
{
    cout << "main开始执行" << endl;

    Singleton &s1 = Singleton::getInstance(); // 1
    Singleton &s2 = Singleton::getInstance(); // 2

    cout << "s1 = " << &s1 << endl;
    cout << "s2 = " << &s2 << endl;

    s2.print();
    s2.release(); // 0
    s1.print();
    s1.release(); // 1

    s1.release();
    cout << "----------" << endl;

    Singleton &s3 = Singleton::getInstance(); // 1
    Singleton &s4 = Singleton::getInstance(); // 2

    cout << "s3 = " << &s3 << endl;
    cout << "s4 = " << &s4 << endl;

    s3.print();
    s3.release(); // 0
    s4.print();
    s4.release(); // 1

    s1.release();

    cout << "main结束了" << endl;

    return 0;
}
