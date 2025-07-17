#include<iostream>      // 标准输入输出（std::cout）
#include<Windows.h>     // Windows API控制台操作（SetConsoleTextAttribute/GetStdHandle/SetConsoleCursorPosition/CONSOLE_CURSOR_INFO）
#include<conio.h>       // 控制台输入检测（_kbhit/_getch）
#include<ctime>         // 时间函数（time/srand/rand）
#include<string>        // 字符串类（std::string）
using namespace std;

//================ 结构体声明 ================

//定义敌人结构 其中最后面Frame代表结构体类型 若不加typedef代表定义的结构体变量
typedef struct Frame
{
       COORD position[2];//敌人为一个矩形，储存的矩形的左上角坐标和右下角坐标
       //   COORD 是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。
       // 其定义为：
       // typedef struct _COORD {
       //             SHORT X;
       //             SHORT Y;
       //          } COORD;
       int flag; //0为正常，1为被摧毁
}Frame;

//================ 全局辅助函数声明 ================

COORD random(COORD a, COORD b);
bool judgeCoordInFrame(Frame frame, COORD spot);

//================ 界面控制函数声明 ================

void setcolor(const char* str);
void HideCursor();
void SetPos(int i, int j);//设置光标位置到坐标（i, j）
void drawRow(int y, int x1, int x2, char ch);//把第y行，[x1, x2) 之间的坐标填充为 ch
void drawCol(int x, int y1, int y2, char ch);//把第x列，[y1, y2] 之间的坐标填充为 ch
//以坐标为a为左上角，b为右下角的矩形，以row为行边，col为列边，画出矩形
void drawFrame(COORD a, COORD b, char row, char col);
//以frame
void drawFrame(Frame frame, char row, char col);
void drawFrame(int x1, int y1, int x2, int y2, char row, char col);

int drawMenu();
void drawPlaying();

//================ 游戏类声明 ================

// 游戏类
class Game
{
public:
       COORD position[10];//飞机坐标
       COORD bullet[10];//子弹坐标
       Frame enemy[8];//敌人数量

       int score;
       int rank;//级别,难度
       //int rankf;//等级标志
       string title;

       int flag_rank;//等级标志
       //构造函数
    Game();
       //初始化所有   //设定位置
       void initPlane();
       void initBullet();
       void initEnemy();
       //填充所有   --画出形状和消失的形状
       void drawPlane();
       void drawPlaneToNull();
       void drawBullet();
       void drawBulletToNull();
       void drawEnemy();
       void drawEnemyToNull();
       //执行某一个操作
       void Playing();//游戏主循环
       void planeMove(char x);//飞机移动
       void judgePlane();//判断飞机是否与障碍物重叠
       void GameOver();//游戏失败
       void Pause();// 该成员函数用来使得游戏暂停
       void Shoot();//发射子弹
       void bulletMove();//子弹移动
       void drawThisBulletToNull(COORD c);//画出失效子弹
       void judgeEnemy();//判断子弹是否击中障碍物
       void drawThisEnemyToNull(Frame f);       //击败的障碍物清空
       void enemyMove();//障碍物移动
       void printScore();//输出分数
};

//================ 全局辅助函数实现 ================


// 这个函数用来初始障碍物的位置，
// 屏幕当中只能同时存在八架障碍物，
// 且每架障碍物用如下结构体Frame来表示，如下所示：
//     typedef struct Frame
//        {
//          COORD position[2];
//          int flag;
//        }Frame;
COORD random(COORD a, COORD b)
{
    int x = rand() % (a.X - b.X) + a.X;//保证x和y在[a.X, b.X)之间]
    int y = rand() % (a.Y - b.Y) + a.Y;
    return {static_cast<SHORT>(x), static_cast<SHORT>(y)};
}

// 这个函数用来判断一个坐标点是否在某个Frame中
bool judgeCoordInFrame(Frame frame, COORD spot)
{
    return (spot.X >= frame.position[0].X && spot.X <= frame.position[1].X &&
            spot.Y >= frame.position[0].Y && spot.Y <= frame.position[1].Y);
}

