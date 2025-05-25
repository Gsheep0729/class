#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class myString
{
public:
    // 无参
    myString() : m_str(new char(0)) {}
    // 含参
    myString(const char *str) : m_str(new char[strlen(str) + 1]) // 为\0多申请1个空间
    {
        // cout << strlen(str) + 1 << endl;
        strcpy(m_str, str);
    }
    // 拷贝构造
    myString(const myString &that)
    {
        // 申请新空间
        m_str = new char[strlen(that.m_str) + 1];
        // 赋值
        strcpy(m_str, that.m_str);
    }
    // 拷贝赋值
    myString &operator=(const myString &that)
    {
        if (&that != this)
        {
            // 释放旧空间
            delete[] m_str;
            // 申请新空间
            m_str = new char[strlen(that.m_str) + 1];
            // 赋值
            strcpy(m_str, that.m_str);
        }
        return *this;
    }
    // 析构
    ~myString()
    {
        delete[] m_str;
    }
    // 删除
    myString &erase()
    {
        // 释放旧空间
        delete[] m_str;
        // 申请新空间
        m_str = new char(0);
        return *this;
    }
    // 长度
    int size()
    {
        return strlen(m_str);
    }
    // at访问
    char at(unsigned int i)
    {
        if (i > strlen(m_str))
        {
            cout << "越界了" << endl;
            exit(-1);
        }
        return m_str[i];
    }
    //+ 成员函数 左右操作数可左可右 返回值右
    const myString operator+(const myString &str) const
    {
        char *res = new char[strlen(m_str) + strlen(str.m_str) + 1];
        // 为新空间赋值
        strcpy(res, m_str);
        strcat(res, str.m_str);

        myString result(res);
        return result;
    }
    //+= 成员函数 左操作数左 右操作数可左可右 返回值左操作数本身
    myString &operator+=(const myString &str)
    {
        // 先申请新空间
        char *res = new char[strlen(m_str) + strlen(str.m_str) + 1];
        // 为新空间赋值
        strcpy(res, m_str);
        strcat(res, str.m_str);
        // 释放旧空间
        delete[] m_str;
        // 更新内容
        m_str = res;
        return *this;
    }
    //== 左右操作数可左可右 返回值bool
    bool operator==(const myString &str) const
    {
        if (strcmp(m_str, str.m_str) == 0)
        {
            return true;
        }
        return false;
    }
    //< 左右操作数可左可右 返回值bool
    bool operator<(const myString &str) const
    {
        if (strcmp(m_str, str.m_str) < 0)
        {
            return true;
        }
        return false;
    }
    //> 左右操作数可左可右 返回值bool
    bool operator>(const myString &str) const
    {
        if (strcmp(m_str, str.m_str) > 0)
        {
            return true;
        }
        return false;
    }
    //[] 左值版本 返回值左值
    char &operator[](int i)
    {
        return m_str[i];
    }
    //[] 右值版本 返回值右值
    const char &operator[](int i) const
    {
        return m_str[i];
    }

    // 输出
    friend ostream &operator<<(ostream &os, const myString &str)
    {
        os << str.m_str;
        return os;
    }
    // 输入
    friend istream &operator>>(istream &is, myString &str)
    {
        // 保存输入
        string res = "";
        is >> res;

        // 释放旧内存
        delete[] str.m_str;
        str.m_str = new char[res.length() + 1];
        // 重新赋值
        strcpy(str.m_str, res.c_str());
        return is;
    }

private:
    char *m_str;
};

int main()
{
    // 无参
    myString str1;
    cout << str1 << endl;

    // 拷贝赋值
    str1 = "abc";
    cout << str1 << endl;

    // 1 5
    cout << str1[1] << endl;
    cout << str1.at(1) << endl;

    // 输入输出
    cout << "输入字符串:";
    cin >> str1;
    cout << str1 << endl;

    // 拷贝构造
    myString str2(str1);
    cout << str2 << endl;

    //+
    myString str3 = str1 + str2;
    cout << str3 << endl;

    //+=
    str3 += "abc";
    cout << str3 << endl;

    //==
    cout << (str3 > "abc") << endl;

    return 0;
}
