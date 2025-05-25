/*浅拷贝 vs 深拷贝
浅拷贝：仅复制指针的值（地址），导致多个对象共享同一块内存。
问题：重复释放内存、悬垂指针、数据意外修改。
深拷贝：为新对象分配独立内存，并复制指针指向的数据。
解决：每个对象拥有独立资源，互不影响。
*/
#include <cstring>
class MyString {
private:
    char* data;//类成员含指针则需考虑构建深拷贝

public:
    // 构造函数
    MyString(const char* s = "") {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }

    // 深拷贝的拷贝构造函数
    MyString(const MyString& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // 深拷贝的赋值运算符重载
    MyString& operator=(const MyString& other) {
        if (this != &other) {  // 防止自赋值
            char* newData = new char[strlen(other.data) + 1];  // 1. 分配新内存
            strcpy(newData, other.data);                      // 2. 复制数据
            delete[] data;                                   // 3. 释放旧内存
            data = newData;                                   // 4. 指向新内存
        }
        return *this;
    }

    // 可选：辅助输出函数
    const char* get() const { return data; }
};
int main() {
    MyString str1("Hello");
    MyString str2 = str1;        // 调用拷贝构造函数（深拷贝）
    MyString str3;
    str3 = str1;                 // 调用赋值运算符（深拷贝）

    // 修改str1不影响str2和str3
    // 因为每个对象拥有独立内存
    return 0;
}