//界面颜色
void setcolor(const char* str)
{

    // 获取标准输出句柄，避免重复调用
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (strcmp(str, "lightblue") == 0) {
        // 亮蓝色 (蓝色 + 高强度)
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else if (strcmp(str, "lightred") == 0) {
        // 亮红色 (红色 + 高强度)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    } else if (strcmp(str, "lightyellow") == 0) {
        // 亮黄色 (红 + 绿 + 高强度)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    } else if (strcmp(str, "lightpink") == 0) {
        // 亮粉色 (红 + 蓝 + 高强度)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else if (strcmp(str, "blue") == 0) {
        // 标准蓝色
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    } else if (strcmp(str, "red") == 0) {
        // 标准红色
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    } else if (strcmp(str, "yellow") == 0) {
        // 黄色 (红 + 绿)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    } else if (strcmp(str, "pink") == 0) {
        // 粉色（红 + 蓝）
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
    } else if (strcmp(str, "lightgray") == 0) {
        // 亮灰色 (红 + 绿 + 蓝 + 高强度)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    } else if (strcmp(str, "gray") == 0) {
        // 暗灰色（红 + 绿 + 蓝）
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        return; // 如果没有匹配的颜色，返回
    }
}

//隐藏控制台光标
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//第二个值0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//设置光标位置到坐标（i, j）
void SetPos(int i, int j)
{
    HANDLE hout;
    COORD coord;
    coord.X = i;
    coord.Y = j;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
}

//绘制行：把第y行，[x1, x2) 之间的坐标填充为 ch
void drawRow(int y, int x1, int x2, char ch)
{
    SetPos(x1, y);
    for (int i = 0; i <= (x2 - x1); i++)
    {
        cout << ch;
    }
}

//绘制列：把第x列，[y1, y2] 之间的坐标填充为 ch
void drawCol(int x, int y1, int y2, char ch)
{
    int y = y1;
    while (y != y2 + 1)
    {
        SetPos(x, y);
        cout << ch;
        y++;
    }
}

//左上角坐标、右下角坐标、用row填充行、用col填充列
void drawFrame(COORD a, COORD  b, char row, char col)
{
    drawRow(a.Y, a.X + 1, b.X - 1, row);
    drawRow(b.Y, a.X + 1, b.X - 1, row);
    drawCol(a.X, a.Y + 1, b.Y - 1, col);
    drawCol(b.X, a.Y + 1, b.Y - 1, col);
}
//绘制矩形框架（帧）
void drawFrame(Frame frame, char row, char col)
{
    COORD a = frame.position[0];
    COORD b = frame.position[1];
    drawFrame(a, b, row, col);
}

//将结构体Frame拆开来
void drawFrame(int x1, int y1, int x2, int y2, char row, char col)
{
    COORD a = { static_cast<SHORT>(x1), static_cast<SHORT>(y1) };
    COORD b = { static_cast<SHORT>(x2), static_cast<SHORT>(y2) };
    drawFrame(a, b, row, col);
}

//================ 游戏类成员函数实现 ================

Game::Game()
{
    initPlane();
    initBullet();
    initEnemy();
    this->score = 0;
    this->rank = 25;
    this->flag_rank = 0;
}

//初始化飞机，确定飞机的构成坐标
void Game::initPlane()
{
    COORD centren;
    centren.X = 39;
    centren.Y = 21;

    // 定义各部分相对于中心0点的偏移量
    int offsets[9][2] =
    {
        {0, 0}, // position[0]
        {-2, 1}, // position[1]
        {-1,1},  // position[2]
        {0, 1},  // position[3]
        {1, 1},  // position[4]
        {2, 1}, // position[5]
        {-1, 2}, // position[6]
        {0, 2},  // position[7]
        {1, 2},  // position[8]
    };

    // 根据偏移量设置各部分的坐标
    for (int i = 0; i < 9; ++i)
    {
        position[i].X = centren.X + offsets[i][0];
        position[i].Y = centren.Y + offsets[i][1];
    }
    // 这个函数体类的代码其实就是为了初始化战机的九个部分的位置，战机的组成如下所示：
    //                     |       0
    //                   *****   12345
    //                    ***     678
}


// 该成员函数用来初始化子弹，
// 即将每个子弹的Y坐标初始化为30（bullet[i].Y = 30）来表示子弹处于失效状态
void Game::initBullet()
{
    //默认地图为80*25
    for (int i = 0; i < 10; i++)
    {
        bullet[i].Y = 30;
    }
}

//初始化敌人坐标
void Game::initEnemy()
{
    COORD a = { 1, 1 };
    COORD b = { 45, 15 };
    for (int i = 0; i < 8; i++)
    {
        enemy[i].position[0] = random(a, b);
        //  random(a, b)是调用了一个重载的函数，它表示在坐标a、b之间的矩形框
        //  内随机生成一个坐标值，并将该坐标值作为障碍物的左上角的坐标。
        // enemy[i].position[0]中是一个Frame结构体类型的变量，存放了障碍物i的左上角的坐标。
        enemy[i].position[1].X = enemy[i].position[0].X + 3;
        enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
        // enemy[i].position[1]也中是一个Frame结构体类型的变量，存放了障碍物i的右下角的坐标。
    }
    //敌人长这样一个方框
    //  --    12
    // |  |  3  4
    //  --    56
}

//绘制飞机
void Game::drawPlane()
{

    for (int i = 0; i < 9; i++)
    {
        SetPos(position[i].X, position[i].Y);
        if(i>0) {
            setcolor("yellow");
            printf("*");
        }
        else {
            setcolor("yellow");
            printf("|");
        }
    }
    //                     |       0
    //                   *****   12345
    //                    ***     678
}

// 这个成员函数通过将战机的每个坐标处输出" "来代替"0"和"|"，
// 来达到将战机消除的目的。
void Game::drawPlaneToNull()
{
    for (int i = 0; i < 9; i++)
    {
        SetPos(position[i].X, position[i].Y);
        cout << " ";
    }
}

// 该成员函数用来画出子弹
// 首先检查每颗子弹的有效性，如果子弹有效，则定位到该子弹的坐标处，输出 "^"，表示该子弹，
// 如果子弹是无效的，则不绘制
void Game::drawBullet()
{
    for (int i = 0; i < 10; i++)
    {
        if (bullet[i].Y != 30)
        {
            SetPos(bullet[i].X, bullet[i].Y);
            setcolor("lightblue");
            printf("^");
        }
    }
}




//子弹失效
void Game::drawBulletToNull()
{
    for (int i = 0; i < 10; i++)
    {
        if (bullet[i].Y != 30)
        {
            SetPos(bullet[i].X, bullet[i].Y + 1);
            printf(" ");
        }
    }
}


// 接下来要根据障碍物的左上角坐标和右下角坐标画出障碍物，
// 显然，障碍物的外形如下所示：
//   --
//  |  |
//   --
void Game::drawEnemy()
{
    for (int i = 0; i < 8; i++)
    {
        setcolor("gray");
        drawFrame(enemy[i].position[0], enemy[i].position[1], '-', '|');
    }
}

// 将障碍物消除，通过输出空白的方式
void Game::drawEnemyToNull()
{
    for (int i = 0; i < 8; i++)
    {
        drawFrame(enemy[i].position[0], enemy[i].position[1], ' ', ' ');
    }
}

//将输入的子弹坐标输出为空
void Game::drawThisBulletToNull(COORD c)
{
    SetPos(c.X, c.Y);
    cout << " ";
}

////击败的障碍物清空
void Game::drawThisEnemyToNull(Frame f)
{
    drawFrame(f.position[0], f.position[1], ' ', ' ');
}

// 该成员函数用过响应战机的一个动作
//  ↑,↓,←,→，来控制战机的移动
//上：38，下：40，左：37，右：39； 
//游戏边界为48*24
// 定义方向枚举
enum Direction { Left = 75, Right = 77, Down = 80, Up = 72 };

void Game::planeMove(char x)
{
    // 定义移动步长
    int step = 2;

    // 获取飞机的边界信息
    int leftmost = position[1].X;
    int rightmost = position[5].X;
    int topmost = position[5].Y;
    int bottommost = position[7].Y;

    // 根据按键调整飞机位置
    switch (static_cast<Direction>(x))
    {
        case Direction::Left: // 左键
            if (leftmost > 1)
            {
                for (int i = 0; i < 9; i++)
                {
                    position[i].X -= step;
                }
            }
            break;

        case Direction::Right: // 右键
            if (rightmost < 47)
            {
                for (int i = 0; i < 9; i++)
                {
                    position[i].X += step;
                }
            }
            break;

        case Direction::Down: // 下键
            if (bottommost < 23)
            {
                for (int i = 0; i < 9; i++)
                {
                    position[i].Y += 1;
                }
            }
            break;

        case Direction::Up: // 上键
            if (topmost > 2)
            {
                for (int i = 0; i < 9; i++)
                {
                    position[i].Y -= 1;
                }
            }
            break;
    }
}

// 这个成员函数用来响应一次射击操作，
// 也就是，当游戏中的时候，玩家按下"k"键，就执行该函数。
// 由于子弹是由COORD bullet[10]定义的，因此同一时刻，界面内只能有10颗子弹同时出现。
// 如果界面内不够10颗子弹，按下"k"键后战机应该发射出一颗子弹，
// 于是，依次遍历10颗子弹，当遇到第一颗失效的子弹后，
// 立即将该子弹赋予新的坐标（战机的炮口，也就是（position[5].X，position[5].Y - 1）），
// 让其激活。然后退出for循环，函数执行完毕。
void Game::Shoot()
{
    for (int i = 0; i < 10; i++)
    {
        if (bullet[i].Y == 30)
        {
            bullet[i].X = position[0].X;
            bullet[i].Y = position[0].Y - 1;
            break;
        }
    }
}

// 此成员函数用来响应一次子弹的运动
// 每次子弹运动，屏幕子弹的坐标都会出现变化，即
// 先判断子弹是否有效（即判断语句if (bullet[i].Y != 30)），
// 若子弹有效，将该子弹的Y坐标减少1，X坐标不变，
// 检测子弹坐标更改之后是否达到上边界，如果达到上边界，则将该子弹从屏幕上擦除，
// 同时，将该子弹置为失效状态，即 bullet[i].Y = 30。
void Game::bulletMove()
{
    for (int i = 0; i < 10; i++)
    {
        if (bullet[i].Y != 30)
        {
            bullet[i].Y -= 1;
            if (bullet[i].Y == 1)
            {
                COORD pos = { bullet[i].X, static_cast<SHORT>(bullet[i].Y + 1) };
                drawThisBulletToNull(pos);
                bullet[i].Y = 30;
            }
        }
    }
}


// 该成员函数用来响应一次障碍物的移动
// 界面上必须同时出现八架障碍物，因此，
// 如果有某架障碍物运动到下边界处，则重置该障碍物的坐标
void Game::enemyMove()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 2; j++)
            enemy[i].position[j].Y++;
        // 我们将每架障碍物的左上角和右下角坐标的Y值增加1，
        // 表示该障碍物向下走了一个距离
        
        // 检测向下走一个距离后的障碍物的右下角坐标的Y值是否达到24，
        // 如果达到，代表障碍物已经运动到下边界了，
        // 此时需要随机重置该障碍物的坐标
        if (enemy[i].position[1].Y==24)
        {
            //战机在区间ab中随机生成一个战机的坐标
            COORD a = { 1, 1 };
            COORD b = { 45, 3 };
            enemy[i].position[0] = random(a, b);
            enemy[i].position[1].X = enemy[i].position[0].X + 3;
            enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
        }
    }
}


