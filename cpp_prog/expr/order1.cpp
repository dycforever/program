#include <iostream>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <vector>

using namespace std;

class World
{
public:
    World(int id) : _identifier(id) //构造函数前导中初始化常量成员
    {
        std::cout<<"Hello world from "<<_identifier<<".\n"; //需加前缀std::
    }
    ~World()
    {
        std::cout<<"Goodbye world from "<<_identifier<<".\n";
    }
private:
    const int _identifier;
};

class CD{
public:
	CD() { cout<< "constructor "<< endl;}

	CD(const CD& cd){
        (void)cd;
		cout << "copy constructor"  << endl;
	}

    // 这个是错误的语法，编译通不过
    // 否则就无穷递归了
//	CD(const CD cd){
//		cout << "copy constructor"  << endl;
//	}

	~CD(){
		cout << "CD destructor" <<endl;
	}
};


class A{
public:
	A(){
        log();
		cout << "A constructor" << endl;
	}

	virtual ~A(){
        log();
		cout << "A destructor" << endl;
	}

	A(A& a){
        (void)a;
		cout << "A copy constructor" << endl;
	}

	A& operator =(A& a){
		cout << "A = operator" << endl;
		return a;
	}

    virtual void log(){
        cout << "A print log" << endl;
    }
};

class B : public A {
public:
	B(){
        log();
		cout << "B constructor" << endl;
	}

	~B(){
        log();
		cout << "B destructor" << endl;
	}

    virtual void log(){
        cout << "B print log" << endl;
    }
};

World TheWorld(1); //全局对象
int main()
{
    World smallWorld(2); //本地对象
    for(int i=3;i<6;++i)
    {
        World aWorld(i);
    }
    World oneMoreWorld(6);
    extern int ff(float);
	cout<< endl << "--------------------------------------------------" << endl <<endl;

	CD cd1;
	vector<CD> * v = new vector<CD>;
	cout << "middle" <<endl;
	v->push_back(cd1);
	cout << "middle" <<endl;
	delete v;

	cout<< endl << "--------------------------------------------------" << endl <<endl;

	A a;
	A a1;
	a1 = a;

	cout<< endl << "--------------------------------------------------" << endl <<endl;

    B* b = new B;
    delete b;

	cout<< endl << "-------------------all over--------------------" << endl <<endl;

	return 0;
}

int ff(float aa)
{
	return ((int)aa);
}
