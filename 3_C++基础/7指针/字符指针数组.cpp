#include <stdio.h>

// 函数声明
void printMonth(int month);

int main() {
    int month;

    // 提示用户输入月份
    printf("请输入一个月份（1-12）：");
    scanf("%d", &month);

    // 调用函数输出月份名称
    printMonth(month);

    return 0;
}

// 函数定义
void printMonth(int month) {
    // 定义存储月份名称的字符串数组
    const char *months[] = {
        "无效月份", // 用于处理非法输入（可选）
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"
    };

    // 检查输入是否在有效范围内
    if (month < 1 || month > 12) {
        printf("输入的月份无效。\n");
    } else {
        // 输出对应的月份名称
        printf("%s\n", months[month]);
    }
}