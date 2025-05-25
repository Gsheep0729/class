/*C语言的动态内存分布和使用目的：为班上人数申请内存再打印出人数。
思路；设班级人数，根据人数申请内存，再初始化内存，最后释放内存*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
int main()
{
    int a = 0;
    cout << "请输入人数";
    cin >> a ;
    int *age = (int*)malloc(sizeof(int) * a);/*C语言格式,设指针"age"为内存块*/
    /*类型转换：由于 malloc 返回的是 void * 类型的指针，
    因此通常需要将其转换为实际所需数据类型的指针*/
    if(age == NULL)
    {
        cout <<"申请空间失败" <<endl;
        return -1;
    }
    /*内存初始化：malloc 分配的内存区域不会自动初始化，其内容是不确定的。如果需要，你必须手
    动初始化分配的内存。为了防止脏数据的出现，一般在申请完空间后，将申请到的空间内容清零*/
    memset(age, 0, a * sizeof(int));
    /*给数组赋值*/
    for(int b = 0; b < a;b++)
    {
        age[b] = b + 1;
    }
    /*打印数组元素*/
    for(int b = 0; b < a;b++)
    {
        cout << age[b] <<" ";
    }
    free(age);/*释放内存*/
    age = NULL;

    return 0;

}