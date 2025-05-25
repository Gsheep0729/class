#include <iostream>
#include <cstdlib>
#include "test_1.h"
using namespace std;

int main()
{
    Array<int> intArray(5);
    for (int i = 0; i < intArray.getSize(); i++)
    {
        intArray[i] = i;
    }
    // 输出整型数组的内容
    for (int i = 0; i < intArray.getSize(); ++i)
    {
        std::cout << intArray[i] << " ";
    }
    std::cout << endl;

    Array<int> intArray1 = intArray;
    // 输出整型数组的内容
    for (int i = 0; i < intArray1.getSize(); ++i)
    {
        std::cout << intArray1[i] << " ";
    }
    std::cout << endl;

    Array<int> intArray2(3);
    intArray2 = intArray;
    for (int i = 0; i < intArray2.getSize(); ++i)
    {
        std::cout << intArray2[i] << " ";
    }
    std::cout << endl;
    std::cout << "-----------------" << endl;

    Array<A> a(5);
    for (int i = 0; i < a.getSize(); i++)
    {
        a[i] = i;
    }
    for (int i = 0; i < a.getSize(); i++)
    {
        std::cout << a[i] << " ";
    }

    return 0;
}

// #ifndef __TEST_1_H__
// #define __TEST_1_H__
// #include <iostream>
// #include <cstdlib>
// #include "test_1.h"
// using namespace std;
// class A
// {
// public:
//     A(int num = 0) : m_num(num)
//     {
//     }
//     friend std::ostream &operator<<(std::ostream &os, A &a);

// private:
//     int m_num;
// };

// // 使用模板类定义一个数组
// template <typename T>
// class Array
// {
// public:
//     Array(int cnt) : m_parr(new T[cnt]), m_cnt(cnt)
//     {
//     }
//     ~Array();

//     // 获取数组大小
//     int getSize();

//     // 访问元素
//     T &operator[](int index);

//     // 拷贝构造
//     Array(const Array &that);

//     // 拷贝赋值
//     Array &operator=(const Array &that);

// private:
//     T *m_parr; // 数组首地址
//     int m_cnt; // 数组元素个数
// };

// ostream &operator<<(ostream &os, A &a)
// {
//     os << a.m_num;
//     return os;
// }

// template <typename T>
// Array<T>::~Array()
// {
//     delete[] m_parr;
// }

// template <typename T>
// int Array<T>::getSize()
// {
//     return m_cnt;
// }

// template <typename T>
// T &Array<T>::operator[](int index)
// {
//     if (index < 0 || index > m_cnt)
//     {
//         cout << "下标输入有误" << endl;
//         exit(-1);
//     }
//     return m_parr[index];
// }

// template <typename T>
// Array<T>::Array(const Array &that)
// {
//     m_cnt = that.m_cnt;
//     m_parr = new T[m_cnt];
//     for (int i = 0; i < m_cnt; i++)
//     {
//         m_parr[i] = that.m_parr[i];
//     }
// }

// template <typename T>
// Array<T> &Array<T>::operator=(const Array &that)
// {
//     m_cnt = that.m_cnt;
//     if (this != &that)
//     {
//         // 释放旧内存
//         delete[] m_parr;
//         // 分配新内存
//         m_parr = new T[m_cnt];
//         for (int i = 0; i < m_cnt; i++)
//         {
//             m_parr[i] = that.m_parr[i];
//         }
//     }
//     return *this;
// }

// #endif