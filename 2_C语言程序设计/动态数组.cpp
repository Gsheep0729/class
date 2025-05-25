/*写一个函数IndexArray(n)，返回指向动态分配的含n个元素的整型数组的指针，每个元素均初始化为自身的下标*/
#include <iostream>
using namespace std;
#define n 10
int* IndexArray(int num)//给指针指向的空间申请内存
{
    int* ip;
    ip = (int*)malloc(sizeof(int)*n);//申请内存
    for(int i=0;i<n;i++)//初始化赋值
    {
        ip[i] = i;
    }
    return ip;
}

int main()
{
    int *p;
    p = IndexArray(n);
    for(int i=0;i<n;i++)//输出
    {
        printf("p[%d] = %d\n",i,p[i]);
    } 
    
    return 0;
}