/*写一个strcmp函数（求字符串的比较）的实现，
使其不调用其他函数，直接使用参数的基本表示。
作为附加练习，以两种方式实现该函数，
一种方式是只使用数组操作，另一种方式是只使用指针操作*/
#include <iostream>
using namespace std;
//   如果返回值小于0，则表示s1小于s2
//   如果返回值等于0，则表示s1等于s2
//   如果返回值大于0，则表示s1大于s2
int strcmp1(char *s1, char *s2)//指针操作
{
    while (*s1 == *s2)// 遍历两个字符串，直到找到不同的字符或到达字符串的末尾
    {
        if (*s1 == '\0')// 如果当前字符是字符串的末尾，则两个字符串相等，返回0
            return 0;
        // 移动指针到下一个字符
        s1++;
        s2++;
    }
    return *s1 - *s2;// 返回两个字符串中当前字符的差值，表示它们的字典顺序
}
int strcmp2(char s1[],char s2[])//数组操作
{
    int i = 0;// 初始化索引i为0，用于遍历字符串数组。
    while (s1[i] == s2[i])// 当s1和s2在当前位置的字符相同时，继续比较下一个字符。
    {
        if (s1[i] == '\0')// 如果当前字符是字符串的末尾（遇到'\0'），则两个字符串相等，返回0。
        {
            return 0;
        }
        i++;// 增加索引i以比较下一个字符。
    }
    return s1[i] - s2[i];// 如果找到不同的字符，返回它们的ASCII值之差，以确定字符串的字典序。
}
int main()
{
    char s1[20] = "hello",
    s2[20]="hello",
    s3[20]="hell",
    s4[20]="hello!";
    cout << "请输入两个字符串：" << endl;
    cout << "strcmp1(s1, s2):" << strcmp1(s1, s2) << endl;
    printf("strcmp2(s1, s3):%d\n", strcmp2(s1, s3));
    printf("strcmp2(s1, s4):%d\n", strcmp2(s1, s4));
    return 0;
}