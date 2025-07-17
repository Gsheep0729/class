//#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>// POSIX特性

int main() {
    // 检查是否支持POSIX特性
    if (_POSIX_C_SOURCE >= 200809L) {
        printf("POSIX 2008 features are supported.\n");
    } else {
        printf("POSIX 2008 features are not supported.\n");
    }

    // 使用特性测试宏控制代码行为
    #ifdef _POSIX_C_SOURCE
        printf("POSIX_C_SOURCE is defined.\n");
    #else
        printf("POSIX_C_SOURCE is not defined.\n");
    #endif

    return 0;
}