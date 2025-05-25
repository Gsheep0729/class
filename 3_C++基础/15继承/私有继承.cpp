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

// 教师类(人类的一个子类)
class Teacher : private Human
{
public:
    Teacher(const string &name, int age, double salary) : Human(name, age), m_salary(salary) {}
    void teach(const string &course)
    {
        cout << "我在教" << course << endl;
    }
    void who(void)
    {
        cout << "我叫" << m_name << ",今年" << m_age << "岁,工资是" << m_salary << endl;
        cout << "身份证号" << getIDnum() << endl;
    }

private:
    double m_salary;
};

int main()
{
    Teacher tea("鹿晗", 19, 2800);
    tea.teach("C++");
    tea.who();

    // 私有继承时，基类公有成员在子类中变为私有，因此不可访问
    // tea.eat("香翅捞饭");

    return 0;
}