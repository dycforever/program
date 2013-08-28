#include<iostream>
using namespace std;
class va1{
//	int i;
//	void f();
	virtual void f();
};
class va2{
//	int i;
	virtual void f();
};
class va3{
//	int i;
	void f();
};

// virtual 
class v3:virtual public va1,va2,va3{

};

int main(){
	cout << sizeof(v3);
	return 0;
}
