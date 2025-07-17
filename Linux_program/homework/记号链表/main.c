/*下面是一个关于使用记号扫描器模块scannerh和 scanner.c来构建记号（token）链表的程序
常见的 token 类型包括：
关键字（Keywords）：如 if、for、while 等。
标识符（Identifiers）：如变量名、函数名等。
操作符（Operators）：如 +、-、*、/、==、> 等。
常量（Constants）：如数字（123）、字符串（"Hello"）等。
分隔符（Delimiters）：如括号（()）、花括号（{}）、逗号（,）、分号（;）等。
注释（Comments）：通常会被词法分析器忽略。
*/
#include <stdio.h>
#include <stdlib.h>  
#include "token.h"
#include "scanner.h"

int main(void)
{
    char *line = NULL;//定义了一个指向字符的指针line，用来存储用户输入的字符串的地址
    size_t n = 0;//size无符号整数类型,表示非负数
    /*getline 函数用于从输入流中读取一行数据，包括换行符。
    它会将读取到的数据存储在指定的缓冲区中，并返回读取到的字符数。
    如果遇到文件结束或读取错误，则返回 -1。
    ssize有符号整数类型，通常用于表示可以是负数的大小或数量
    */
   //输入字符串，并记录输入字符的个数，包括换行符
    ssize_t read = getline(&line, &n, stdin);//第2222222222222222222个填写
    line[read - 1] = '\0';//删除输入字符串的换行符，替换为空字符
    init_scanner(line);//初始化扫描器
    /*声明链表指针（link包含两个成员：一个指向字符数组的指针 name，用于存储名称；
    一个指向下一个节点的指针 next，用于链接下一个节点）*/
    token_t *link = NULL;//声明链表指针
    while (!at_end_of_line())//循环，直到到达行尾，用来提取非特殊字符
    {
        //定义一个token_t的指针p并分配一个指针的内存用来存储提取的记号首节点位置
        token_t *p = malloc(sizeof(token_t));
        p->name = get_next_token();//将提取的记号首节点地址赋值给p->name
        //the two line inserts new node
        p->next = link;//第10个填写
        //链表头
        link = p; //根据思考题的逻辑最后一个填写
    }  

    token_t *ptr = link;//将

    while (ptr)//打印链表，根据设置的节点别打印
    {  
        print_token(ptr);
        ptr = ptr->next;
    }  
    return 0;  
}  