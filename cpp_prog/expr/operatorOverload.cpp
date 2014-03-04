/*
 * test.cpp
 *
 *  Created on: Sep 7, 2011
 *      Author: dyc
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <set>
#include <utility>
using namespace std;

class a{
public:
	string s;
	int i;

	a(string sp):s(sp),i(0){
		cout << "in a(string)" << endl;
	};

	a(){};

	a(const a& ac):s(ac.s){
		cout << "in a(const a&)" << endl;
	}

	a(a& ac):s(ac.s){
		cout << "in a(a&)" << endl;
	}

	void show(){
		cout<<"show s: "<<s<<endl;
	}

	void operator=(const a& ap){
        (void)ap;
		cout <<"in const op=(a)" << endl;
	}

	void operator=(a& ap){
        (void)ap;
		cout <<"in op=(a)" << endl;
	}

	void operator=(const string &s){
        (void)s;
		cout <<"in const op=(string)" << endl;
	}

	void operator=(string &s){
        (void)s;
		cout <<"in op=(string)" << endl;
	}

	void operator=(int s){   //void operator=(int s) is right, keep in mind!!!
        (void)s;
		cout <<"in op=(i)" << endl;
	}

    // 等价与下面的 void operator+(a& ap, int i)
//	void operator+(int i){
//		cout << "a + i = "<< this->i +i <<endl;
//	}
    operator long() {
		cout <<"cast to long" << endl;
        return 0;
    }

    operator int() {
		cout <<"cast to int" << endl;
        return 0;
    }

    a operator + (a& l){
        (void)l;
	    cout << "a + a = " <<endl;
        return *this;
    }
};

// 以下函数和void operator+(int i,a& ap)等价
void operator+(const int i,a& ap){
	cout << "const i + a = "<< ap.i +i <<endl;
}

void operator+(a& ap, int i){
	cout << "a + i = "<< ap.i +i <<endl;
}

void operator+(const a& ap, int i){
	cout << "const a + i = "<< ap.i +i <<endl;
}

int main(){
//	a ao = string("dyc");  // it seems to have called the const copy constructor,but we can't see the output
	a ao;
	cout<< "************" << endl;
	ao = 321;
    string s("dyc");
    ao = s;
	ao = string("dyc2");
	ao.show();
	cout<< "************" << endl;
	a ao2 = ao;
	a ao3("dyc");
	cout<< "************" << endl;
	123 + ao;
	ao + 1234;
	ao = ao2;

	cout<< "************" << endl;
    // 可见，函数返回的临时对象，如果作为另一个函数的参数
    // 调用的会是那个函数的const版本，但是这个临时对象其实不是
    // const，而是可以被赋值的
    ao + ao2 = ao + ao3;
	ifstream file("filename");
//	ifstream file2 = "filename";
	return 0;
}


