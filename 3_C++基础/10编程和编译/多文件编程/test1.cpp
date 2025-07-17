/*配对头文件时必要头文件,如果源文件里使用了某个头文件里声明的函数，则这个头文件也是必要头文件*/
#include"test1.h"
#include<iostream>
void print()
{
std::cout << "test1.cpp中的print函数" << std::endl;
}
int test1(int a, int b)
{
return a + b;
}
void setValue()
{
std::cout << "&num = " << &num << "---by setValue" << std::endl;
std::cout << "请输入一个数字：";
std::cin >> num;
}

