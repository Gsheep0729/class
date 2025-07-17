//多文件编程时编译的命令：编译多文件程序的时候需要在g++命令后列出所有源文件的路径
#include <iostream>
#include <string>
/*main与test1.h文件不在同一个目录下，需要使用相对路径，即test1.h文件所在目录的相对路径*/
#include "test1.h"
int num;
using namespace std;
int d = 10;
int main()
{
    print();
    int b,c;
    cout << "请输入两个数：" << endl;
    cin >> b >> c;
    int a = test1(b, c);
    std::cout << a << std::endl;
    std::cout << "&num = " << &num << "---by main" << std::endl;
    setValue();
    std::cout << "num = " << num << std::endl;
    return 0;

}