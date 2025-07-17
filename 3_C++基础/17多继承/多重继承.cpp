
#include <iostream>
using namespace std;

class Dingyuan
{
protected:
    void fun_dy()
    {
        cout << "丁原" << endl;
    }
    Dingyuan()
    {
        cout << "丁原" << endl;
    }
    void aim()
    {
        cout << "统一西凉" << endl;
    }
};

class Dongzhuo
{
protected:
    void fun_dz()
    {
        cout << "董卓" << endl;
    }
    Dongzhuo()
    {
        cout << "董卓" << endl;
    }
    void aim()
    {
        cout << "把持朝纲" << endl;
    }
};

class Wangyun
{
protected:
    void fun_wy()
    {
        cout << "王允" << endl;
    }
    Wangyun()
    {
        cout << "王允" << endl;
    }
    void aim()
    {
        cout << "拯救大汉" << endl;
    }
};

class lvbu : public Wangyun, public Dingyuan, public Dongzhuo
{
public:
    void introduce()
    {
        cout << "我的义父有：" << endl;
        fun_dy();
        fun_dz();
        fun_wy();
        // aim();//error 基类中存在多个aim()同名函数，存在歧义问题
        Dingyuan::aim();
        Dongzhuo::aim();
        Wangyun::aim();
    }
};
int main()
{
    lvbu l;
    l.introduce();

    // // 向上造型
    // Dingyuan *dy = l;

    // lvbu l2;
    // // 向上造型
    // Dongzhuo &dz = l2;
    // Wangyun *wy = &l2;

    return 0;
}