#include <iostream>
#include <cstring>
int main()
{
    char b []= "520CXY";
    std::cout << strlen(b) <<std::endl;
    //字符数组方式， strlen(字符串) 函数，不包括 '\0' ，返回值就是字符串长度
    std::string a = "520CXY";
    //string方式，字符串.length() 或者字符串.size() ，不包括'\0'
    std::cout << a.length() << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << a[0] << std::endl;
    std::cout << a[1] << std::endl;
    std::cout << a[6] << std::endl;
    std::cout << a[7] << std::endl;//越界,为空格
    
 return 0;
}