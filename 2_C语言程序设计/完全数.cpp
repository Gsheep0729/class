//完全数：一个数的全部的因子之和等于该数本身。
#include <iostream>
using namespace std;
void IsPerfect()
{
    int n;
    cout << "请输入一个要判断是否为完全数的正整数：" << endl;
    cin >> n;
    int i = 1;
    int sum = 0;
    while (i < n)//找出这个数的全部约数并相加
    {
        if (n % i == 0)
        {
            sum += i;
        }
        i++;
    }
    if (sum == n)
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }

}
int main() 
{
    IsPerfect();
    

    return 0;
}