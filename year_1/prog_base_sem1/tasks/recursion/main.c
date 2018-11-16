#include <stdio.h>
#include <string.h>

#define ERROR '0'
#define ARRLEN 100

char repSymbol(char *, size_t);

int main(void) {

	//Get the string from user.
	char buff[ARRLEN];
	puts("Please, enter your line! :");
	gets_s(buff, ARRLEN * sizeof(char));
	int len = strlen(buff);

	//Find repeatable symbol
	char resultCh = repSymbol(buff, len);
	printf("%c\n", resultCh);

	getchar();
	return 0;
}

char repSymbol(char *str, size_t len) {
	if (1 == len) {
		return ERROR;
	}
	else if (str[len] == str[len-1]) {
		return str[len];
	}
	else {
		repSymbol(str, len - 1);
	}
}