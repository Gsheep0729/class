#include <stdio.h>      // printf, sprintf
#include <conio.h>      // 控制台输入处理：_kbhit, _getch
#include <windows.h>    // 控制台句柄操作、光标定位
#include <stdbool.h>    // 布尔类型支持
#include <stdlib.h>     // 内存管理：malloc, free
#include <time.h>       // 随机数生成：time

#define WIDTH 40        // 游戏区域宽度（列数）
#define HEIGHT 20       // 游戏区域高度（行数）
#define INITIAL_LENGTH 3 // 贪吃蛇初始长度

// 蛇身节点结构（链表实现）
typedef struct SegmentNode {
    int x, y;                   // 节点在游戏区域中的坐标
    struct SegmentNode* next;   // 指向下一个节点的指针
} SegmentNode;

// 贪吃蛇结构（链表实现）
typedef struct {
    SegmentNode* head;          // 指向蛇头节点的指针
    SegmentNode* tail;          // 指向蛇尾节点的指针
    int length;                 // 当前蛇身长度
} Snake;

int direction;      // 当前移动方向（1上 2下 3左 4右）
int fruitX, fruitY; // 食物坐标
int score;          // 游戏得分
Snake snake;        // 贪吃蛇实例
bool isGameOver;    // 游戏结束标志
bool showStartTip;  // 显示开始提示标志

// 设置控制台光标位置（基于0的坐标系统）
void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)x, (SHORT)y }; // 坐标结构体
    SetConsoleCursorPosition(hConsole, coord); // 应用新坐标
}

// 初始化贪吃蛇（链表版本）
void initSnake() {
    int startX = WIDTH / 2;   // 初始中心X坐标
    int startY = HEIGHT / 2;  // 初始中心Y坐标

    // 初始化三个节点，形成链表：头节点->第二节点->尾节点
    SegmentNode* third = (SegmentNode*)malloc(sizeof(SegmentNode));
    third->x = startX - 2;    // 尾部节点X坐标
    third->y = startY;        // 保持Y轴一致
    third->next = NULL;       // 尾节点的next为空

    SegmentNode* second = (SegmentNode*)malloc(sizeof(SegmentNode));
    second->x = startX - 1;   // 中间节点X坐标
    second->y = startY;
    second->next = third;     // 指向尾部节点

    SegmentNode* first = (SegmentNode*)malloc(sizeof(SegmentNode));
    first->x = startX;       // 头部节点X坐标
    first->y = startY;
    first->next = second;     // 指向中间节点

    snake.head = first;       // 初始化蛇头
    snake.tail = third;       // 初始化蛇尾
    snake.length = INITIAL_LENGTH; // 设置初始长度
}

// 生成新食物（与文档1逻辑相同）
void generateFruit() {
    fruitX = rand() % WIDTH;  // X坐标在0-WIDTH之间
    fruitY = rand() % HEIGHT; // Y坐标在0-HEIGHT之间
}

// 移动贪吃蛇（链表版本）
void moveSnake() {
    SegmentNode* head = snake.head;
    int newX = head->x;       // 获取当前头部X坐标
    int newY = head->y;       // 获取当前头部Y坐标

    // 根据方向计算新头部坐标
    switch (direction) {
    case 1: newY--; break; // 上
    case 2: newY++; break; // 下
    case 3: newX--; break; // 左
    case 4: newX++; break; // 右
    }

    // 边界碰撞检测
    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) {
        isGameOver = true;
        return;
    }

    // 自碰撞检测（从第二个节点开始检查）
    SegmentNode* current = head->next;
    while (current != NULL) {
        if (current->x == newX && current->y == newY) {
            isGameOver = true;
            return;
        }
        current = current->next;
    }

    // 创建新头部节点
    SegmentNode* newHead = (SegmentNode*)malloc(sizeof(SegmentNode));
    newHead->x = newX;
    newHead->y = newY;
    newHead->next = snake.head; // 新头节点指向原头节点
    snake.head = newHead;       // 更新链表头部

    // 食物检测逻辑
    if (newX == fruitX && newY == fruitY) {
        snake.length++;        // 增加蛇身长度
        score += 10;           // 更新得分
        generateFruit();       // 生成新食物
    } else {
        // 未吃到食物时需要移除尾节点
        if (snake.length == 1) { // 特殊情况处理：仅剩头节点
            free(snake.head);
            snake.head = snake.tail = NULL;
        } else {
            // 遍历找到尾节点的前驱节点
            SegmentNode* prev = snake.head;
            while (prev->next != snake.tail) {
                prev = prev->next;
            }
            free(snake.tail);  // 释放尾节点内存
            prev->next = NULL; // 前驱节点next置空
            snake.tail = prev; // 更新尾节点指针
        }
    }
}

