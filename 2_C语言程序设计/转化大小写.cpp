/*实现一个函数Capitalize(str)，它返回一个首字符是大写的(如果是字母)，
其他所有字母都转换成小写的字符串，其他字符不受影响。
例如，Capitalize("BOOLEAN")和Capitalize("boolean")应该都返回字符串"Boolean"*/
#include <iostream>
using namespace std;
char Capitalize(char str)//无论大小写都进行切换
{
    if (str >= 'A' && str <= 'Z') 
    {
        return str + ('a' - 'A'); // 将大写字母转换为小写字母
    } 
    else if (str >= 'a' && str <= 'z') 
    {
        return str - ('a' - 'A'); // 将小写字母转换为大写字母
    } 
    else 
    {
        return str; // 如果不是字母，则保持不变
    }
}

int main() 
{
    char str[15];
    printf("请输入一个15位以内的字符串，只包含字母和数字，不包含空格: \n");
    scanf("%s", str);// 输入字符串
    printf("原字符串: %s\n", str);
    if(str[0] >= 'a' && str[0] <= 'z')// 使首字母为大写字母
    {
        str[0] = Capitalize(str[0]);
    }
    for (int i = 1; str[i] != '\0'; i++)//遍历所有字符
    {
        if(str[i] >= 'a' && str[i] <= 'z')//使其他字母转换为小写字母
        {
            continue;
        }
        else
        {
            str[i] = Capitalize(str[i]);
        }
    }

    printf("转换后的字符串: %s\n", str);

    return 0;
}