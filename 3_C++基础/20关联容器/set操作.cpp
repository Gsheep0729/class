#include <iostream>
#include <map>

using namespace std;
int main()
{
    // 初始化一个元素
    std::map<int, string> myMap = {{1, "one"}};

    // 1.构造类型思想插入
    myMap.insert({2, "two"});
    // 2.类模板方式插入
    myMap.insert(std::pair<int, string>(3, "three"));
    // 3. 函数模板方式插入
    myMap.insert(std::make_pair(4, "four"));

    cout << myMap.size() << endl;
    // 存在
    cout << myMap[1] << endl;
    // 不存在
    cout << myMap[-1] << endl;
    cout << myMap.size() << endl;

    // 存在
    cout << myMap.at(1) << endl;
    // 不存在
    // cout << myMap.at(-2) << endl;//检查键是否存在

    std::map<int, string>::iterator it = myMap.find(10);
    if (it == myMap.end())
    {
        cout << "不存在这个键" << endl;
    }
    else
    {
        cout << it->first << endl;
        cout << it->second << endl;
    }

    myMap.erase(myMap.begin());   // 删除的是-1
    cout << myMap.size() << endl; // 4

    int result = myMap.erase(10);
    if (result == 1)
    {
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "删除失败" << endl;
    }

    for (std::map<int, string>::iterator it = myMap.begin(); it != myMap.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}
