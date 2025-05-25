/*头文件和源文件之间通过 #include 指令相互引用。头文件中的声明告诉编译器如何
在源文件中找到和使用这些声明，而源文件中的定义则提供了这些声明的具体实现*/
void print();//对print函数的声明，以调用test1中的函数
int test1(int a, int b);
extern int num;
void setValue(); 
