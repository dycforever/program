#include <iostream>
using namespace std;

class A{
private:
	int i;
public:
	A(int i){this->i = i;}

    void nc(){
    }

	void f() const{
		cout << "const" <<endl;
	}

	void f() {
		cout << "non const" << endl;
	}
};

int main(){
	A a1(1);
	const A a2(2);
	a1.f();
	a2.f();
}
