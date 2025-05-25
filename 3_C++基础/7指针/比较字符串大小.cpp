/*用字符数组方式的mystrcmp函数( MyStrcmp函数按照 ASCII 表的
顺序逐个比较两个字符串中的字符，直到出现不同的字符或者遇到字符串结束符 '\0')
思路：将字符串首元素进行比较，若相同则依次比较*/
#include <iostream>
#include <cstring>
using namespace std;
int fuck(const char *a, const char *b)
{
    /*用一个while判断相等字符，找不同的字符的位置
    插入：for 已知条件范围循环，while则根据条件结果循环，只要满足条件都循环*/
    while(*a == *b && *a != '\0' && *b != '\0')
    {
        a++;
        b++;
    }
    /*while找到不同后运行if语句*/
    if(*a>*b)
    {
        return 1;
    }
    else if(*a<*b)
    {
        return -1;
    }
    else
    {
        return 0;
    }

}

int main()
{
    /*记得定义字符串“数组”的大小*/
    char a[] = "gy";
    char b[] = "gy";
    /*调用fuck函数比较大小*/
    int (* p)(const char *a, const char *b) = NULL;
    /*定义了一个指针变量，初始化，再将给指针赋值
    函数指针形式调用：将函数名字替换为指针*/
    p = fuck;
    cout << p(a,b);/*调用指针变量*/

    return 0;
}
/* a>b=1;a<b=-1;a=b->0*/