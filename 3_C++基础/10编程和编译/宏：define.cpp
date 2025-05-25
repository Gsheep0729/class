/*宏函数命名之间不能用大写，宏函数的副作用：
不要把自增或自减的结果作为宏的参数使用
*/
#include <iostream>
#include <string>
using namespace std;
/*define将文本进行替换，并不考虑优先级*/
#define gy(a,b)  a*b
#define GY(a,b)  (a)*(b)

int main()
{
    //1*2=2
    cout <<"a*b = 1*2 = "<<gy(1,2)<< endl;
    //2-1*3-1=-1
    cout <<"a*b = 2-1*3-1 = "<<gy(2-1,3-1)<< endl;
    //(2-1)*(3-1)=-1*/
    cout <<"(a)*(b) = (2-1)*(3-1) = "<<GY(2-1,3-1)<< endl;
    return 0;
}