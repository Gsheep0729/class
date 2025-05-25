#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

void Double(int &n)
{
    n *= 2;
}
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::for_each(v.begin(), v.end(), Double);

    std::for_each(v.begin(), v.end(), [](int n)
                  { cout << n << " "; });
    cout << endl;

    std::list<int> l;
    // std::copy(v.begin(), v.end(), l.begin());
    // std::for_each(l.begin(), l.end(), [](int n)
    //               { cout << n << " "; });

    std::transform(v.begin(), v.end(), l.begin(), [](int n)
                   { return n * 2; });
    std::for_each(l.begin(), l.end(), [](int n)
                  { cout << n << " "; });
    cout << endl;
    std::replace(v.begin(), v.end(), 2, 100);
    std::for_each(v.begin(), v.end(), [](int n)
                  { cout << n << " "; });
    cout << endl;
    std::replace_if(v.begin(), v.end(), [](int n)
                    { return n < 10; }, 1);
    std::for_each(v.begin(), v.end(), [](int n)
                  { cout << n << " "; });

    return 0;
}