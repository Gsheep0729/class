#include <iostream>
using namespace std;

class A
{
public:
    A(double height = 0, int age = 0, const string &name = "") : m_height(height), m_p_age(new int(age)), m_name(name)
    {
        cout << "构造" << endl;
    }
    ~A()
    {
        cout << "析构" << endl;
        delete m_p_age;
    }
    // A(const A&that) //浅拷贝
    //{
    //     cout << "拷贝构造" << endl;
    //     m_height = that.m_height;
    //     m_p_age = that.m_p_age;
    //     m_name = that.m_name;
    // }
    // A&operator = (const A& that)//浅拷贝
    //{
    //     cout << "拷贝赋值" << endl;
    //     m_height = that.m_height;
    //     m_p_age = that.m_p_age;
    //     m_name = that.m_name;

    //    return *this;
    //}

    A(const A &that) // 深拷贝
    {
        cout << "拷贝构造" << endl;
        m_height = that.m_height;
        // m_p_age = that.m_p_age;
        m_p_age = new int(*that.m_p_age);
        m_name = that.m_name;
    }
    A &operator=(const A &that) // 深拷贝
    {
        cout << "拷贝赋值" << endl;
        if (&that != this)
        {
            m_height = that.m_height;
            // m_p_age = that.m_p_age;
            // 释放旧资源（如果不释放旧资源，则之前申请的空间没有释放，会内存泄露）
            delete m_p_age;
            m_p_age = new int(*that.m_p_age);
            // 分配新资源
            m_name = that.m_name;
        }

        return *this;
    }

    void print()
    {
        cout << "m_height = " << m_height << ", *m_p_age = " << *m_p_age << ", m_name = " << m_name << endl;
    }

private:
    double m_height;
    int *m_p_age;
    string m_name;
};

int main()
{
    A a1(180.1, 18, "蔡徐坤");
    a1.print();

    // A a2(a1);
    A a2 = a1;
    a2.print();

    A a3(180.1, 18, "鸡哥");
    a3.print();

    a3 = a1;
    a3 = a3;

    return 0;
}