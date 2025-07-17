#include <windows.h>
#include <stdio.h>

/**
 * @brief 设置控制台光标位置
 * @param x 控制台窗口中的横向坐标（基于0的起始位置）
 * @param y 控制台窗口中的纵向坐标（基于0的起始位置）
 * 
 * 该函数通过Windows API操作控制台光标位置，使用标准输出句柄，
 * 将光标移动到控制台窗口的指定坐标位置。内部使用COORD结构体
 * 存储坐标值，并调用SetConsoleCursorPosition完成实际操作
 */
void setCursorPosition(int x, int y) {
    // 获取标准输出设备句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 构造坐标结构体（注意坐标需转换为SHORT类型）
    COORD coord = {(SHORT)x, (SHORT)y};
    // 执行光标位置设置操作
    SetConsoleCursorPosition(hConsole, coord);
}

int main() {
    // 在控制台坐标(5,5)处输出文本
    // （实际显示位置可能因控制台字体大小和窗口尺寸影响）
    setCursorPosition(5, 5);
    printf("Hello, World!");

    // 在控制台坐标(10,10)处进行二次输出演示
    setCursorPosition(10, 10);
    printf("This is a test.");

    return 0;
}