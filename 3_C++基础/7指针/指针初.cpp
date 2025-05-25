#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    int b = 1;
    int *p_a = &a; // 定义指针变量p_a，存储a的地址
    int *p_b = &a; // 多个指针变量可以指向同一个地址
    p_b = &b;      // 指针的指向是可以改变的

    // double *p = &a; //error 指针的类型要和变量的类型一致

    // int *p;         // 野指针
    int *p1 = NULL; // 空指针 合法初始化

    char ch = 'b';
    char *p_ch = &ch;
    std::cout << "sizeof(p_ch) = " << sizeof(p_ch) << std::endl;
    std::cout << "sizeof(p_a) = " << sizeof(p_a) << std::endl;

    return 0;
}
