/*结构体的使用，起别名，嵌套，结构体数组*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
//起别名typedef struct student GY;
struct Date
{
    int year;
    int month;
    int day;
};
typedef struct student
{
    char name[10];/*姓名*/
    int age;/*年龄*/
    float height;/*身高*/
    Date date;
    /*Date为我定义的数据类型，date为数据变量，结构体嵌套*/

    void printf()
    {
        /*结构体的引用*/
        cout << "name=" << name << ",age="<<age<<",height="
        <<height<<endl;
        /*嵌套结构体的引用*/
        cout << date.year<<"年" <<date.month<<"月"<<date.day<<"日"<<endl;
    }
}GY;

int main()
{
    //struct student a0={"高扬",18,180.1};
    /*起了别名后可以省略“struct”*/
    GY a1 ={"杨红鑫",18,200.1,{2024,1,1}};
    a1.printf();
    a1.height = 190.2;
    a1.printf();
    /*结构体数组:结构体数组和普通数组并无太大差异,
     只不过是数组中的元素都是结构体而已*/
    GY a2[3]
    {
        {"高扬",18,180.3,{2024,1,2}},
        {"杨红鑫",18,180.4,{2024,1,3}},
        {"周绍芳",58,150.5,{2024,1,4}}
    };/*初始化结构体*/
    for(int b =0;b < 3;b++)
    {
        a2[b].printf();
    }/*循环引用*/

    
    return 0;

}