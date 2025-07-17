 //目的：用一个函数，在字符串里找一段字符串的相对位置
#include <iostream>
 using namespace std;
int fuck(string a , string b )
//函数定义输入的形参在函数名时就需定义
//假设在a里找一段b
{
   if(a.length() < b.length())//须满足b包含于a
   {
     return 404;
     //输出错误 
   }
   /*确定了范围没问题后要寻找字符串b中第一个字符在a中的位置
   然后用这个字符的位置作为b的相对位置
   for(初始化表达式；循环条件表达式；循环后的操作表达式)/初始化表达式可以写在for外面
   for里面可以不写。循环条件表达式、循环后的操作表达式也可以不写，只不过会变成死循环*/
   for(int c = 0;c <= a.length() ; c++)
   //定义了一个在范围内递增的变量
   {
      if(b[0] == a[c] )// 当找到字符与要查找的字符第一个字符相同
      {
         int d = c;
         //得到符合目标第一个字符的位置，还需验证是否满足目标
         int e = 0;//定义一个递增变量
         //用while函数，可以把循环控制条件全写在（）里
         while(a[d] == b[e] && e <=b.length() && d <= a.length())
         {
            d++;
            e++;
         }
         if(e >= b.length())//若未发现有符合条件的字符串返回0
         {
            return c;//若发现有符合条件的字符串，返回第一个字符的相对位置
         }
         else
         {
            return -1;
         }
      }
   }
   return -1;
   

}
 

int main()
 {
   int sit = fuck("Iloveyoumom","mo");//输入变量
   cout << "位置在第" << sit <<"个"; 
    return 0;
 }