// 该成员函数用来判断战机是否坠毁，
// 依次判断每架障碍物与战机的每个部分是否有接触，
// 如果有接触，则表示战机坠毁
void Game::judgePlane()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 9; j++)
            // 此处的实参position[j]是指战机的10个部分的COORD坐标，
            // 类中的成员函数可以访问数据成员变量。
            // 此处也可以写成this-> position[j]，因为
            // 成员函数具有一个附加的隐含形参，即指向该类对象的一个指针，
            // 这个隐含形参命名为this，与调用成员函数的对象绑定在一起。
            // 成员函数不能定义this形参，而是由编译器隐含地定义。
            // 成员函数的函数体可以显式使用this指针，但不是必须这么做。
            if (judgeCoordInFrame(enemy[i], position[j]))
            {
                SetPos(61, 2);
                printf("  坠毁      ");
                setcolor("yellow");
                drawFrame(enemy[i], '+', '+');
                // 将与战机相撞的障碍物的形状绘制为:
                //    ++
                //   +  +
                //    ++
                Sleep(1000);
                GameOver();
                break;
            }
    }
}


// 该成员函数依次遍历每一架障碍物障碍物，
// 将每一架障碍物依次与每一颗子弹进行检测，
// 判断障碍物是否与子弹有接触，如果有接触，则表示击中障碍物，
// 此时将障碍物和子弹擦除，然后在界面顶部的位置处随机生成一架障碍物
void Game::judgeEnemy()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (judgeCoordInFrame(enemy[i], bullet[j]))
            {
                score += 5;
                drawThisEnemyToNull(enemy[i]);
                COORD a = { 1, 1 };
                COORD b = { 45, 3 };
                enemy[i].position[0] = random(a, b);
                enemy[i].position[1].X = enemy[i].position[0].X + 3;
                enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
                drawThisBulletToNull(bullet[j]);
                bullet[j].Y = 30;
            }
        }
    }
}


