#include<iostream>

using namespace std;
class A{
	int a;
public :
	virtual void p(){cout << "a" << endl;}
//	virtual ~A(){};
};
class B:public A{
	int b;
public :
	void p(){cout << "b" << endl;}
//	~A(){};
};
class C:public A{
	int c;
	void p(){cout << "c" << endl;}
};
class D:public B, public C{
	int d;
};
class E:public D{
	int d;
};
class test{
public:
	test(){};
	test(int i){++i;};
	void f(){};
};
int main(){
	string s = "dycforever";
	cout << "sizeof(A)=" << sizeof(A)
		<< " sizeof(B)=" << sizeof(B)
		<< " sizeof(C)=" << sizeof(C)
		<< " sizeof(D)=" << sizeof(D)
		<< " sizeof(E)=" << sizeof(E);
	test t;
	t.f();
	cout << endl <<"sizeof(s)= " << sizeof(s) << endl;


}
