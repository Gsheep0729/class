#include <iostream>
#include <list>

using namespace std;

int main()
{
    // 创建一个空的 int 类型列表
    std::list<int> myList;

    // 在列表末尾插入元素
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    // 在列表开头插入元素
    myList.push_front(5);
    // myList[1];//error 不支持下标访问
    for (std::list<int>::iterator it = myList.begin(); it != myList.end(); ++it)
    {
        // it--;
        if (*it == 10)
        {
            myList.insert(it, 100);
        }
    }

    // myList.insert(myList.begin() + 1, 100);//error

    for (std::list<int>::iterator it = myList.begin(); it != myList.end(); ++it)
    {

        cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}