/*
 * init.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: dyc
 */

#include <iostream>
//using namespace std;


class Init{
	const static float f =3.1;
	int m;
	const float f2;// =3.1;
	int ar[3];
public:
	void show(){
		std::cout<<"showing \n m="<<m<<std::endl;
		for(int i=0;i<3;i++)
			std::cout<<ar[i]<<std::endl;
	}
	Init(int i):m(i),f2(i){};
	Init():f2(0){};
};

float global;
Init i1;
int main(){
	Init ca[2];

	float local;
	std::cout<<"global = "<<global<<"  local= "<<local<<std::endl;
	Init i1;
	i1.show();
	std::cout<<"---------------------------"<<std::endl;
	Init i2;
	i2.show();
	std::cout<<"---------------------------"<<std::endl;
	for(int i=0;i<1;i++){
		Init i3;
		i3.show();
		std::cout<<"---------------------------"<<std::endl;
	}

	return 0;
}






