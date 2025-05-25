//字母替换加密
#include <iostream>
using namespace std;
#define key  4
int main()
{
    char str[100];
    cout << "请输入100位以内的字符串(避免空格)：\n";
    cin >> str;
    //for(int i=0;i < 100;i++)// 循环遍历
    for (int i=0;str[i]!='\0';i++)
    {
        if(str[i]<='z' &&  str[i]>='a')// 小写
        {
            str[i]=str[i] + key;// 向加密key位
            if(str[i]>='z')// 以a~z为界，超过则减去26
            {
            str[i]=str[i]-'z'+'a';
            }
        }
        else if(str[i]<='Z' &&  str[i]>='A')// 大写
        {
            str[i]=str[i] + key;
            if(str[i]>='Z')// 以A~Z为界，超过则减去26
            str[i]=str[i]-'Z'+'A';
        }
        /*else if(str[i]<='9' &&  str[i]>='0')// 数字加密
        {
            str[i]=str[i] + key;
            if(str[i]>='9')// 以0~9为界，超过则减去10
            str[i]=str[i]-'9'+'0';
        }*/
        else
        {
            continue;
        }
    }
    cout <<str<< endl;
    return 0;
}