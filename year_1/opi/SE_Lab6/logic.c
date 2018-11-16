#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "logic.h"

void initialize_array(int* arrBegin, int*arrEnd) {

	srand((unsigned int) time(NULL));
	while (arrBegin != arrEnd)
	{
		*arrBegin = rand() % 100;
		printf("%d ", *arrBegin);
		arrBegin++;
	}
}

int findEntry(int* arrBegin, int* arrEnd, int P, int* index1Ptr) {

	int itemInArray = 0;
	int index1 = 101, index2 = 101;
	int* tempArrBegin = arrBegin, tempArrEnd = arrEnd;

	while (tempArrBegin != tempArrEnd) {
		if (*tempArrBegin == P) {
			index2 = itemInArray;
		}
		tempArrBegin++;
		itemInArray++;
	}

	while (arrEnd != (arrBegin - 1)) {
		if (*arrEnd == P) {
			index1 = itemInArray;
		}
		arrEnd--;
		itemInArray--;
	}
	*index1Ptr = index1;

	return index2;
}

int copy(int mas1 [], int mas2 [], int n, int l, int r) {

	int i;
	int* ptrOne = mas1;
	int* ptrTwo = mas2;
	while (l != r + 1)
	{
		*ptrTwo = *(ptrOne + l);
		l++;
		ptrTwo++;
	}
	return 0;
}

int multiplication(int mas []) {
	int index1, index2, result;
	int* index1Ptr = &index1;
	index2 = findEntry(mas, mas + 10, specialNumber, index1Ptr);
	result = index1*index2;

	return result;
}

