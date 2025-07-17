#include <iostream>
using namespace std;

class A
{
public:
    A(int num = 0) : m_num(num)
    {
    }
    friend ostream &operator<<(ostream &os, A &a)
    {
        os << a.m_num;
        return os;
    }

private:
    int m_num;
};
// 使用模板类定义一个数组
template <class T>
class Array
{
public:
    Array(int cnt) : m_parr(new T[cnt]), m_cnt(cnt)
    {
    }
    ~Array()
    {
        delete[] m_parr;
    }
    // 获取数组大小
    int getSize()
    {
        return m_cnt;
    }
    // 访问元素
    T &operator[](int index)
    {
        if (index < 0 || index > m_cnt)
        {
            cout << "下标输入有误" << endl;
            exit(-1);
        }
        return m_parr[index];
    }
    // 拷贝构造
    Array(const Array &that)
    {
        m_cnt = that.m_cnt;
        m_parr = new T[m_cnt];
        for (int i = 0; i < m_cnt; i++)
        {
            m_parr[i] = that.m_parr[i];
        }
    }
    // 拷贝赋值
    Array &operator=(const Array &that)
    {
        m_cnt = that.m_cnt;
        if (this != &that)
        {
            // 释放旧内存
            delete[] m_parr;
            // 分配新内存
            m_parr = new T[m_cnt];
            for (int i = 0; i < m_cnt; i++)
            {
                m_parr[i] = that.m_parr[i];
            }
        }
        return *this;
    }

    void Init(int size); // 类模板内

    template <typename T1> // 模板头函数定义
    T1 add(T1 a, T1 b)     // T只是一个名字,表示一种类型
    {
        // 函数体;
        return a + b; // T类型的对象本身是可以相加的  自定义类型 重载+这个符号
    }

private:
    T *m_parr; // 数组首地址
    int m_cnt; // 数组元素个数
};

template <typename T> // 定义
void Array<T>::Init(int size)
{
    for (int i = 0; i < size; i++)
    {
        m_parr[i] = i;
    }
}

template <typename T>
void print(Array<T> &arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
}

int main()
{
    Array<int> intArray(5); // 类模板的使用
    // for (int i = 0; i < intArray.getSize(); i++)
    // {
    //     intArray[i] = i;
    // }
    intArray.Init(intArray.getSize());
    cout << intArray.add(1, 2) << endl;
    // // 输出整型数组的内容
    print(intArray, intArray.getSize());
    // for (int i = 0; i < intArray.getSize(); ++i)
    // {
    //     std::cout << intArray[i] << " ";
    // }
    std::cout
        << endl;

    // Array<int> intArray1 = intArray;
    // // 输出整型数组的内容
    // for (int i = 0; i < intArray1.getSize(); ++i)
    // {
    //     std::cout << intArray1[i] << " ";
    // }
    // std::cout << endl;

    // Array<int> intArray2(3);
    // intArray2 = intArray;
    // for (int i = 0; i < intArray2.getSize(); ++i)
    // {
    //     std::cout << intArray2[i] << " ";
    // }
    // std::cout << endl;
    // std::cout << "-----------------" << endl;

    // Array<A> a(5);
    // for (int i = 0; i < a.getSize(); i++)
    // {
    //     a[i] = i;
    // }
    // for (int i = 0; i < a.getSize(); i++)
    // {
    //     std::cout << a[i] << " ";
    // }

    return 0;
}