//100/50/20/10换算

#include <iostream>

int main()
{
    int hundred = 100;
    int fifty = 50;
    int twenty = 20;
    int ten = 10;
    for( int a = 0  ; a <= 2 ;a++)//100
    {
        for ( int b = 0 ; b <= 5 ;b++)//20
        {
            for( int c = 0 ; c <=10 ;c++)//10
            {
                if( a * fifty + b * twenty + c * ten == hundred )//用“==”为等于，"="为定义，初始赋值
                {
                    std::cout << a <<"张50  "<< b <<"张20  "<< c <<"张10  "<<std::endl;
                }
            }
        }
    }
    


    return 0 ;
}