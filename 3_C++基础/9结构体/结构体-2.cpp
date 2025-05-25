/*结构体指针及检引用*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
struct student
{
    char name[10];/*姓名*/
    int age;/*年龄*/
    float height;/*身高*/

};
int main()
{
    struct student a={"高扬",18,170};
    /*结构体指针定义*/
    struct student *b=&a;
    //检引用，3种方法
    cout<<a.name<<endl;
    cout<<(*b).name<<endl;
    cout<<b->name<<endl;
    return 0 ;
}