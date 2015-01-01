#include <fstream>
#include <iostream>
#include <string>
#include <wchar.h>
using namespace std;

int main(){
	string filename ;
	cin>>filename;
	ifstream infile(filename.c_str());
	
	if(!infile){
		cout << "open error\n";
		return (1);
	}
	string readin;
	wstring wreadin;
	streambuf* old_buffer = cin.rdbuf(infile.rdbuf());
//	cin >> wreadin;

	char c;
	int count=0;
	infile>>readin;
	cout<<"I am cout:"<<readin<<endl;
	
	/*
	 *  put() OK!
	 *
	while(infile.get(c)){
		if(count++ < 300)
			cout.put(c);
		else 
			break;
	}
	cout << "put over" << endl;
	*/



	/*  
	 *  getline() ok!
	 *
	while(getline(infile,readin)){
		if(count++ < 1)
			cout<<readin;
		else 
			break;
	}
	cout << "getline over" << endl;
	*/

	/*
	 * ifstream.getline() OK!
	 *
	char buffer[1024];
	infile.getline(buffer,1024);
	cout << buffer;
	if(!infile.good()){
		cout <<"broken" <<endl;
	}
	*/

	cout << readin << endl;
//	cout << "readin=" << readin <<"**";
	cout << "\n\n ok ,end" << endl;
	return 0;
}
