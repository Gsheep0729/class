#include <stdio.h>      // printf, sprintf
#include <conio.h>      // 非阻塞键盘检测（_kbhit）和字符输入（_getch）
#include <windows.h>
/*
GetStdHandle - 用来获取标准输入、输出或错误流的句柄，通常用于控制台程序。
SetConsoleCursorPosition - 设置控制台光标的位置，通常用于在控制台窗口中移动光标。
SetConsoleOutputCP - 设置控制台的输出字符集，通常用于改变字符编码，特别是在多语言环境中。
GetConsoleCursorInfo - 获取当前控制台光标的状态信息（如光标大小和是否可见）。
SetConsoleCursorInfo - 设置控制台光标的状态信息，包括大小和是否可见。
Sleep - 让程序暂停一段时间，单位是毫秒，常用于暂停程序执行。
*/
#include <stdbool.h>    // bool
#include <stdlib.h>     // malloc, realloc, free, rand, srand, exit
#include <time.h>       // time

#define WIDTH 40 // 界面宽度
#define HEIGHT 20 // 界面高度
#define INITIAL_LENGTH 3  // 保持初始3节

// 蛇节,只储存坐标
typedef struct
{
    int x, y;
} Segment;

// 蛇身，
typedef struct
{
    Segment* body; //一个动态分配的数组，用于储存蛇的各个节
    int length;//  当前长度
    int capacity;// 当前分配给蛇身体数组的最大容量，用于动态扩展
} Snake;

int direction; // 当前移动方向
int fruitX, fruitY; // 食物坐标
int score; // 分数
Snake snake; // 蛇
bool isGameOver; // 游戏是否结束
bool showStartTip; // 是否显示开始提示

//精确控制控制台光标位置
void setCursorPosition(int x, int y)
{
    // 创建控制台句柄，GetStdHandle - 用来获取标准(STD_OUTPUT_HANDLE)输入、输出或错误流的句柄，通常用于控制台程序。
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {(SHORT)x, (SHORT)y}; // 二维坐标结构体
    // 通过GetStdHandle()获取的控制台句柄来移动光标到coord位置
    SetConsoleCursorPosition(hConsole, coord);
}

// 修改点1：初始化蛇身坐标重叠
void initSnake() 
{
    snake.capacity = 10; // 初始最大容量为10
    snake.body = (Segment*)malloc(snake.capacity * sizeof(Segment)); // 分配内存
    snake.length = INITIAL_LENGTH; // 设置初始长度

    int startX = WIDTH / 2; // 起始x坐标
    int startY = HEIGHT / 2; // 起始y坐标
    // 所有节段初始位置相同（从中心开始）
    for(int i = 0; i < INITIAL_LENGTH; i++) 
    {
        snake.body[i].x = startX;  // 不再减i
        snake.body[i].y = startY;
    }
}

// 生成食物
void generateFruit() 
{
    fruitX = rand() % WIDTH; // 随机生成食物x坐标
    fruitY = rand() % HEIGHT; // 随机生成食物y坐标
}

// 扩展蛇的容量
void expandCapacity() 
{
    snake.capacity *= 2; // 默认扩容为原来的两倍
    // 重新分配蛇身体数组的所占的内存大小
    Segment* newBody = (Segment*)realloc(snake.body, snake.capacity * sizeof(Segment));
    if(newBody) snake.body = newBody; // 如果重新分配成功，则赋值给蛇身体数组
}

// 修改点2：初始时碰撞检测忽略头部自身
void moveSnake() 
{
    int newX = snake.body[0].x; // 新头部x坐标
    int newY = snake.body[0].y; // 新头部y坐标

    switch(direction) 
    {
        case 1: newY--; break; // 上
        case 2: newY++; break; // 下
        case 3: newX--; break; // 左
        case 4: newX++; break; // 右
    }

    // 边界碰撞检测（检查头是否超出边界）
    if(newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) 
    {
        isGameOver = true; // 游戏结束
        return;
    }

    // 自碰撞检测（从第4节开始检查，因为三节不可能与自身发生碰撞）
    for(int i = 3; i < snake.length; i++) 
    {  
        if(snake.body[i].x == newX && snake.body[i].y == newY) 
        {
            isGameOver = true; // 游戏结束
            return;
        }
    }

    // 检查身体大小是否越界
    if(snake.length + 1 >= snake.capacity) 
    {
        expandCapacity(); // 扩容
    }

    // 插入新头部（将节依次转递位置）
    for(int i = snake.length; i > 0; i--) 
    {
        snake.body[i] = snake.body[i-1];
    }
    snake.body[0].x = newX;
    snake.body[0].y = newY;

    // 当吃到食物时
    if(newX == fruitX && newY == fruitY) 
    {
        snake.length++; // 长度+1
        score += 10; // 分数+10
        generateFruit(); // 生成新的食物
    }
}

