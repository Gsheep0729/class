#include <iostream>
using namespace std;

// 假设的坐标点结构
struct Point
{
    int x;
    int y;
};

// 定义每个形状的最大顶点数
#define SIZE 10

class Shape
{
protected:
    Point arr[SIZE]; // 结构体数组来存放顶点
    int numArr;      // 当前形状的顶点数

public:
    Shape() : numArr(0) {}

    // 添加顶点，注意这里需要确保不会超过数组的最大容量
    void addVertex(const Point &p)
    {
        if (numArr < SIZE)
        {
            arr[numArr++] = p;
        }
        else
        {
            std::cerr << "Error: Too many vertices for this shape." << std::endl;
        }
    }
    virtual void draw() const
    {
        cout << "输出某个形状--by Shape类" << endl;
    }
};

// 三角形子类
class Triangle : public Shape
{
public:
    Triangle()
    {
        // 三角形的三个顶点
        addVertex({0, 0});
        addVertex({0, 5});
        addVertex({5, 0});
    }
    void draw() const override
    {
        cout << "输出三角形" << endl;
        for (int i = 0; i < numArr; i++)
        {
            std::cout << "(" << arr[i].x << "," << arr[i].y << ")" << endl;
        }
    }
};

// 四边形子类
class Quadrilateral : public Shape
{
public:
    Quadrilateral()
    {
        // 四边形的四个顶点
        addVertex({0, 0});
        addVertex({0, 5});
        addVertex({5, 5});
        addVertex({5, 0});
    }
    virtual void draw() const
    {
        cout << "输出四边形" << endl;
        for (int i = 0; i < numArr; i++)
        {
            std::cout << "(" << arr[i].x << "," << arr[i].y << ")" << endl;
        }
    }
};
int main()
{
    // 对于同一件事物的不同体现形式
    // 对于draw()的不同体现形式
    Triangle triangle;
    // triangle.draw();

    cout << endl;

    Quadrilateral quadrilateral;
    // quadrilateral.draw();

    cout << endl;

    Shape shape;
    // shape.draw();

    // 向上造型 指向子类对象基类指针数组
    Shape *shapes[2] = {&triangle, &quadrilateral};

    for (int i = 0; i < 2; i++)
    {
        shapes[i]->draw();
    }

    // 向上造型 指向子类对象基类指针数组
    Shape *shapes[2] = {&triangle, &quadrilateral};

    // 重新恢复为子类类型
    Triangle *ptr = dynamic_cast<Triangle *>(shapes[0]);
    ptr->draw();

    return 0;
}