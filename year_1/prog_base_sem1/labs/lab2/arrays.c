#include <stdlib.h>
#include <math.h>
#include <time.h>

void fillRand2(int arr[], int size) {
	int i, signNum;
	for (i = 0; i < size; ++i) {
		signNum = ((rand() % 2) == 0) ? -1 : 1;
		arr[i] = signNum * rand() % 256;
	}
	return;
}

int checkRand2(int arr[], int size) {
	int i;
	for (i = 0; i < size; ++i) {
		if (abs(arr[i]) > 255) {
			return 0;
		}
	}
	return 1;
}

float meanValue(int arr[], int size) {
	int i;
	float sum = 0;
	for (i = 0; i < size; ++i) {
		sum += arr[i];
	}
	return sum / size;
}

int minValue(int arr[], int size) {
	int i, minimal = arr[0];
	for (i = 0; i < size; ++i) {
		if (arr[i] < minimal) {
			minimal = arr[i];
		}
	}
	return minimal;
}

int meanIndex(int arr[], int size) {
	int i, index = 0;
	float minSub, minSubTemp;
	float averNum = meanValue(arr, size);
	minSub = abs(arr[0] - averNum);

	for (i = 0; i < size; ++i) {
		minSubTemp = abs(arr[i] - averNum);
		if (minSubTemp < minSub) {
			index = i;
			minSub = minSubTemp;
		}
	}
	return index;
}

int minIndex(int arr[], int size) {
	int i, index = 0, minimum = arr[0];
	for (i = size - 1; i >= 0; --i) {
		if (arr[i] < minimum) {
			minimum = arr[i];
			index = i;
		}
	}
	return index;
}

int maxOccurance(int arr[], int size) {
	int count = 1, tempCount;
	int popular = arr[0];
	int i, j;
	for (i = 0; i < (size - 1); i++) {
		tempCount = 0;
		for (j = 1; j < size; j++) {
			if (arr[i] == arr[j]) {
				tempCount++;
			}
		}
		if (tempCount > count) {
			popular = arr[i];
			count = tempCount;
		}
	}
	return popular;
}

int diff(int arr1[], int arr2[], int res[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		res[i] = arr1[i] - arr2[i];
	}
	for (i = 0; i < size; i++) {
		if (res[i] != 0) {
			return 0;
		}
	}
	return 1;
}

void add(int arr1[], int arr2[], int res[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		res[i] = arr1[i] + arr2[i];
	}
	return;
}

int gteq(int arr1[], int arr2[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr1[i] < arr2[i]) {
			return 0;
		}
	}
	return 1;
}

void land(int arr1[], int arr2[], int res[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		res[i] = arr1[i] & arr2[i];
	}
	return;
}