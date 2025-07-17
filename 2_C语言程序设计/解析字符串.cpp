/*写一个函数GetDate，
用于从用户处读入形如:dd-mmm-yy的日期，
其中ad是一个一位数或两位数的日，mmm是月份的三个字母的缩写，yy是一个两位数的年份。
你写的函数应该读入日期的各部分，并将它们以数字形式赋给三个参数，这三个参数都通过引用传递*/
#include <iostream>
#include <cstring>
using namespace std;
void GetDate(int *dp,int *mp,int *yp)//参数通过引用传递
{
    printf("日期为:%d年%d月%d日",*yp,*mp,*dp);
}

int main()
{
    //定义月份数组
    const char* months[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char data[10],monthstr[4];//以字符形式存储用户输入的日期和解析出来的月份
    int day=0,month=0,year=0;//以数字形式存储日期的各部分
    cout<<"请输入日期(dd-mmm-yy):";
    scanf("%10s",data);//读入日期
    sscanf(data,"%d-%3s-%d",&day,(char *) monthstr,&year);//解析日期
    for(int i=0;i<12;i++)//遍历月份数组，找到月份
    {
        if (strcmp(monthstr, months[i]) == 0)
        {
            month=i+1;
            break;
        }
    }
    GetDate(&day,&month,&year);//调用GetDate函数

    
    return 0;
}