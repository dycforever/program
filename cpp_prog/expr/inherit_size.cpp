#include<iostream>

using namespace std;
class A{
public :
	int a;
	virtual void p() const {cout << "const a" << endl;}
	virtual void p() {cout << "a" << endl;}
//	virtual ~A(){};
};

class B_A: public A{
	int b;
public :
	void p() {cout << "B_A" << endl;}
	void p() const {cout << "const B_A" << endl;}
//	~A(){};
};

class C_A: public A{
public:
	int c;
	void p() {cout << "C_A" << endl;}
	void p() const {cout << "const C_A" << endl;}
};

class D_BC: public B_A, public C_A{
public:
	int d;
};

class E_D_BC: public D_BC{
public:
	int d;
};

void print_size()
{
	string s = "dycforever";
	cout << "sizeof(A)=" << sizeof(A)
		<< " sizeof(B_A)=" << sizeof(B_A)
		<< " sizeof(C_A)=" << sizeof(C_A)
		<< " sizeof(D_BC)=" << sizeof(D_BC)
		<< " sizeof(E_D_BC)=" << sizeof(E_D_BC);
	cout << endl <<"sizeof(s)= " << sizeof(s) << endl;
}

void call_function()
{
    A* a = new A;
    a->p();

    A* a2 = new B_A;
    B_A* b = dynamic_cast<B_A*>(a2);
    b->p();

    C_A* c_a = new C_A;
    const C_A* c_a_const = c_a;
    c_a->p();

    const D_BC* d_bc = new D_BC;
    // error: ambiguous p()
    // d_bc->p();

    E_D_BC* e = new E_D_BC;
    // error: ambiguous p()
    // e->p();
}

int main() 
{
    call_function();
}

