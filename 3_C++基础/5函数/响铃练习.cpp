#include <iostream>
int main()
{
    int a = 1;
    int b = 2;
    std::cout << "请输入第一个数：";
    std::cin >> a;

    while (getchar() != '\n');
        

    std::cout<< "请输入第二个数：";
    std::cin >> b;

    std::cout << "a = " << a << ", b = " << b << std::endl;

    char c = '\a'; // 他就表示一个响铃，运行这行代码，计算机就会响一下
    std::cout << c << std::endl;
    return 0;
}