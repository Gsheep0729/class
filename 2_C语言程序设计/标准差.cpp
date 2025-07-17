/*标准差*/
#include <iostream>
#include <cmath>
using namespace std;
double standardDeviation(double *array,int n)
{
    double sum=0,sum2=0;
    for(int i=0;i<n;i++)//计算和
    {
        sum+=array[i];
        sum2+=array[i]*array[i];
    }
    return sqrt((sum2-sum*sum/n)/(n-1));  //返回标准差
}

int main()
{
    int n;
    cout<<"请输入数组长度："<<endl;
    cin>>n;
    double array[n];
    cout<<"请输入数组元素："<<endl;
    for(int i=0;i<n;i++)//输入数组元素
    {
        cin>>array[i];
    }
    cout<<"标准差为："<<standardDeviation(array,n)<<endl;
    
    
    return 0;
}