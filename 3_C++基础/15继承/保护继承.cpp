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
// 明星类(人类的一个子类)
class Star : protected Human
{
public:
    // Human(...)说明从基类中继承来的成员的初始化方式
    Star(const string &name, int age, const string &label) : Human(name, age), m_label(label) {}
    void act(const string &movie)
    {
        cout << "我在演" << movie << endl;
    }
    void who(void)
    {
        cout << "我叫" << m_name << ",今年" << m_age << "岁,标签是" << m_label << endl;
        cout << "身份证号" << getIDnum() << endl;
    }

private:
    string m_label; // 标签
};

int main()
{
    Star star("吴京", 35, "硬汉");
    star.who();
    star.act("战狼3");

    // 基类的公有成员,通过保护继承,成为了派生类自己的保护成员
    // star.eat("香翅捞饭");
    return 0;
}