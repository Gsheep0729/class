#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool isEven(int n)
{
    return n > 3;
}

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int>::iterator it = std::find(v.begin(), v.end(), 3);
    if (it == v.end())
    {
        cout << "没找到" << endl;
    }
    else
    {
        cout << *(it + 1) << endl;
    }

    it = std::find_if(v.begin(), v.end(), isEven);
    if (it == v.end())
    {
        cout << "没找到" << endl;
    }
    else
    {
        cout << *it << endl;
    }

    std::vector<int> v2{5, 4, 6, 7};
    it = std::find_first_of(v.begin(), v.end(), v2.begin(), v2.end());
    if (it == v.end())
    {
        cout << "没找到" << endl;
    }
    else
    {
        cout << *it << endl;
    }

    std::vector<int> v3{2, 4};
    it = std::search(v.begin(), v.end(), v3.begin(), v3.end());
    if (it == v.end())
    {
        cout << "没找到" << endl;
    }
    else
    {
        cout << *it << endl;
    }

    return 0;
}