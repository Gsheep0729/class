#include <iostream>
#include <cstring>
int main()
{
    char a [999] = "";//要优先定义足够长能存放得下的字符串
    //std::string a = "";//两种都可
    std::cout << "请输入：" ;
    std::cin >> a ;
    int c = 0 ;
    int d = 0 ;
    for(int b = 0 ; b < strlen(a); b++)
    /*上面有个个问题，我现在解决不了→5行
    for(int b = 0 ; b < a.length();b++)
    char->strlen必须要有“#include <cstring>”头文件，另一种就不需要
    a-变量，b-位置，c-提取的数字，d-输出的结果*/
    {
        if( a[b] >= '0' && a[b] <= '9')
        {
            c =  c * 10 + (a[b]-'0');
            //-'0'是为了字符变数字而运算
        }
        else
        {
            d += c;
            c = 0 ;
            
        }
    }
     if (c != 0)
    {
        // 有可能字符串以数字结尾，导致最后一个数字未被计算进去
        d += c;
    }
    std::cout << "数字相加结果：" << d << std::endl;
    //std::cout << "数字相加结果：" << d+c << std::endl;
    //字符串末尾为数字时，储存在if中
    return 0;
}