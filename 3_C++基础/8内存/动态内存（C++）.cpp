/*C++动态内存分配使用 new，原理和malloc完全相同，表示申请一块相应类型相应长度的内存*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
int main()
{ 
    int a = 0;
    cout << "请输入人数";
    cin >> a ;
    int *age = new int[a];
    /*如果a=1,可省略为*/
    /*int *age = new int[a]*/
    if(age == NULL)
    {
        cout <<"申请空间失败" <<endl;
        return -1;
    } 
    for(int b=0;b >= 0;b++)
    {
        cout << age[b] << endl;
    }
    /*释放内存*/
    //int *p = new int/*[1]*/;
    //delete /*[]*/p;  []省略同上
    delete[] age;


return 0;
}