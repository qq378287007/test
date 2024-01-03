#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using std::function;

int add(int a, int b)
{
    cout << "int add(int, int)" << endl;
    return a + b;
}

class Example
{
public:
    int add(int a, int b)
    {
        cout << "int Example::add(int, int)" << endl;
        return a + b;
    }

    int data = 100;//C++11的初始化方式
};

void test()
{
    //function与bind结合使用，就可以实现多态
    
    //bind可以绑定add，可以改变函数add的形态(类型)
    //int(int, int)--->int()
    //函数也是有类型的（函数返回类型与函数的参数列表）
    /* auto f = bind(add, 1, 2); */
    function<int()> f = bind(add, 1, 2);
    cout << "f() = " << f() << endl;

    Example ex;
    //成员函数要取地址，需要明确写出取地址符号
    //int(int, int)--->int(int)
    /* auto f2 = bind(&Example::add, ex, 3, 5); */
    function<int()> f2 = bind(&Example::add, ex, 3, 5);
    cout << "f2() = " << f2() << endl;

    //占位符
    //int(int, int)--->int(int)
    /* auto f3 = bind(add, 4, std::placeholders::_1); */
    function<int(int)> f3 = bind(add, 4, std::placeholders::_1);
    cout << "f3(5) = " << f3(5) << endl;

    //bind可以绑定数据成员
    //int data = 100;
    f = bind(&Example::data, &ex);
    cout << "f() = " << f() << endl;
	/*
	int add(int, int)
	f() = 3
	int Example::add(int, int)
	f2() = 8
	int add(int, int)
	f3(5) = 9
	f() = 100
	*/
}

int main(int argc, char** argv)
{
    test();
    return 0;
}

