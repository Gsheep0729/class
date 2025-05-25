#include <iostream>
#include <cstring>
using namespace std;
typedef struct student
{
    //char name[10];/*姓名，同样可以string mane->="高扬"*/
    char *name;
    int age;/*年龄*/
    float height;/*身高*/
    void printf()
    {
        cout<<"name="<<name<<",age="<<age<<",height="<<height<<endl;
    }

}GY;
int main()
{
    /*为指针变量指向的内容申请空间*/
    GY a ={NULL,18,170.111f};
    //普通变量（栈区）
    /*char类型为字符数组类型，所以申请内存时要加上“[]”*/
    a.name=new char[10];
    strcpy(a.name,"高扬");
    a.printf();

    /*栈区*/
    //堆区域结构体变量首先为结构体变量申请内存
    GY *b = new GY;
    //为指针变量指向的内容申请空间
    b->name=new char[10];
    strcpy(b->name,"高扬");
    b->age =18;
    b->height=170.222f;
    b->printf();
    /*new申请的数组的内存，delete也要加上“[]”
    释放顺序一定要与申请顺序相反,先释放大的
    会使小的找不到，也就无法释放小的内存*/
    delete[] a.name;
    a.name = NULL;

    delete[] b->name;
    b->name=NULL;

    delete[] b;
    b=NULL;

    return 0 ;
}