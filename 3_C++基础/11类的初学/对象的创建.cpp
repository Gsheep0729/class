#include <iostream>
#include <stdlib.h>
using namespace std;

class Student
{
public:
    Student(const string name, const int age = 0, const int id = 0) // 前面不能加void
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
    // // 在栈区创建单个对象，编译器自动申请内存并结束生命周期
    // Student s("蔡徐坤", 18, 1);         // 可以成功调用到构造函数
    // Student s1 = Student("蔡徐坤", 18); // 可以成功调用到构造函数
    // s.who();
    // s1.who();

    // // 在栈区创建多个对象
    // Student sarr[3] =
    //     {
    //         Student("蔡徐坤", 18, 1),
    //         Student("鹿晗", 19, 2),
    //         Student("范丞丞", 20, 3)};
    // sarr[0].who();
    // sarr[1].who();
    // sarr[2].who();

    // 在堆区创建单个对象，主动申请内存控制生命周期
    Student *ps = new Student("马嘉祺", 21, 4);//自动调用类的构造函数初始化

    // 对象.成员   对象指针->成员
    ps->who();//调用成员函数
    (*ps).who();

    // 在堆区创建对象数组
    Student *psarr = new Student[3]{
        Student("蔡徐坤", 18, 1),
        Student("鹿晗", 19, 2),
        Student("范丞丞", 20, 3)};
    psarr[0].who();
    psarr[1].who();
    psarr[2].who();

    delete[] psarr;
    psarr = NULL;

    // 销毁
    delete ps;

    ps = NULL;
    return 0;
}