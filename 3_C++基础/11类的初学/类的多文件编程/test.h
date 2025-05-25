/*在写类的时候,一般一个标准的类都分为两个文件(.h/.cpp)  
在头文件中声明类型和函数*/
#ifndef TEST_H
#define TEST_H
 #include<iostream>
 class Student
 {
 public:
    void setName(const std::string name);
    void setAge(const int age);
    void who();
 private:
    std::string m_name;
    int m_age;
 };
#endif