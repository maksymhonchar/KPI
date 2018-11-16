#include <stdio.h>
#include <stdlib.h>
#include "logic.h"


int main(void) {

	int i;
	int arr[10] = { 1,2,5,6,7,8,5,9,5,10 };
	//int arr[10];
	int arr2[10];
	int index1, index2, multResult;
	int* index1Ptr = &index1;

	//initialize_array(arr, arr + 10);

	index2 = findEntry(arr, arr + 10, specialNumber, index1Ptr);
	printf("\nindex 1 is %d ", index1);
	printf("\nindex 2 is %d ", index2);

	copy(arr, arr2, 10, index1, index2);

	multResult = multiplication(arr);
	printf("\nMultiplication result is %d", multResult);

	puts("\n");

	for (i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
		printf("%d\n", arr2[i]);
	}

	getchar();
	return EXIT_SUCCESS;
}