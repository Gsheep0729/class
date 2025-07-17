/*条件编译：格式（#if ... #elif(任意多次)... #else ... #endif）
条件编译的好处是可以进行判断，减少编译的时间和占用空间
灰色部分是未被编译的部分*/
#include<iostream>
#define A 114514/*定义一个宏*/
int main()
{
#if A > 0
std::cout << "正数" << std::endl;
#elif A == 0
std::cout << "0" << std::endl;
#else
std::cout << "负数" << std::endl;
#endif
/*与未加#的if区别是，未加#的if全部被编译了，没有执行而已*/
return 0;
}