// 绘制游戏界面（适配链表实现）
void draw() {
    setCursorPosition(0, 0); // 重置光标到左上角

    const int LINE_SIZE = WIDTH + 3; // 每行字符数（包含边界）
    char buffer[(LINE_SIZE * (HEIGHT + 2)) + 50]; // 屏幕缓冲区
    memset(buffer, 0, sizeof(buffer));
    int index = 0; // 缓冲区写入位置指针

    // 绘制上边界
    for (int i = 0; i < WIDTH + 2; i++) buffer[index++] = '#';
    buffer[index++] = '\n';

    // 绘制游戏区域
    for (int y = 0; y < HEIGHT; y++) {
        buffer[index++] = '#'; // 左边界
        for (int x = 0; x < WIDTH; x++) {
            bool isSnake = false;
            SegmentNode* current = snake.head;
            int pos = 0; // 节点位置（0表示头节点）
            while (current != NULL) {
                if (current->x == x && current->y == y) {
                    // 使用@表示头部，O表示身体
                    buffer[index++] = (pos == 0) ? '@' : 'O';
                    isSnake = true;
                    break;
                }
                current = current->next;
                pos++;
            }
            if (!isSnake) buffer[index++] = (x == fruitX && y == fruitY) ? 'F' : ' ';
        }
        buffer[index++] = '#'; // 右边界
        buffer[index++] = '\n';
    }

    // 绘制下边界
    for (int i = 0; i < WIDTH + 2; i++) buffer[index++] = '#';
    buffer[index++] = '\n';

    // 状态信息显示
    index += sprintf(buffer + index, "Score: %d\n", score);

    // 游戏结束/开始提示显示
    if (isGameOver) {
        index += sprintf(buffer + index,
            "Game Over! Score: %d\nPress Q to quit, R to restart\n",
            score);
    }
    else if (showStartTip) {
        index += sprintf(buffer + index, "Press WASD to start\n");
    }

    printf("%s", buffer);
    fflush(stdout); // 强制刷新输出缓冲区
}

// 初始化游戏状态（与文档1逻辑相似）
void initialize() {
    system("cls");          // 清屏
    srand(time(NULL));      // 初始化随机数种子
    initSnake();            // 初始化蛇
    generateFruit();        // 生成第一个食物
    score = 0;              // 重置得分
    direction = 0;          // 初始无方向
    isGameOver = false;     // 重置游戏状态
    showStartTip = true;    // 显示开始提示
}

int main() {
    // 控制台光标设置（与文档1相同）
    CONSOLE_CURSOR_INFO originalCursorInfo;
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &originalCursorInfo);

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    initialize(); // 初始化游戏

    bool isRunning = true;
    while (isRunning) {
        if (_kbhit()) { // 检测按键输入
            int key = _getch();
            if (isGameOver) { // 游戏结束后的操作
                if (tolower(key) == 'q') isRunning = false;
                else if (tolower(key) == 'r') initialize();
            } else { // 游戏进行中的操作
                switch (tolower(key)) {
                case 'w': if (direction != 2) direction = 1; break; // 防止180度转向
                case 's': if (direction != 1) direction = 2; break;
                case 'a': if (direction != 4) direction = 3; break;
                case 'd': if (direction != 3) direction = 4; break;
                case 'q': isRunning = false; break;
                }
                showStartTip = false; // 关闭开始提示
            }
        }

        if (!isGameOver && direction != 0) moveSnake(); // 游戏进行中移动
        draw();          // 刷新界面
        Sleep(200);      // 控制游戏速度（200ms/帧）
    }

    // 释放链表内存（文档2新增的重要操作）
    SegmentNode* current = snake.head;
    while (current != NULL) {
        SegmentNode* temp = current;
        current = current->next;
        free(temp); // 逐个释放节点内存
    }

    // 恢复控制台原始设置
    SetConsoleCursorInfo(hConsole, &originalCursorInfo);
    return 0;
}