/*用柱状图显示这些数字，范围为0~9，10~19，20~29，等等，范围最大为100*/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int n, min = 0, max= 9;
    cout << "数据为:100,95,47,88,86,92,75,89,81,70,55,80 "<<endl;;
    cout << "---------------------------------------------------------" << endl;
    int num[12] = {100, 95, 47, 88, 86, 92, 75, 89, 81, 70, 55, 80};
    for(int i = 0; i < 10; i++)//遍历各范围
    {
        cout << setw(4) << right << min <<" ~ " << setw(4) << left << max << "|";//输出范围
        for(int j = 0; j < 12; j++)//遍历找出各范围的数字个数
        {
            if(num[j] >= min && num[j] <= max)//判断是否在范围内
            {
                cout << "*";//打印各范围的条形图
            }
        }
        min+= 10;
        max+= 10;
        cout << endl;
    }
    cout <<"      100  |";//单独判断100
    for(int i = 0; i < 12; i++)
    {
        if(num[i] == 100)
        {
            cout << "*"<<endl;
        }
        

    }
    
    return 0;
}