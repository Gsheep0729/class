#include <iostream>
//#include <cstring>
int fuck(int a ,int b)
{
    
    //函数中再定义鸡的变量
    for(int d = 0; d <= a;d++)
    {
        if(d * 2+ ( a - d ) * 4 == b )
        {
           return d;
           //输入形参，函数里为实参，最后的结果返回 
        }
    
    }

    return 404;
    //函数结束后要记得归零

}
int main()
{
    int a = 0;//头
    int b = 0;//脚
    int c = 0;//鸡数
    std::cout << "请分别输入头和脚";
    std::cin >> a >> b ; 
    if(b % 2  || b < 2*a || b > 4*a)
    //注意！错误算式判断需谨慎严谨
    {
        std::cout<<"错误！";
    }
    else
    {
        c = fuck( a , b );
        std::cout << "鸡的数量为：" << c << "兔的数量为："<< a-c;
    }

    return 0;
}