// 该成员函数用来使得游戏暂停
void Game::Pause()
{
    SetPos(61, 2);
    cout << "         ";
    SetPos(61, 2);
    cout << "暂停中...   ";
    // 当出现"暂停中..."的提示以后，程序不停的接收按下的按键，
    // 当按下'p'键以后，说明要退出暂停状态，此时需要清除"暂停中..."的提示
    // 通过输出空白 "         "来将其覆盖，达到效果
    char c = _getch();
    while (c != 'p')
    {
        c = _getch();
    }
    SetPos(61, 2);
    cout << "         "; 
    setcolor("green");
    SetPos(61, 2);
	cout << "飞机大战"; 
    
}


//游戏结束
void Game::GameOver()
{
	setcolor("lightgreen");
    system("cls");
    COORD p1 = { 28,9 };
    COORD p2 = { 53,15 };
    drawFrame(p1, p2, '=', '|');
    SetPos(36, 12);
    string str = "Game Over!";
    for (int i = 0; i < str.size(); i++)
    {
        Sleep(80);
        cout << str[i];
    }
    Sleep(1000);
    system("cls");
    drawFrame(p1, p2, '=', '|');
    SetPos(31, 11);
    setcolor("blue");
    cout << "击毁障碍物：" << score / 5 << "个";
    SetPos(31, 12);
    cout << "得　　分：" << score;
    SetPos(31, 13);
    cout << "获得称号：" << title;
    SetPos(30, 18);
    Sleep(1000);
    setcolor("green");
    cout << "继续？ 是（Y）| 否（N）";
as://goto 语句标签 直接跳转至此
    char x = _getch();
    if (x == 'n' || x == 'N')
    {
        exit(0);
    }
    else if (x == 'y' || x =='Y')
    {
        system("cls");
        Game game;
        int a = drawMenu();       // 绘制游戏开始界面主菜单
        if (a == 2)
            game.rank = 20;
        system("cls");
        drawPlaying();           // 绘制游戏界面框架
        game.Playing();
    }
    else 
        goto as;
}

