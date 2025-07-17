//扑克牌随机生成器
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    const char *num[13] ={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    const char *color[4] ={"梅花","方塊","红桃","黑桃"};
    srand((time(NULL)));
    printf("随机抽10张牌：\n");
    for(int i=0;i<10;i++)
    {
        printf("%s%s\n", color[rand()%4], num[rand()%13]);
    }
    
    return 0;
}