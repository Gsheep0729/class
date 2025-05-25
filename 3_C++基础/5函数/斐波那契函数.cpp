//用递归和循环两种方式输出斐波那契额数列前30项
//1 1 2 3 5 8 13 
#include <iostream>
using namespace std;
//递归：一个函数多次自我利用
int GY(int a)
{
    if(a <= 2)
    {
        return 1;
    }
    return GY(a-1) + GY(a-2);//a3=a1+a2,a4=a2+a3=a2+(a1+a2),a5=a3+a4=(a1+a2)+(a2+a3)
}
//函数循环：多次利用函数，利用一次打印一次
int fuck(int a )
{
    int b = 1;
    int c = 1;
    int g = 0;
    
    //while用于不知道循环次数，但知道条件，将满足条件的都循环执行（找到结果数据）
    //当类型
    //while(  c >= a && c <=b )
    
    //{
    //     cout<< "此时c="<< c << endl;
    //   c++;
    //   return 0;
    //}
    //for用于知道循环次数，重复执行满足次数内循环（处理数据）
    //直到类型
    if(a <= 2)
    {
        return 1; 
    }
    //for(int f = 3;f <=a ;f++)//等效while

    int f  = 3 ;
    while(f <= a)
    {
        g = b + c;//第一项b,第二项c
        c = b;//c成了第二项
        b = g;//b成了第三项
        f++;

    }
    return g ;
}

int main()
{
    cout <<"GY fuck"<<endl;
    for(int a =1;a <= 10 ;a++)//a为函数里的参数，a的意义：斐波那契额数列的第a个
    //用for语句重复输出每一个条件内的结果
    {
        cout << fuck(a) << "    " << GY(a)<<endl;
    }
    //cout << "那什么数依次=" << d << endl;只能输出数列的第几个
    return 0;
}