void Game::printScore()
{
    if (score <= 100)
    {
        flag_rank = 1;
    }
    else if (score > 100 && score <= 320)
    {
        flag_rank = 2;
    }
    else if (score > 320 && score <= 440)
    {
        flag_rank = 3;
    }
    else if (score > 440)
    {
        flag_rank = 4;
    }
    SetPos(60, 6);
    cout << score;
    SetPos(60, 7);
    if (flag_rank == 1)
    {
        title = "初级飞行员";
    }
    else if (flag_rank == 2)
    {
        title = "中级飞行员";
    }
    else if (flag_rank == 3)
    {
        title = "高级飞行员";
    }
    else if (flag_rank == 4)
    {
        title = "王牌飞行员";
    }
    cout << title;
}

// 这个成员函数是游戏的主循环函数，
// 定义了整个游戏过程。
void Game::Playing()
{
    drawEnemy();
    drawPlane();
 
    int flag_bullet = 0;
    int flag_enemy = 0;
 
    while (true)
    {
        Sleep(20);
        // 函数名：kbhit()（VC++6.0下为_kbhit()）
        // 功能及返回值： 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
        // 用法：int kbhit(void);
        // 包含头文件： include <conio.h>
        // kbhit()在执行时,检测是否有按键按下,有按下返回非0值，没有按下则返回0，是非阻塞函数；
        // 不同于getch()的在执行时, 检测按下什么键, 如果不按键该函数不返回，也就不进行下一步操作，是阻塞函数。
        if (_kbhit())
        {
            char x = _getch();
            // getch()是编程中所用的函数，这个函数是一个不回显函数，
            // 当用户按下某个字符时，函数自动读取，无需按回车
            // getch()并非标准C中的函数，不存在C语言中。
            // 所在头文件是conio.h，而不是stdio.h。
            // 用ch = getch(); 会等待你按下任意键之后，把该键字符所对应的ASCII码赋给ch, 再执行下面的语句。
            if (75 == x || 80 == x || 77 == x || 72 == x)
            {
                drawPlaneToNull();     // 将战机先擦除
                planeMove(x);          // 根据所输入的操作符，对战机的坐标进行更改
                drawPlane();           // 访问类中的数据成员——战机的坐标，在新的坐标处重新绘制战机
 
                judgePlane();          // 判断战机是否有坠毁
            }
            //  在某一循环当中，如果检测到有'p'键按下，
            // 首先在右侧游戏界面输出"暂停中..."，然后陷入while()循环一直等待'p'键再次按下，
            // 如果'p'键没有按下，就一直处在while()循环内，因此不能执行后面的程序，起到暂停的效果。
            else if ('p' == x)
            {
                Pause();
            }
            // 如果是检测到空格键按下，则运行Shoot()函数，
            else if (32 == x)
            {
                Shoot();
            }
            // 如果是检测到'k'键按下，则运行GameOver()函数，
            // GameOver()函数执行完毕后，执行break;语句跳出while循环（注意不是if (_kbhit())）。
            // break语句用于结束最近的while、do while、for或switch语句，并将程序的执行权传递给紧接在
            // 被终止语句之后的语句。
            else if ('e' == x)
            {
                //CloseHandle(MFUN)
                GameOver();
                break;
            }
        }
        // 接下来处理子弹
        // 判断子弹状态的程序一直在运行
        if (flag_bullet == 0)
        {
            bulletMove();           // 更新界面上有效子弹的坐标
            drawBulletToNull();     // 将处于旧坐标的子弹擦除
            drawBullet();           // 绘制出新坐标上的子弹
            judgeEnemy();          // 判断障碍物是否被子弹击中
        }
        flag_bullet++;
        if (flag_bullet==1)
        {
            flag_bullet = 0;
        }
        //  接下来处理障碍物
        if (flag_enemy==0)
        {
            drawEnemyToNull();     // 将所有的障碍物都擦除
            enemyMove();           //  更新障碍物的坐标
            drawEnemy();           // 绘制出处于新坐标上的障碍物
            judgePlane();          // 判断障碍物是否与战机接触
        }
        flag_enemy++;
        if (flag_enemy >= rank)
        {
            flag_enemy = 0;
        }
        /* 输出得分 */
 
        printScore();
    }
}

