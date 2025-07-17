/*串的模式匹配（BF和KMP算法）*/
#include <iostream>
#include <cstring>
using namespace std;

int BF(char *s, char *t) //BF算法
{
    int i = 0, j = 0;//i为主串的索引，j为模式串的索引
    while (i < strlen(s) && j < strlen(t))
    {
        if (s[i] == t[j])//从头开始匹配
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;//主串回溯
            j = 0;
        }
    }
    if (j == strlen(t)) return i - j + 1;
    else return -1;
}

//求出next数组的值
void get_next(char *t,int *next)
{
    int j = 0, k = -1;//j为模式串的索引，k为最大公共前后缀的长度
    int len = strlen(t);
    next[0] = -1;
    while (j < len - 1)//遍历模式串t
    {
        if (k == -1 || t[j] == t[k])//第一个字符不匹配，返回到第一个字符继续||匹配成功，继续匹配下一个字符
        {
            j++;//妙处在于j不回溯
            k++;
            next[j] = k;//next[j]表示模式串t[j]的后缀的最长匹配前缀的长度
        }
        else
            k = next[k];//匹配失败，k回溯到前一个位置
    }
}

//求出nextval数组的值
void get_Nextval(char *t, int *next, int *nextval)
{
    nextval[0] = -1;                      // 初始化第一个位置
    int len = strlen(t);
    for (int j = 1; j < len; j++)// 从j=1开始遍历模式串
    {
        if (t[j] == t[next[j]])           // 当前字符与next[j]位置的字符相同
            nextval[j] = nextval[next[j]];// 直接继承nextval[next[j]]的值
        else
            nextval[j] = next[j];        // 否则保留next[j]的值
    }
}

//KMP算法
int KMP(char *s, char *t, int *nextval) {
    int i = 0, j = 0;
    int len_s = strlen(s), len_t = strlen(t);
    while (i < len_s && j < len_t) {
        if (j == -1 || s[i] == t[j]) {
            i++;
            j++;
        } else {
            j = nextval[j];
        }
    }
    if (j >= len_t) return i - j + 1; // 返回位置（下标从1开始）
    return -1;
}

int main()
{
    char s[] = "abcabcdabcdeabcdefabcdefg";
    char t[] = "abcdeabcdefab";
    cout << "BF算法中,t在s的第:" << BF(s, t) <<"个位置"<< endl;

    //生成next
    int len_t = strlen(t);
    int *next = new int[len_t];
    get_next(t, next);

    //生成nextval
    int *nextval = new int[len_t];
    cout << "KMP算法中,t在s的第:" << KMP(s, t, nextval) <<"个位置"<< endl;
    
    return 0;
}