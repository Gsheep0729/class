#include <iostream>
#include <cstring>
using namespace std;
void fuck(int num)
{
    cout << num <<" = 1";
    for(int a = 2;a <=num ;a++)
    {
        while(num % a == 0)
        {
            cout<<" * " << a;
            //判断完num可以被a除后完成一个循环，记得对数进行处理
            num /= a;
        }
    }
    cout << endl;
}


int main()
{
    int b = 0;
    cout <<"请输入你想用于因式分解的整数: ";
    cin >> b;
    fuck(b);

    
    return 0;
}