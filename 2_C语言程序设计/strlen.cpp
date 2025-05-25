/*字符串库中最简单的函数是strlen(求字符串长度)，
它通过寻找标志字符串结束的空字符来计算字符串的长度。
编写一个strlen的实现，它以一个字符数组为参数*/
#include <iostream>
using namespace std;
int strlen(char *str)
{
    int i = 0;//计数器
    while (str[i] != '\0')//循环遍历字符串，直到遇到空字符
    {
        i++;
    }
    return i;
}

int main()
{
    char str[] = "hello world";
    cout << strlen(str) << endl;
    
    
    return 0;
}