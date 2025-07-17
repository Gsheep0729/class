#include <iostream>
#include "test.h"
using namespace  std;
 void Student::setName(const std::string name)
 {
    m_name = name;
 }
 void Student::setAge(const int age)
 {
    m_age = age;
 }
 void Student::who()
 {
    std::cout << "m_name = " << m_name << ", m_age = " << m_age << std::endl;
 }