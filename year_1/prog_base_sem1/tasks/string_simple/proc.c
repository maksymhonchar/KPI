#include <string.h>
#include <stdio.h>

char * process(char * resultStr, const char * textLines [],
	int linesNum, const char * extraStr) {

	int i, status = 0;
	char lastLineEqUpLow[100];
	char *helpingPtr;
	helpingPtr = lastLineEqUpLow;
	//Find the last line, that has equal num of uppers and lowers.
	for (i = 0; i < linesNum; i++) {
		int j = 0, lower = 0, upper = 0;
		char *line = textLines[i];
		while (line[j] != '\0') {
			if (line[j] >= 'A' && line[j] <= 'Z') {
				upper++;
			}
			if (line[j] >= 'a' && line[j] <= 'z') {
				lower++;
			}
			j++;
		}
		//Find the exact line and save it in helpingPtr.
		if (upper == lower) {
			status = 1;
			helpingPtr = line;
		}
	}
	//If helpingPtr wasn`t filled.
	if (status == 0) {
		strcpy(resultStr, "0 NULL");
		return resultStr;
	}	
	//Add all items from helpingPtr to array /(>_<)
	i = 0;
	char finalArray[100];
	while (helpingPtr[i] != '\0') {
		finalArray[i] = helpingPtr[i];
		i++;
	}
	finalArray[i] = '\0';
	//count upper and lower letters
	int finalLen = i;
	int upper = 0, lower = 0;
	for (i = 0; i < finalLen; i++) {
		if (finalArray[i] >= 'A' && finalArray[i] <= 'Z') {
			upper++;
		}
	}
	//An array for result: [0] - digit, [1] - space, [2]-inf - lower letters
	char theLastArrayIPromise[100];
	//Add a number and space.
	snprintf(theLastArrayIPromise, sizeof(theLastArrayIPromise), "%d ", upper);
	//Add lower letters.
	int j = 2;	
	for (i = 0; i < finalLen; i++) {
		if (finalArray[i] >= 'a' && finalArray[i] <= 'z') {
			theLastArrayIPromise[j] = finalArray[i];
			j++;
		}
	}
	theLastArrayIPromise[j] = '\0';
	//Copy result to resultStr
	char *kek = theLastArrayIPromise;
	strcpy(resultStr, kek);

	return resultStr;
}