#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define ARRLENGTH 3

void setTextColor(int color) {
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cnsHndlr, color);
}

void setCursorPosition(int x, int y) {
	COORD myCoord = { x, y };
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(cnsHndlr, myCoord);
}

int main(void) {

	time_t t;
	int i, j, sum = 0;
	float rawLength;
	float percentage;
	srand((unsigned)time(&t));
	//Initialize array, print numbers, define Sum
	unsigned int myArr[ARRLENGTH];
	for (i = 0; i < ARRLENGTH; i++) {
		myArr[i] = rand() % 10;
		sum += myArr[i];
		setCursorPosition(5 * i, 0);
		printf("%d", myArr[i]);
	}
	//Print raws
	for (i = 0; i < ARRLENGTH; i++) {
		percentage = ((float)myArr[i] * 100.0) / (float)sum;
		rawLength = (12 * percentage) / 100;
		if (rawLength < 1.0 && rawLength > 0) {
			rawLength = 1.0;
		}
		for (j = 0; j < (int)rawLength; j++) {
			setCursorPosition(5 * i, 12 - j);
			setTextColor(BACKGROUND_RED | BACKGROUND_INTENSITY);
			printf(" ");
		}
		rawLength = 0;
	}
	//Print stuff :*
	for (i = 0; i < 79; i++) {
		setCursorPosition(i, 13);
		setTextColor(0x080808);
		printf("-");
	}
	

	getchar();
	return 0;
}