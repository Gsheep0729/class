#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // 获取指向第一个元素的迭代器
    std::vector<int>::iterator first = vec.begin();

    // 获取指向第三个元素的迭代器
    std::vector<int>::iterator third = first + 2;

    // 计算两个迭代器之间的距离
    std::size_t distance = std::distance(first, third);
    cout << distance << endl;

    std::list<int> l = {1, 2, 3, 4, 5};
    std::list<int>::iterator l_first = l.end();

    // 正数前进 负数后退 next
    std::advance(l_first, -3);
    cout << *l_first << endl; //
    return 0;
}