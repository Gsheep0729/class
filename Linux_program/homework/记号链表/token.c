#include <stdio.h>
#include "token.h"//11111111111111111

void print_token(token_t *p)//打印出记号的名字
{  
    /*使用 fputs 函数将p指向的节点中的 name 成员（即记号的名称）输出到标准输出（stdout）*/
    fputs(p->name, stdout);
    /*使用 putchar 函数输出单个字符，使得下一次输出从新的一行开始*/
    putchar('\n');  
}  