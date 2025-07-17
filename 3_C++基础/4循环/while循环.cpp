#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int a = 0;
    cout<<"while:";
    while( a < 7 )
    //括号内只写条件
    {
        cout<< " a="<< a << endl;
        a++;
    }
    cout<<"for:";
    for(int a =0/*局部变量*/;a<7;a++)
    {
        cout<< " a="<< a << endl; 
    }
    

    return 0;
}