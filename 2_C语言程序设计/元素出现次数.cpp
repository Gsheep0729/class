/*写一个函数Tabluate(array，n)，
使其取一个整型数组和它的有效大小作为参数，画出一张显示每个元素出现次数的表格*/
#include <iostream>
#include <cstring>
using namespace std;
void Tabluate(int *num,int n)
{
    int min=num[0],max=num[0];
    for(int i=0;i<n;i++)//利用冒泡算法进行从小到大排序
    {
        for(int j=i+1;j<n;j++)
        {
            if(num[i]>num[j])//如果当前元素大于后续元素，则交换两者位置
            {
                int temp=num[i];
                num[i]=num[j];
                num[j]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)//遍历所有元素
    {
        printf("%d ",num[i]);//打印当前元素
        if(num[i]==num[i+1])//判断当前元素与下一个元素是否相同
        {
            int count=1;//初始化计数器为1，用于记录重复元素出现的次数
            while(num[i]==num[i+1])//循环判断下一个元素是否与当前元素相同
            {
                count++;//统计连续重复元素的次数
                i++;//跳过重复元素
            }
            printf(":%d\n",count);//打印重复元素及其出现次数
        }
        else
        {
            printf(":1\n");//如果当前元素没有重复，则打印出现次数为1
        }
    }
}

int main()
{
    int num[]={91,93,98,92,92,95,93,92,91,95,99,92,98};
    int n = sizeof(num)/sizeof(num[0]);//计算数组长度
    Tabluate(num,n);
    return 0;
}