// 绘制函数保持不变
void draw() 
{
    setCursorPosition(0, 0); // 设置光标位置到左上角

    const int LINE_SIZE = WIDTH + 3; // 每行字符数（含边界和换行）

    /*这里由于编辑器的问题，不能直接一条语句初始化，在加了一个memset进行初始化
    char buffer[BORDER_SIZE + GAME_AREA_SIZE + SCORE_SIZE] = {0};
    */
    // 创建足够大的缓冲区存储游戏界面
    char buffer[(LINE_SIZE * (HEIGHT + 2)) + 50];
    memset(buffer, 0, sizeof(buffer));
    int index = 0; // 缓冲区写入位置指针

    // 构建上边界
    for(int i = 0; i < WIDTH+2; i++) buffer[index++] = '#';
    buffer[index++] = '\n'; // 换行

    // 构建游戏区域
    for(int y = 0; y < HEIGHT; y++) {
        buffer[index++] = '#';
        for(int x = 0; x < WIDTH; x++) {
            bool isSnake = false;
            for(int i = 0; i < snake.length; i++) {
                if(snake.body[i].x == x && snake.body[i].y == y) {
                // 如果是蛇头，则显示 '@'，否则显示 'O'
                buffer[index++] = (i == 0) ? '@' : 'O';
                isSnake = true;
                break;
                }
            }
            if(!isSnake) buffer[index++] = (x == fruitX && y == fruitY) ? 'F' : ' ';
        }
        buffer[index++] = '#';
        buffer[index++] = '\n';
    }

    // 构建下边界
    for(int i = 0; i < WIDTH+2; i++) buffer[index++] = '#';
    buffer[index++] = '\n'; // 换行

    // 添加状态信息
    index += sprintf(buffer + index, "Score: %d\n", score); // 添加分数信息

    // 游戏结束提示
    if(isGameOver) 
    {
        index += sprintf(buffer + index, 
            "Game Over! Score: %d\n"
            "Press Q to quit, R to restart\n", 
            score);
    } 
    else if(showStartTip) 
    {
        index += sprintf(buffer + index, "Press WASD to start\n"); // 开始提示
    }

    printf("%s", buffer); // 一次性输出游戏界面
    fflush(stdout); // 强制刷新输出缓冲区(控制台逐字符覆盖旧内容)
}

// 初始化游戏
void initialize() 
{
    system("cls");
    /* 先生成随机数种子->再初始化蛇->生成食物->设置初始方向为0 */
    srand(time(NULL)); // 初始化随机数种子
    initSnake(); // 初始化蛇
    generateFruit(); // 生成食物
    score = 0; // 初始化分数
    direction = 0; // 初始化方向
    isGameOver = false; // 初始化游戏状态为未结束
    showStartTip = true; // 显示开始提示
}

int main() 
{
    CONSOLE_CURSOR_INFO originalCursorInfo; // 保存原始光标状态
    
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出为UTF-8编码
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台句柄
    
    // 先获取并保存原始光标状态
    GetConsoleCursorInfo(hConsole, &originalCursorInfo); 

    CONSOLE_CURSOR_INFO cursorInfo; // 光标信息结构体
    GetConsoleCursorInfo(hConsole, &cursorInfo); // 获取当前光标信息
    cursorInfo.bVisible = false; // 设置光标不可见
    SetConsoleCursorInfo(hConsole, &cursorInfo); // 应用新设置

    initialize(); // 初始化游戏

    bool isRunning = true; // 游戏运行状态
    while(isRunning) 
    {
        if(_kbhit()) // 检测是否有按键按下
        {
            int key = _getch(); // 获取按键值
            
            if(isGameOver) 
            {
                if(tolower(key) == 'q') isRunning = false; // 按Q退出游戏
                else if(tolower(key) == 'r') initialize(); // 按R重新开始游戏
            } 
            else 
            {
                switch(tolower(key)) 
                {
                    case 'w': if(direction != 2) direction = 1; break; // 上
                    case 's': if(direction != 1) direction = 2; break; // 下
                    case 'a': if(direction != 4) direction = 3; break; // 左
                    case 'd': if(direction != 3) direction = 4; break; // 右
                    case 'q': isRunning = false; break; // 按Q退出游戏
                }
                showStartTip = false; // 隐藏开始提示
            }
        }

        if(!isGameOver && direction != 0) moveSnake(); // 如果游戏未结束且有方向输入，则移动蛇
        draw(); // 绘制游戏界面
        Sleep(200); // 休眠200毫秒
    }

    // 退出前恢复原始光标状态
    SetConsoleCursorInfo(hConsole, &originalCursorInfo); 
    
    free(snake.body); // 释放蛇身体数组内存
    return 0;
}