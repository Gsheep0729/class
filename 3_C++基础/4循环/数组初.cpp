#include <iostream>

int main()
{
    //int a [3] = {1,2,3}
    double a [] = {2,1,3};//定义个数必须是常量,全部初始化。
    //若未初始化，自动初始为0，完全不初始化为随机值

    std::cout << sizeof(a)/sizeof(double) << std::endl;
    std::cout << "a[0] = " << a[0] << std::endl;//从0开始数
    std::cout << "a[1] = " << a[1] << std::endl;
    std::cout << "a[2] = " << a[2] << std::endl;
    //std::cout << a[3] << std::endl;//数组越界(最好别这么做)随机值


    for(int b = 0 ; b < 3 ; b++)
    {
        std::cout << a[b] << std::endl;
    }







    //int a = 1 ;
    //for ( int a = 0; a < 6 ; a++)
    //{
    //    for( int b =0 ;b <= a ;b++)
    //    {
    //        std::cout << "*";
    //    }
    //    std::cout<<std::endl;
    //}
    
    return 0;
}       