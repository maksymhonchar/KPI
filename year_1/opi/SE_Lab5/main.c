//
// Лабораторна робота №5 
// Обчислення на мові асемблера виразу average(a,b)*c
// 
// Гончар Максим КП-51
//

#include <stdio.h>
#include <limits.h>
#include "multiply.h"


int main() {

	int a, b, c;
	int result;
	int status = 0;

	do {
		status = scanf("%d%d%d", &a, &b, &c);
		//fflush(stdin);
	} while (status < 3);


	//Or set your a,b,c var`s here
	/*a = 5;
	b = 3;
	c = 7;*/

	__asm {
		lea eax, result
			push eax
			mov eax, c
			push eax
			mov eax, b
			push eax
			mov eax, a
			push eax

			call mul_avr

			mov status, eax
			pop ebx
			pop ebx
			pop ebx
			pop ebx
	}

	if (status)
		printf("Overflow\n");
	//result = (int)average(a,b) * c
	else
		printf("%d\n", result);

	return 0;
}