#include <iostream>
using namespace std;

// 前置声明
class Child;
//--------------------------------------声明-------------------------------------
// 母亲类：被观察者
class Mother
{
public:
    Mother();
    ~Mother();
    // 添加观察者
    void AddChild(Child *c);
    // 移除观察者
    void DelChild(Child *c);
    // 通知
    void Notify(string action);

private:
    // Child list[10];//1
    // 一个被观察者：可以拥有多个观察者。
    Child *list[10]; // 2比较合适 数组固定长度 有效/无效的孩子数据（NULL）  指针数组（数组）栈区
};

// 父亲类：被观察者
class Father
{
public:
    Father();
    ~Father();

    void AddChild(Child *c);    // 添加观察者
    void DelChild(Child *c);    // 移除观察者
    void Notify(string action); // 通知
private:
    // 一个被观察者：可以拥有多个观察者。
    Child *list[10]; // 目前我们通过数组来实现观察者集合
};

// 观察者
class Child
{
public:
    Child(string name);
    ~Child();
    string getName();

    // 状态切换的接口
    void Updata(string action);

private:
    // 名字区分
    string m_name;
};

//--------------------------------------实现-------------------------------------
Mother::Mother()
{
    for (int i = 0; i < 10; i++)
    {
        list[i] = NULL;
    }
}

Mother::~Mother(){}

// 添加观察者
void Mother::AddChild(Child *c)
{
    // 遍历孩子数组，找一个空位置来添加
    for (int i = 0; i < 10; i++)
    {
        // 判断当前的位置是否为空
        if (list[i] == NULL)
        {
            list[i] = c; // 添加观察者
            cout << c->getName() << "被添加到了观察者集合" << endl;
            break;
        }
    }
}

// 移除观察者
void Mother::DelChild(Child *c)
{
    // 遍历孩子数组，找一个到需要移除的观察者
    for (int i = 0; i < 10; i++)
    {
        // 判断当前的位置是否和c指针指向同一个空间
        if (list[i] == c)
        {
            cout << list[i]->getName() << "被移除了观察者集合" << endl;
            list[i] = NULL; // 移除观察者 理论上后面所有的数据都需往前移动
            // cout << list[i]->getName() << "被移除了观察者集合" << endl;

            break;
        }
    }
}

// 通知
void Mother::Notify(string action)
{
    // 遍历孩子数组，逐个的将每个观察者都通知到
    for (int i = 0; i < 10; i++)
    {
        if (list[i])
        {
            // 更改状态
            list[i]->Updata(action);
            // 不能break 要通知所有的观察者
        }
    }
}

Father::Father()
{
    for (int i = 0; i < 10; i++)
        list[i] = NULL;
}
Father::~Father(){}

void Father::AddChild(Child *c) // 添加观察者
{
    // 遍历孩子数组，找一个空位置来添加
    for (int i = 0; i < 10; i++)
    {
        // 判断当前的位置是否为空
        if (list[i] == NULL)
        {
            list[i] = c; // 添加观察者
            cout << c->getName() << "被添加到了观察者集合" << endl;
            break;
        }
    }
}
void Father::DelChild(Child *c) // 移除观察者
{
    // 遍历孩子数组，找一个到需要移除的观察者
    for (int i = 0; i < 10; i++)
    {
        // 判断当前的位置是否和c指针指向同一个空间
        if (list[i] == c)
        {
            cout << list[i]->getName() << "被移除了观察者集合" << endl;
            list[i] = NULL; // 移除观察者
            break;
        }
    }
}
void Father::Notify(string action) // 通知
{
    // 遍历孩子数组，逐个的将每个观察者都通知到
    for (int i = 0; i < 10; i++)
    {
        if (list[i] != NULL)
            list[i]->Updata(action);
    }
}

Child::Child(string name) : m_name(name)
{
}

Child::~Child()
{
}

string Child::getName()
{
    return m_name;
}

// 状态切换的接口
void Child::Updata(string action)
{
    std::cout << m_name << "观察到:" << action << "::";
    if (action == "妈妈在开门!" || action == "爸爸下班了!")
    {
        std::cout << "关闭电脑，开启疯狂学习模式!" << std::endl;
    }
    else if (action == "妈妈出门了!" || action == "爸爸上班了!")
    {
        std::cout << "打开电脑，开启疯狂游戏模式!" << std::endl;
    }
    else
    {
        std::cout << "无效信号!" << std::endl;
    }
}

int main()
{
    Mother m, m2; // 创建一个被观察者
    Father f;     // 创建一个被观察者

    Child c1("蔡徐坤");
    Child c2("范丞丞");

    m.AddChild(&c1);
    m.AddChild(&c2);

    f.AddChild(&c1);

    // m.Notify("妈妈在开门!");//两个孩子都通知到了
    // f.Notify("爸爸下班了!"); // 只有c1被通知到

    // m.DelChild(&c1);
    // m.Notify("妈妈在开门!");

    m2.AddChild(&c1);
    m2.Notify("妈妈在开门!");

    return 0;
}