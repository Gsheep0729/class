#include <iostream>
using namespace std;

class Human
{
public:
    Human(const string &name, int age) : m_name(name), m_age(age), m_IDnum(1234)
    {
        cout << "基类构造函数" << endl;
    }

    void eat(const string &food)
    {
        cout << "我在吃" << food << endl;
    }
    void sleep(int time)
    {
        cout << "我睡了" << time << "个小时" << endl;
    }

public:
    // 名字
    string m_name;

protected:
    // 年龄
    int m_age;

    // 但是可以提供保护的接口函数来间接访问
    int getIDnum()
    {
        return m_IDnum;
    }

private:
    // ID
    int m_IDnum;
};

// 学生类(人类的一个子类 公有继承)
class Student : public Human
{
public:
    // Human(...)说明从基类中继承来的成员的初始化方式
    Student(const string &name, int age, int no) : Human(name, age), m_no(no)
    {
        cout << "子类构造函数" << endl;
    }
    void learn(const string &course)
    {
        cout << "我在学" << course << endl;
    }

    void who(void)
    {
        // 父类私有成员在子类不可访问
        cout << "我叫" << m_name << ",今年" << m_age /*<< m_IDnum*/ << "岁,学号是" << m_no << endl;
        cout << "身份证号" << getIDnum() << endl;
    }

private:
    int m_no;
};

int main()
{
    cout << sizeof(Human) << endl;   // 8
    cout << sizeof(Student) << endl; // 12

    Student stu("蔡徐坤", 18, 001);
    stu.who();

    stu.eat("香翅捞饭");
    stu.sleep(8);
    stu.learn("C++");

    // 保护成员,通过公有继承,成为派生类自己的保护成员.类内可访问 ，类外无法访问
    // stu.m_age;
    // stu.getIDnum();
    // stu.m_IDnum;

    return 0;
}