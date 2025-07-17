#include <iostream>
#include <deque>

using namespace std;

int main()
{
    // 创建一个空的deque
    std::deque<int> myDeque;

    // 向deque的开始位置插入元素
    myDeque.push_front(1);
    myDeque.push_front(2); // 2 1

    // 向deque的末尾插入元素
    myDeque.push_back(3);
    myDeque.push_back(4); // 2 1 3 4

    // 输出deque的大小
    std::cout << "Size of deque: " << myDeque.size() << std::endl;

    // 访问并输出deque的第一个和最后一个元素
    std::cout << "First element: " << myDeque.front() << std::endl;
    std::cout << "Last element: " << myDeque.back() << std::endl;

    for (std::deque<int>::iterator it = myDeque.begin(); it != myDeque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}