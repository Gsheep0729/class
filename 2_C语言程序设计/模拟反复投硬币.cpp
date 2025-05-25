//模拟反复投硬币，直到连续出现三个正面为止
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int random()
{
    srand(time(0));
    return rand() % 2;
}
int main()
{
    printf("现在开始一直投硬币直到累计3个正面停止:\n");
    //srand(time(0));
    int count = 0,result,total=0;
    while (result != 0 || count < 3)
    {
        result = random() % 2;
        if (result == 0)
        {
            cout << "正面";
            count++;
        }
        else
        {
            cout << "反面";
            count = 0;
        }
        total++;
        cout << " ";
    }

    printf("\n一共抛了%d次",total);
    
    
    return 0;
}