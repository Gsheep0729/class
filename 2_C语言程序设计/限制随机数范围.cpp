//限制随机数范围
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int random(int low, int high)//限制随机数的范围
{
    /*确保随机数的范围是偶数*/
    if(low > high)
    {
        return random(high, low);
    }
    if(low%2 == 1)
    {
        low = low + 1;
    }
    if(high%2 == 1)
    {
        high = high - 1;
    }
    int k;
    double d;
    d = (double)rand() / RAND_MAX/2;//获得一个[0,1]的随机数
    k = (int)(d * (high - low ) )*2 + low ;//
    return k;
}
int main()
{
    srand(time(NULL));
    printf("输出10个(2,100)的偶随机数:\n");
    // int a, b;
    // cout << "请输入两个整数来限制随机数的范围(a,b): "<<endl;
    // cin >> a >> b;
    for (int i = 0; i < 10; i++)
    {
        cout << random(2,100) << " " ;
    }
    return 0;

}