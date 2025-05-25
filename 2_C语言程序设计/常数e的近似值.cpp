//求常数e的近似值
#include <iostream>
using namespace std;

int main()
{
    double num = 1,e = 1;
    for (int i = 1; i <= 100; i++)
    {
        num = num * i;
        e += 1.0 / num;
    }
    cout <<"e≈" <<e << endl;
    
    
    return 0;
}