#ifndef SCANNER_H
#define SCANNER_H
#include <stdbool.h>

void init_scanner(char *str);

/* 函数 get_next_token;
用法： char *tp = get_next_token（）;
省略一些关于 Token 的行。
自由 （TP）;
--------------------------------
这个函数返回一个指针
指向在堆中分配的 token
} */

char *get_next_token(void);  
bool at_end_of_line(void);  

#endif // SCANNER_H  