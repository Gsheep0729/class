#include <iostream>
#include <cstring>
using namespace std;
typedef struct student
{
    char name[10];/*姓名，同样可以string mane->="高扬"*/
    int age;/*年龄*/
    float height;/*身高*/
    void printf()
    {
        cout<<"name="<<name<<",age="<<age<<",height="<<height<<endl;
    }

}GY;
int main()
{
    GY a  = {"高扬",18,170.111f};
    cout<<"name="<<a.name<<",age="<<a.age<<",height="<<a.height<<endl;
    /*申请结构体一样大小的内存(内存首地址为b)，同时释放掉*/
    GY *b = new GY;
    //GY *b = &a;
    /*判断内存是否申请成功*/
    if(b == NULL)
    {
        cout << "申请内存失败";
        return -1;
    
    }
    /*将申请的内存初始化，格式：void * memset(void * buffer, int c, size_t num)
    buffer为起始地址，c为需要设置的值，num为设置该值的字节数*/
    memset(b,0,sizeof(student));//注：memset标识符在string头文件里
    /*对申请的内存初始化后的数据进行赋值*/
    strcpy(b->name,"高扬");//本质是复制字符串
    b->age =19;
    b->height = 180.222f;
    b->printf();

    /*内存释放*/
    delete b;
    b = NULL;


    return 0 ;
}