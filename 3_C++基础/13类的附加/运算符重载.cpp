#include <iostream>
#include <stdexcept> // 用于异常处理

// ==================== 示例类：复数类 Complex ====================
class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // -------------------- 运算符重载示例 --------------------

    // 1. 算术运算符 '+'（成员函数）
    Complex operator+(const Complex& other) const {
        // const 修饰符：表示该函数不会修改当前对象（安全）
        // 参数为 const 引用：避免拷贝，同时禁止修改传入对象
        // 返回新对象：因为加法操作不修改原对象
        return Complex(real + other.real, imag + other.imag);
    }

    // 2. 赋值运算符 '='（必须为成员函数）
    Complex& operator=(const Complex& other) {
        // 返回引用（Complex&）：支持链式赋值（如 a = b = c）
        if (this != &other) { // 处理自赋值（防止资源冲突）
            real = other.real;
            imag = other.imag;
        }
        return *this; // 返回当前对象的引用
    }

    // 3. 比较运算符 '=='（成员函数）
    bool operator==(const Complex& other) const {
        // const 修饰符：比较操作不修改对象
        return (real == other.real) && (imag == other.imag);
    }

    // -------------------- 友元函数示例 --------------------
    // 输入/输出运算符通常需要访问私有成员，故声明为友元
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

// 4. 输出运算符 '<<'（必须为非成员函数，通过友元访问私有成员）
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os; // 返回流引用以支持链式调用（如 cout << a << b）
}

// 5. 输入运算符 '>>'
std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imag;
    return is;
}

// ==================== 示例类：动态数组类 DynamicArray ====================
class DynamicArray {
private:
    int* data;
    size_t size;

public:
    DynamicArray(size_t s) : size(s) {
        data = new int[size];
    }

    ~DynamicArray() {
        delete[] data;
    }

    // 6. 下标运算符 '[]'（成员函数）
    int& operator[](size_t index) {
        // 返回引用：允许通过下标修改元素（如 arr[0] = 5）
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const int& operator[](size_t index) const {
        // const 版本：用于 const 对象，返回 const 引用（禁止修改）
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    // 7. 前置自增运算符 '++'
    DynamicArray& operator++() {
        // 返回引用：直接修改原对象并返回自身
        for (size_t i = 0; i < size; ++i) ++data[i];
        return *this;
    }

    // 8. 后置自增运算符 '++'
    DynamicArray operator++(int) {
        // 返回临时对象：返回自增前的旧值
        // 参数 int 仅用于区分前置和后置，无实际用途
        DynamicArray temp = *this;
        ++(*this); // 调用前置版本
        return temp;
    }
};

// ==================== 示例：函数调用运算符 ====================
class Multiplier {
public:
    // 9. 函数调用运算符 '()'
    int operator()(int a, int b) const {
        // const 表示调用不会修改对象状态
        return a * b;
    }
};

// ==================== 示例：类型转换运算符 ====================
class Convertible {
private:
    int value;
public:
    Convertible(int v) : value(v) {}

    // 10. 类型转换运算符（转换为 int）
    operator int() const {
        // const 表示转换不修改对象
        return value;
    }
};

// ==================== 主函数测试 ====================
int main() {
    // 测试 Complex 类
    Complex a(2, 3), b(4, 5);
    Complex c = a + b; // 调用 operator+
    std::cout << "c = " << c << std::endl; // 调用 operator<<

    // 测试 DynamicArray 类
    DynamicArray arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3; // 调用 operator[]
    ++arr; // 前置++
    DynamicArray arr2 = arr++; // 后置++

    // 测试函数调用运算符
    Multiplier mul;
    std::cout << "mul(3,4) = " << mul(3, 4) << std::endl;

    // 测试类型转换
    Convertible conv(42);
    int num = conv; // 隐式调用 operator int()
    std::cout << "num = " << num << std::endl;

    return 0;
}