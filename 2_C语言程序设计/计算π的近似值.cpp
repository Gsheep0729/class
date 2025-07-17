//计算π的近似值
#include <iostream>
using namespace std;

int main()
{
    double n=0;
    for(int i = 1; i <= 10000; i++)
    {
        if(i%2==1)//第i个为奇数为加
        {
            n+=1.0/(2.0*i-1);
        }
        else//偶数为减
        {
            n-=1.0/(2.0*i-1);
        }
    }
    printf("π≈%.10lf", 4*n);
    
    
    return 0;
}