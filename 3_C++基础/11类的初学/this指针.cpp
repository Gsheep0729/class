#include <iostream>
#include <cstring>
using namespace std;

class Counter
{
public:
    Counter(int num = 0) // 区分作用域
    {
        this->num = num;
    }
    Counter add() // 返回调用对象本身
    {
        ++num; // num+=1
        cout << "num = " << num << endl;
        // 返回值 this类型 Counter *
        // this指向调用对象  *this就是调用对象自身
        return *this;
    }
    int num;
};

int main()
{
    Counter cn(1);
    cn.add().add().add();

    return 0;
}