#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    cout << &a << endl;
    printf("%p\n", &a);

    int d = 1;

    char c = 'a';
    cout << (void *)&c << endl; // c++字符类型需要
    printf("%p\n", &c);

    int arr[5] = {0};
    for (int i = 0; i < 5; i++)
    {
        std::cout << "&arr[i] = " << &arr[i] << std::endl;
    }

    return 0;
}