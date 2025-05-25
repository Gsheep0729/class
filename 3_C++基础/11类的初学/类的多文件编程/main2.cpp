#include <iostream>
#include "test.h"
using namespace  std;
/*inline void Student::who()
 {
    std::cout << "m_name = " << m_name << ", m_age = " << m_age << std::endl;
 }*/
 int main()
 {
    Student s;
    s.setName("abc");
    s.setAge(18);
    s.who();
    return 0;
 }