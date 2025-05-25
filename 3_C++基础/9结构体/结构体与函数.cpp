#include <iostream>
#include <cstring>
using namespace std;

typedef int INT;

typedef struct Student
{
    char name[10]; // 姓名  string name p->name = "丁程鑫"
    // char *name;   // 表示字符串
    INT age;      // 年龄
    float height; // 身高

    void print()
    {
        std::cout << "name = " << name << ", age = " << age << ", height = " << height << std::endl;
    }
} STU;

void setValue(STU stu) // int a
{
    strcpy(stu.name, "qwe");
    stu.age = 20;
    stu.height = 181.2f;
}

void setValue(STU *stu)
{
    strcpy(stu->name, "qwe");
    stu->age = 20;
    stu->height = 181.2f;
}

void set_stu_pro(STU *tmp, int n)
{
    for (int i = 0; i < n; i++)
    {
        strcpy(tmp[i].name, "蔡徐坤");
        tmp[i].age = 20;
        tmp[i].height = 190;
    }
}

int main()
{
    STU stu = {"abc", 18, 180.1f};
    setValue(stu);
    stu.print();
    setValue(&stu);
    stu.print();

    STU s[3] = {0};
    set_stu_pro(s, 3); // 数组名传递
    for (int i = 0; i < 3; i++)
    {
        s[i].print();
    }

    return 0;
}