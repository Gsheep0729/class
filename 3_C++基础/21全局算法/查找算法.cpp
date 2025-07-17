#include <iostream>
#include <memory>
using namespace std;

struct MyStruct
{
    MyStruct(int value) : value_(value) {}
    ~MyStruct()
    {
        std::cout << "Deleting MyStruct with value " << value_ << std::endl;
    }

    int value_;
};

int main()
{
    // 创建一个指向 MyStruct 的 shared_ptr
    std::shared_ptr<MyStruct> ptr1 = std::make_shared<MyStruct>(10);

    // 复制 shared_ptr，增加引用计数
    std::shared_ptr<MyStruct> ptr2 = ptr1;

    // 当 ptr1 离开作用域并被销毁时，引用计数不会减少到 0，因为还有 ptr2 指向同一个对象
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    {
        std::shared_ptr<MyStruct> ptr3 = ptr1;
        std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    }
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;

    // 当 ptr2 离开作用域并被销毁时，引用计数减少到 0，对象被删除
    // 输出析构函数的调用信息

    // 使用 std::make_unique 创建 std::unique_ptr
    std::unique_ptr<MyStruct> ptr_unique = std::make_unique<MyStruct>(42);
    // 输出 ptr 指向的对象的值
    std::cout << "Value: " << ptr_unique->value_ << std::endl;

    // 不允许复制
    // std::unique_ptr<MyStruct> ptr_unique1 = ptr_unique;
    std::unique_ptr<MyStruct> ptr_unique2 = std::move(ptr_unique); // 可以移动构造

    ptr_unique = NULL;
    std::cout << "Value: " << ptr_unique2->value_ << std::endl;

    return 0;
}