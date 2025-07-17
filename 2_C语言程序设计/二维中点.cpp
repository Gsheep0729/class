/*编写函数Midpoint(pl，p2)，返回p1和p2之间线段的中点*/
#include <iostream>
using namespace std;
typedef struct
{
    double x, y;
} pointT;
// 修改Midpoint函数以接受两个pointT类型的参数
pointT Midpoint(pointT p1,pointT p2)
{
    pointT p = {0, 0};
    p.x = (p1.x + p2.x) / 2;
    p.y = (p1.y + p2.y) / 2;
    return p; // 计算x坐标的中点
}
int main()
{
    pointT p1 = {1, 2}; // 创建两个pointT类型的变量
    pointT p2 = {3, 4};
    cout << "中点坐标为(" << Midpoint(p1, p2).x << "," << Midpoint(p1, p2).y << ")" << endl;
    return 0;
}