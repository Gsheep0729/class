#include <iostream>
#include <cstring>
using namespace std;

class Book
{
public:
    Book(const char *name, float price = 0, int count = 0)
     : m_name(new char[strlen(name) + 1]), m_price(price), m_count(count)
    {
        cout << "含参构造" << endl;
        strcpy(m_name, name);
    }
    void print() const
    {
        cout << "名字：" << m_name << "，价格：" << m_price << "，数量：" << m_count << endl;
    }
    ~Book()
    {
        cout << "析构" << endl;
        delete[] m_name;
        m_name = NULL;
    }

private:
    // string m_name;
    char *m_name;
    float m_price;
    int m_count;
};

int main()
{
    Book b("偶像练习生", 2.5, 10);
    int *p = new int[10];

    b.print();
    return 0;
}