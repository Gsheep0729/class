#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // 模板类 创建对象 编译时根据数据类型来创建出对应类型对象
    std::vector<int> myVector;

    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);

    // 使用 size() 获取 std::vector 的大小
    std::cout << "Size of myVector: " << myVector.size() << std::endl;

    // 使用 at() 访问元素（会进行边界检查）
    std::cout << "Element at index 1: " << myVector.at(1) << std::endl;

    // 使用 [] 访问元素（不会进行边界检查）
    std::cout << "Element at index 2: " << myVector[2] << std::endl;

    // 使用 front() 和 back() 访问第一个和最后一个元素
    std::cout << "First element: " << myVector.front() << std::endl;
    std::cout << "Last element: " << myVector.back() << std::endl;

    // 插入 1 100 2 3
    myVector.insert(myVector.begin() + 1, 100);

    // 删除 100 2 3
    myVector.erase(myVector.begin());
    // 100 2
    myVector.pop_back();

    for (std::vector<int>::iterator it = myVector.begin(); it != myVector.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    if (myVector.empty())
    {
        std::cout << "空" << endl;
    }
    else
    {
        std::cout << "非空" << endl;
    }

    return 0;
}