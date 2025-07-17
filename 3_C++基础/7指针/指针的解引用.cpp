#include <iostream>
using namespace std;

int main()
{
    int a = 5;
    int *p_a = &a; // 定义变量的时候 * 是一个类型说明符,说明定义的这个变量是一个指针变量

    cout << *p_a << endl; // 对指针变量**解引用**，即获取指针变量所指向区域的内容
    // p_a = 10;//error
    *p_a = 10;
    cout << *p_a << endl; //*p_a  <==> a
    cout << a << endl;

    int *p;                        // 野指针
    p = &a;                        // 重新绑定内存
    std::cout << *p << std::endl;  // 野指针和空指针不能解引用
    int *p1 = NULL;                // 野指针
    p1 = &a;                       // 重新绑定内存
    std::cout << *p1 << std::endl; // 野指针和空指针不能解引用

    return 0;
}