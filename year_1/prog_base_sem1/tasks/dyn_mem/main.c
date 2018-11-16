#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
	//Allocate memory for result char.
	char *result = (char*) malloc(2 * sizeof(char));
	*result = (char*) calloc(2, sizeof(char));
	//Allocate memory for user input.
	char *myLine = (char*) malloc(100 * sizeof(char));
	myLine = (char*) calloc(100, sizeof(char));
	//Get the user input.
	gets_s(myLine, 100 * sizeof(char));
	//Save the last item in lower to *result.
	while (*myLine) {
		if (islower(*myLine)) {
			*result = *myLine;
			result[1] = '\0';
		}
		*myLine++;
	}
	//Print result.
	if (!isalpha(result[0])) {
		putchar('0');
	}
	else {
		putchar(result[0]);
	}
	free(result);
	free(myLine);

	return 0;
}