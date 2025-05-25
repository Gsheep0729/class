//埃拉托色尼筛选素数
#include <iostream>
using namespace std;

int main()
{
    int num[20];
    for(int i=0;i<20;i++)//初始化为首项为2公差为1的数组
    {
        num[i] = i+2;
    }
    for(int i=0;i<20;i++)//循环筛选n个数
    {
        if(num[i] != 0)//判断是否为0,如果已经赋值为0则则跳过
        {
            for(int j=i+1;j<20;j++)//从i+1开始后的每个数都进行筛选
            {
                if(num[j]%num[i] == 0)//如果能被i整除，则赋值为0
                {
                    num[j] = 0;
                }
            }
        }
    }
    for(int i=0;i<20;i++)//输出筛选结果
    {
        if(num[i] != 0)
        {
            printf("%d ",num[i]);
        }
    }

    
    
    return 0;
}