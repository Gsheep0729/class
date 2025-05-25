#include <iostream>

int Max(int c, int d) // 函数定义 包含函数体
{
    // std::cout << a << std::endl;

    std::cout << "糟糕，MAX函数正在被执行" << std::endl;
    if (c > d)
    {
        return c;
    }
    else
    {
        return d;
    }
}

int main()
{
    int a = 1314;
    int b = 520;
    int max = 0;

    std::cout << "MAX函数要被执行啦" << std::endl;
    max = Max(a, b); // 调用
    std::cout << "MMAX函数执行完毕" << std::endl;

    std::cout << "max = " << max << std::endl;

    return 0;
}