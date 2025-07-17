#include <windows.h>
#include <stdio.h>

void setCursorPosition(int x, int y) {
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    system("cls"); // 清屏（Windows）
    // system("clear"); // 清屏（Linux/macOS）
}

int main() {
    clearScreen(); // 清屏
    setCursorPosition(0, 0); // 将光标移到左上角
    printf("Screen cleared. Cursor at (0,0).");
    return 0;
}