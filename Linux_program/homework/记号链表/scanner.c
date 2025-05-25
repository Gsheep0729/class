#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
/*因为带“;”就不能填define，C语言中可能为extern或者static，
extern 用来声明一个变量或函数为外部变量或函数，可以在其他文件中引用，作用域更大，
而static 用来声明一个变量或函数为静态变量或静态函数，区别extern作用域，static作用域在函数内或者
该文件内，外部文件无法访问，封装行更强
羔羊通过观察这五个文件总结出下面两个指针变量只在scanner使用，所以定义为static（其实省略了也无大碍）
*/
static char *buf_ptr;//第333333333333333333333个填写
static char *buf_end;//第444444444444444个填写

void init_scanner(char *str)//初始化扫描器
{
    //buf_ptr 指向字符串的起始位置
    buf_ptr = str;//第55555555555555555555555个填写
    //buf_end 指向字符串的结束位置
    buf_end =str + strlen(str);//第6666666666666666个填写
}  

bool at_end_of_line()//检查是否到达行尾
{
    //当达到行尾时，返回 true
    return buf_ptr >= buf_end || *buf_ptr == '\0';//第777777777777777777个填写
}  

char *get_next_token(void)//获取下一个记号
{
    char *start;//记录识别到的记号的起始位置
    char *token;//存储并返回识别到的记号的地址，并且最后加一个终止符用来间隔下一个字符
    /*isalnum() 拼写错误,isalnum 是 C 标准库<ctype.h>中的一个函数，
    用于检查一个字符是否是字母或数字,是则返回true，否则返回false
    isalnum 函数的作用是检查一个字符是否是字母或数字。它的主要用途包括：
    1.验证字符类型：快速判断一个字符是否属于字母（a-z 或 A-Z）或数字（0-9）。
    2.字符串处理：在处理字符串时，用于过滤或验证字符串内容是否只包含字母和数字。
    3.输入验证：在用户输入中，检查字符是否符合特定格式要求（例如用户名、密码等）。
    4.数据清洗：在处理文本数据时，去除非字母数字的字符。
    */
    if (isalnum(*buf_ptr))//判断首字符是否为字母或数字
    {
        //若是，则将识别到的一串字母或数字为一个记号
        start = buf_ptr;//将字符的首节点地址值值赋给局部变量start
        while (buf_ptr <= buf_end && isalnum(*buf_ptr)){
        buf_ptr++;}//跳过非字母或数字的字符
        size_t length = buf_ptr - start;//计算token的长度
        /*strncpy 的作用是从源字符串start中复制最多lengeh个字符
        到目标字符串 token 中。方向：start → token*/
        //分配足够的内存来储存识别到的字符串，最后添加一个终止符
        token = malloc(length + 1);//第8888888888888888个填写
        strncpy(token, start, length);//将start复制到token
        //需手动添加终止符
        token[length]  = '\0';//第99999999999999999999个填写
    }
    else
    {
        //若首字符不是字母或数字，则单独领出来作为一个记号
        //分配两个字节的内存，一个用来储存字符，一个用来添加终止符
        token = malloc(2);
        *token = *buf_ptr++;//跳过当前字符
        *(token + 1) = '\0';//添加终止符
    }  
    return token;  
}  