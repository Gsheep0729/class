/*设计一个函数原型，允许这个函数能同时寻找和返回一个double型数组中的最大值和最小值*/
#include <iostream>
using namespace std;
#define n 100
void findMaxMin(double a[])
{
    double max = a[0], min = a[0];
    for (int i = 1; i < n; i++)//使用冒泡算法寻找最大值和最小值
    {
        if (a[i] > max)
        {
            max = a[i];
        }
        if (a[i] < min)
        {
            min = a[i];
        }
    }
    printf("数组的范围为:%g-%g\n", min,max);
    
}

int main()
{
    cout <<"请一直输入浮点数，直到输入0结束："<<endl;
    double a[n];
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] == 0)
        {
        break;
        }
    }
    findMaxMin(a);
    
    return 0;
}