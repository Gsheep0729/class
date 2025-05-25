/*回文(palindrome)是一个正读和反读都完全一样的单词，
如level或noon。写一个谓词函数IsPalindrome(str)，如果字符串str是回文
，则返回TRUE。此外，设计并写一个测试程序，它调用IsPalindrome来验证其正确性。
在写此程序时，要关注如何简单地解决问题，而不是使你的解决方案更有效。*/
#include <iostream>
#include <cstring>
using namespace std;
int IsPalindrome(char str[])
//int IsPalindrome(char* str)
{
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right)//从两边往中间判断
    {
        if (str[left] != str[right])//不相等，不是回文
        {
            break;//判断为非回文则停止判断

        }
        left++;
        right--;
    }
    if (left >= right)//判断是否是回文
    {
        cout << "是回文" << endl;

    }
    else
    {
        cout << "不是回文" << endl;

    }
    return 0;
}

int main()
{
    char str[20];
    cout << "请输入一个20位以内的字符串：\n";
    scanf("%s",str);
    /*IsPalindrome 函数的参数类型定义为 char，而实际传入的是 char * 类型的字符串。
    C++ 不允许将 char * 类型的参数传递给 char 类型的形参。*/
    IsPalindrome(str);
    return 0;
}