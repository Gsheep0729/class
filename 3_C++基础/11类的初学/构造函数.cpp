#include<iostream> 
using namespace std;
class Student
{
public:
    /*void */Student(const string name, const int age, const int id)//构造函数不能有返回值
    {
        cout << "构造函数" << endl;
        m_name = name;
        m_age = age;
        m_id = id;
    }
    void who(void)
    {
        cout << "我叫" << m_name << ",今年" << m_age
            << "岁,学号是" << m_id << endl;
    }
 private:
    string m_name;
    int m_age;
    int m_id;
};
int main() 
{
    //创建对象,构造函数将自动被调用
    //(...):指明构造函数需要的实参
    Student s("贾修", 18, 1);
    //Student s = Student("贾修", 18, 1);//与上面的写法相同
    s.who();
    //Error 构造函数不能显示调用
    //s.Student("贾修", 18, 1);
    return 0;
 }