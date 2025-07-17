#include <iostream>
using namespace std;

// 定义一个员工类，包含薪水，姓名，工号（基类） 成员变量和成员函数
class Emplyoee
{
public:
    Emplyoee(int no, double salary, string name) : m_no(no), m_salary(salary), m_name(name)
    {
    }
    void who()
    {
        cout << "我叫" << m_name << ",工号是" << m_no << ",薪水是" << m_salary << endl;
    }

private:
    int m_no;
    double m_salary;
    string m_name;
};

class Manage : public Emplyoee
{
public:
    Manage(int no, double salary, string name, string project) : Emplyoee(no, salary, name), m_project(project)
    {
    }
    void print()
    {
        cout << "我在做" << m_project << "项目" << endl;
    }

private:
    string m_project;
};

int main()
{
    Manage man(1, 2800, "蔡徐坤", "偶像练习生");
    man.who();

    man.print();

    return 0;
}