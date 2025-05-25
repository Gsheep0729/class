/*写一个函数Reversesting(carray)，使参数中的字符倒序排列*/
#include <iostream>
using namespace std;
void Reversesting(char *carray)
{
    int i = 0, j = 0;
    char temp;
    while (carray[i] != '\0')
    {
        i++;
    }
    i--;
    while (i > j)
    {
        temp = carray[i];
        carray[i] = carray[j];
        carray[j] = temp;
        i--;
        j++;
    }
    cout << carray << endl;
}

int main()
{
    char carray[20] = "hello world!";
    Reversesting(carray);
    return 0;
}