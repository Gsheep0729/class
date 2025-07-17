/*由于各裁判打分时存在某些主观因素，
因此在计算平均值时通常去掉一个最高分，去掉一个最低分。
写一个程序，读入7个裁判所打的分数，去掉一个最低分，
去掉一个最高分，求剩余5个元素的平均值*/
#include <iostream>
using namespace std;

int main()
{
    int a[7],i,j,max,min,sum=0;
    cout << "请输入裁判的7个打分："<< endl;
    for(i=0;i<7;i++)//输入7个数
    {
        cin >> a[i];
    }
    max=a[0];
    min=a[0];
    //找出最大值和最小值
    for(i=0;i<7;i++)//循环7次
    {
        if(a[i]>max)//找到最大值
        {
            max=a[i];
        }
        if(a[i]<min)//找到最小值
        {
            min=a[i];
        }
    }
    for(i=0;i<7;i++)//循环7次
    {
        if(a[i]!=max&&a[i]!=min)//去掉最大值和最小值
        {
            sum+=a[i];
        }
    }
    cout << "选手的平均成绩为："<<sum/5;//求平均值
    
    
    return 0;
}