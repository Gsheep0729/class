#include <stdio.h>
#include <time.h>
/*
struct tm {
    int tm_sec;    // 秒，范围为 0 到 61（允许闰秒）
    int tm_min;    // 分钟，范围为 0 到 59
    int tm_hour;   // 小时，范围为 0 到 23
    int tm_mday;   // 一个月中的第几天，范围为 1 到 31
    int tm_mon;    // 月份，范围为 0 到 11（0 表示 1 月，11 表示 12 月）
    int tm_year;   // 年份，从 1900 年开始计算（例如，2025 年对应 125）
    int tm_wday;   // 一周中的第几天，范围为 0 到 6（0 表示星期日）
    int tm_yday;   // 一年中的第几天，范围为 0 到 365（0 表示 1 月 1 日）
    int tm_isdst;  // 夏令时标志（Daylight Saving Time）
};
*/

int main() {
    // 获取当前时间的时间戳
    time_t now = time(NULL);

    // 将时间戳转换为本地时间
    struct tm *time_info = localtime(&now);//标准库里的时间结构体

    // 提取年、月、日、时、分、秒
    int year = time_info->tm_year + 1900;  // tm_year 是从 1900 开始的
    int month = time_info->tm_mon + 1;     // tm_mon 是从 0 开始的（0 表示 1 月）
    int day = time_info->tm_mday;          // tm_mday 是日期（1-31）
    int hour = time_info->tm_hour;         // tm_hour 是小时（0-23）
    int minute = time_info->tm_min;        // tm_min 是分钟（0-59）
    int second = time_info->tm_sec;        // tm_sec 是秒（0-59）

    // 打印当前时间的详细信息
    printf("当前时间：\n");
    printf("年：%d\n", year);
    printf("月：%d\n", month);
    printf("日：%d\n", day);
    printf("时：%02d\n", hour);    // 使用 %02d 格式化为两位数
    printf("分：%02d\n", minute);  // 使用 %02d 格式化为两位数
    printf("秒：%02d\n", second);  // 使用 %02d 格式化为两位数

    return 0;
}