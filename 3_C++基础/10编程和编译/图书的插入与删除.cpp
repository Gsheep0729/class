/*分为写入，打印，插入，删除4个步骤函数实现*/
#include <iostream>
#include <cstring>
using namespace std;

// 定义书籍信息的结构体
typedef struct bookInfo
{
    char name[10]; // 书名，最多10个字符
    float price;   // 书的价格
    int num;       // 书的数量
} BOOKINFO;

// 计算有效图书的数量（————————————————————写入）
int size(const BOOKINFO *p)
{
    int n = 0; // 用于计数有效图书数量

    // 初始化信息0，非0是有效图书
    while (p->num != 0) // 只要当前图书数量不为0，就认为是有效图书
    {
        n++;           // 统计有效图书数量
        p++;           // 指向下一个书籍信息
    }
    return n; // 返回有效图书的数量
}

// 打印所有有效图书的信息（————————————————————打印）
void print(const BOOKINFO *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "第" << i + 1 << "本书的信息为："
             << "名字:" << p[i].name << "，价格:" << p[i].price << "，数量:" << p[i].num << endl;
    }
}

// 在指定位置插入一本书的信息
// p：结构体数组首元素地址
// p_info：要插入的图书信息
// location：插入的位置
// size：当前有效图书数量
void Insert(BOOKINFO *p, BOOKINFO *p_info, int location, int *size)//（————————————————————插入）
{
    BOOKINFO *p_tmp = p; // 临时指针，用于遍历插入位置后的元素

    // 有效图书数量增加1
    (*size)++;
    // 将指针移动到最后一个有效元素的下一个位置
    p_tmp += *size; // 指向新有效元素的下一个位置
    // 从后往前移动元素以腾出插入位置
    while (p_tmp > p + location)
    {
        *p_tmp = *(p_tmp - 1); // 前一个元素的信息覆盖到当前元素
        p_tmp--;               // 指针向前移动
    }
    *(p + location) = *p_info; // 将新图书信息放到指定插入位置
}

// 删除指定位置的图书信息
// p：结构体数组首元素地址
// location：删除的位置
// size：当前有效图书数量
void Delete(BOOKINFO *p, int location, int *size)//（————————————————————删除）
{
    BOOKINFO *p_tmp = p; // 临时指针，用于遍历删除位置后的元素

    // 将指针移动到要删除的位置
    p_tmp += location;

    // 从删除位置开始，覆盖后续元素
    while (p_tmp < p + *size) // 只要未超过有效元素范围
    {
        *p_tmp = *(p_tmp + 1); // 将后一个元素的信息覆盖到当前元素
        p_tmp++; // 指针向后移动
    }

    // 有效图书数量减少1
    (*size)--;
}

int main()
{
    int i = 0; // 计数器，用于记录已输入的图书数量
    // 申请一个大小为10的动态数组，用于存储图书信息
    BOOKINFO *p = new BOOKINFO[10];
    // 清空数组，初始化所有元素为0
    memset(p, 0, sizeof(BOOKINFO) * 10);   

    // 循环输入五本书的基本信息
    do
    {
        cout << "请输入第" << i + 1 << "个图书信息:";
        cin >> p[i].name >> p[i].price >> p[i].num; // 输入书名、价格和数量
        i++;
    } while (i < 5); // 只输入5本书的信息

    int n = size(p); // 计算有效图书的数量
    print(p, n); // 打印所有有效图书信息

    // 创建一个新的书籍信息用于插入
    BOOKINFO *p_info = new BOOKINFO;
    cout << "请输入要插入的图书信息:";
    cin >> p_info->name >> p_info->price >> p_info->num; // 输入新书信息

    int location = 0; // 插入位置初始化
    cout << "请输入要插入的位置:";
    cin >> location; // 输入插入位置

    Insert(p, p_info, location, &n); // 调用插入函数
    print(p, n); // 打印插入后的有效书籍信息

    cout << "请输入要删除的位置:";
    cin >> location; // 输入要删除的位置

    Delete(p, location, &n); // 调用删除函数
    print(p, n); // 打印删除后的有效书籍信息

    // 释放动态分配的内存
    delete p_info; // 删除新书信息
    p_info = NULL; // 将指针置为NULL以防止悬空指针

    delete[] p; // 删除图书信息数组
    p = NULL; // 将指针置为NULL以防止悬空指针
    return 0; // 程序结束
}