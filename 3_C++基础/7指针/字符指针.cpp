/*像指针一样操作字符串*/
#include <iostream>
using namespace std;
int main()
{
    // 定义一个指向常量字符串的指针
    const char *p = "Hello, World!";
    // 输出指针p所指向的字符串
    cout <<"p="<< p << endl;// Hello, World!
    // 输出指针p所指向的第一个字符
    cout <<"*p="<< *p << endl;// H
    // 输出指针p所指向的第一个字符，等同于*p
    cout <<"*(p+0)="<< *(p+0) << endl;// H
    // 输出指针p所指向的第二个字符
    cout <<"*(p+1)="<< *(p+1) << endl;// e
    // 使用数组下标的方式输出指针p所指向的第一个字符，等同于*p
    cout <<"p[0]="<< p[0] << endl;  // H
    // 使用数组下标的方式输出指针p所指向的第二个字符
    cout <<"p[1]="<< p[1] << endl;   // e
    // 输出指针p本身加0后的地址，即指针p的地址
    cout <<"p+0="<< p+0 << endl;  // Hello, World!
    // 输出指针p加1后的地址，即指向字符串的第二个字符
    cout <<"p+1="<< p+1 << endl;// ello, World!
    // 输出指针p加2后的地址，即指向字符串的第三个字符
    cout <<"p+2="<< p+2 << endl;// llo, World!
    return 0;
}