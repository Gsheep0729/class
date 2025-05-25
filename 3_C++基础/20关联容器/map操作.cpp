#include <iostream>
#include <set>

using namespace std;
int main()
{
    // 创建一个空的 std::set
    std::set<int> mySet;

    // 插入元素
    mySet.insert(4);
    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);

    // 插入重复被忽略
    mySet.insert(4);

    // 迭代器删除 ++逻辑上的偏移  +物理
    mySet.erase(++mySet.begin());
    // 键删除 []
    mySet.erase(4);

    for (std::set<int>::iterator it = mySet.begin(); it != mySet.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
