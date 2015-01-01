#include <stdio.h>
//#include <stdlib.h>
#include <wchar.h>
#include <clocale>
#include <string>
#include <string.h>
using namespace std;
int main(){
	setlocale(LC_ALL,"zh_CN.gbk");
	/*
	wchar_t wcstr[20] =L"×Ö·û²âÊÔ123abc";
    int len = wcslen(wcstr)+1;
	printf("len = %d /n",len);
	int i;
	for(i = 0; i < len; i++)
		printf("0x%x ",wcstr[i]);
	printf("/n");
	*/
	wchar_t wcstr[20];//=L"×Ö·û²âÊÔ123abc";
	wstring wstr = L"×Ö·û²âÊÔ123abc";
	char str[55] ="×Ö·û²âÊÔ123abc" ;    
	/*
    int n = wcstombs(str,wcstr,55);
    if(-1 == n){
	    perror("wcstombs ");
	    exit(-1);
	}    
    printf("n = %d/n",n);
    for(i = 0; i < n+1; i++)
        printf("0x%x ",str[i]);
    printf("/n");    
    wchar_t wch[50]={0};
*/	int i;
    int m = mbstowcs(wcstr,str,strlen(str));    
    if(m == -1)
    {
	    perror("Converting");
	    exit(-1);
    }
    printf("m = %d/n",m);
    for(i =0; i<m+1;i++)
	    printf("0x%x ",wcstr[i]);
    printf("/n");
    return 0;
}
