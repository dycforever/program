#include <iostream>
#include <stdio.h>
using namespace std;
class A{
 const static int i=0;
} ;

struct st1{
int i;
short s;
char c;
long l;
};
struct st2{
short s;
char c;
int i;
long l;
};

int get(int );
int main(){
	int pp;
	cin >> pp;
	const int ii = get(pp);
//	const int i2 = ii;
	int ai[ii];
	A* a = new A();
	cout << "finish" << endl;
	char ca[] = "dyc";
	cout << "sizeof ca= " << sizeof(ca) << endl;
	printf("ca=%s\n",ca);
	ca[1]='9';
	printf("ca=%s\n",ca);
	/*-----------------------------*/
	printf("char=%d short=%d int=%d long=%d\n",sizeof(char),sizeof(short),sizeof(int),sizeof(long));
	printf("st1=%d\n",sizeof(st1));
	printf("st2=%d\n",sizeof(st2));

}
// no sense just test if array can be defined without knowing the length, and yes
int get(int p){
	for(int j=0;j<50;j++){
		p++;
	}
	if(p%67==1){
		return 2;
	}else return 1;
}
