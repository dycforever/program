#include<iostream>
using namespace std;
int main(){
	int i = 0;
	int b = i++ + i++;
	i=0;
	int c = ++i + ++i;
	cout << "b=" << b << "  c=" << c << endl;
	return 0;
}