//================ 界面绘制函数 ================

//主菜单绘制
int drawMenu()
{
    setcolor("lightgreen");
    system("Title        飞 机 大 战");
    SetPos(30,1);
    cout << "飞 机 大 战";
    drawRow(3, 0, 79, '-');
    drawRow(5, 0, 79, '-');
    SetPos(28, 4);
    setcolor("red");
    cout << "↑和↓选择，回车确定";
    int j = 11;
    SetPos(12, j);
    cout << ">>";
    SetPos(15, 11);
    cout << "1. 简单的任务";
    SetPos(15, 13);
    cout << "2. 困难的任务";
    drawRow(20, 0, 79, '-');
    SetPos(47, 11);
    setcolor("yellow");
    cout << "简单的任务：";
    SetPos(51, 13);
    cout << "简单任务的自动飞行速度较慢，任务难度较小。                  ";
    SetPos(30, 21);
    setcolor("lightblue");
    cout << "纳米核心";
    setcolor("red");
    drawRow(22, 0, 79, '-');
 
    while (true)
    {
        if (_kbhit())
        {
            char x = _getch();
            switch (x)
            {
            case 72:
            {
                if (j == 13)
                {
                    SetPos(12, j);
                    cout << "  ";
                    j = 11;
                    SetPos(12, j);
                    setcolor("red");
                    cout << ">>";
                    SetPos(51, 13);
                    cout << "　　　　　　　　　　　　";
                    SetPos(47, 11);
                    setcolor("yellow");
                    cout << "简单的任务：";
                    SetPos(51, 13);
                    cout << "简单任务的自动飞行速度较慢，任务难度较小。                  ";
                }
                break;
            }
            case 80:
            {
                if (j == 11)
 
                {
                    SetPos(12, j);
                    cout << "　";
                    j = 13;
                    SetPos(12, j);
                    setcolor("red");
                    cout << ">>";
                    SetPos(51, 13);
                    cout << "　　　　　　　　                 　　　　　　";
                    SetPos(47, 11);
                    setcolor("yellow");
                    cout << "困难的任务：";
                    SetPos(51, 13);
                    cout << "困难任务自动飞行速度较快，难操作哟！                         ";
                }
 
                break;
            }
            case 13://回车键：13 
            {
                
                if (j == 11)//源代码为8？
                    return 1;
                else
                    return 2;
            }
            }
        }
    }
 
    return 0;
}

