// gcc -O3 nonalign.c -o nonalign
// ./nonalign
// debug
// gdb ./nonalign
// run
// display /10i $pc
// find the movdqa and print the memory address
// p $rax or $r8

#include <stdio.h>
#include <stdlib.h>

int main () 
{
	char * ch;
	int i;

	short * u16;

	ch = (char *)malloc(2000);

	u16 = (short *)(ch + 1);

	for (i = 0; i < 100; i++)
		u16[i] = i;

	printf("%d %d", ch, u16);
}