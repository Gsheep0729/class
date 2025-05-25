/*定义一个图书类，包含图书名字、价格、数量。写一个常函数，将图书信息打印出来*/
#include <iostream>
using namespace std;
class book
{
    //在类内定义函数来访问类的成员变量，以方便内外访问
    public:
    void setname(string name)
    {
        this->inname = name;
    }
    void setprice(double price)
    {
        this->inprice = price;
    }
    void setnum(int num)
    {
        this->innum = num;
    }
    void show()const
    {
        cout << "图书名字：" << inname << endl;
        cout << "图书价格：" << inprice << endl;
        cout << "图书数量：" << innum << endl;
    }

    // 定义类数据成员（隐私）
    private:
    string inname;
    double inprice;
    int innum;

};
int main()
{
    //定义一个book类型的变量
    book content;//变量命前缀加“ . ”来初始化，指针就用“->”
    content.setname("C++从入门到精通");
    content.setprice(99.9);
    content.setnum(10);
    content.show();
    
    
    return 0 ;
}