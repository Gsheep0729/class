/*虽然你没有显式定义 str 为指针，但在 C++ 中，
数组名可以隐式转换为指向其第一个元素的指针。
因此，你可以对 str 进行指针操作，如解引用和指针算术运算*/
#include <iostream>
using namespace std;
int main()
{
    // 定义一个字符数组并初始化，用于存储字符串
    char str[] = "Hello world";
    // 定义一个字符指针，使其指向字符数组str的首地址
    char *p = str;
    
    // 输出字符数组str的全部内容
    cout << "str=" << str << endl;
    // 输出字符数组str的第一个元素
    cout << "str[0]=" << str[0] << endl;
    // 输出字符数组str的第二个元素
    cout << "str[1]=" << str[1] << endl;
    // 输出指针str所指向的值，即字符数组str的第一个元素
    cout << "*str=" << *str << endl;
    // 输出指针p所指向的值，即字符数组str的第一个元素
    cout << "*p=" << *p << endl;
    // 输出指针str加1后所指向的值，即字符数组str的第二个元素
    cout << "*(str+1)=" << *(str+1) << endl;
    // 输出指针p加1后所指向的值，即字符数组str的第二个元素
    cout << "*(p+1)=" << *(p+1) << endl;
    
    return 0;
}