// 绘制游戏界面
void drawPlaying()
{
	setcolor("red");
    drawFrame(0,  0, 48, 24, '=', '|');//    draw map frame主界面
    drawFrame(49, 0, 82, 4, '-', '|');//    draw output frame 状态界面
    drawFrame(49, 4, 82, 9, '-', '|');//    draw score frame 分数界面
    drawFrame(49, 9, 82, 20, '-', '|');//    draw operate frame 操作界面
    drawFrame(49,20, 82, 24, '-', '|');//    draw other message frame 提示界面
    setcolor("yellow") ;
    SetPos(61,2);
	cout << "飞机大战" ; 
    SetPos(52, 6);
    cout << "得分：";
    SetPos(52, 7);
    cout << "称号：";
    SetPos(52, 11);
    setcolor("yellow") ;
    cout << "操作方式：";
    SetPos(52, 13);
    cout << "↑,↓,←,→可以控制战机移动。";
    SetPos(52, 15);
    cout << "P和E分别可以暂停游戏或退出游戏。";
    SetPos(52, 17);
    cout << "空格可以发射燃烧弹";
    SetPos(52, 19);
    cout << "你的任务是躲避障碍物并击毁它们!";
    SetPos(52, 22);
    setcolor("lightblue") ;
    cout << " 游戏虽好玩，不要贪多哦 ";
}

//================ 主函数 ================

int main()
{
    cout << "\t\t****飞机大战游戏正在准备****\n";
    cout << "\n已加载 0%";
    for (int i = 0; i < 9; i++)
    {
        SetPos((i + 1) * 2 - 1, 1);
        cout << "■ ";
        SetPos(7 - 1, 3 - 1);
        cout << i + 1;
        Sleep(200);
    }
    Sleep(200);
    SetPos(19, 1);
    cout << "■ \n已加载100%";
    Sleep(200);
    system("cls");
    srand((unsigned int)time(NULL));
    HideCursor();
    Game game;
    int a = drawMenu();
    if (a == 2)
    {
        game.rank = 20;
    }
    system("cls");
    HideCursor();
    drawPlaying();
    game.Playing();
    return 0;
}