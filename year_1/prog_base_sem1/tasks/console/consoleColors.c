#include <stdio.h>
#include <Windows.h>

COORD curPos;
HANDLE consHndlr;
short* xCrdPtr;
short* yCrdPtr;

void drawItem(short xCoord, short yCoord) {
	int color;
	curPos.X = xCoord;
	curPos.Y = yCoord;
	SetConsoleCursorPosition(consHndlr, curPos);
	printf("*");
	Sleep(1);
	return;
}

void drawHorizontalRight(short xCrd, short yCrd, short endingX) {
	int myColor;
	while (xCrd < endingX-1) {
		drawItem(xCrd, yCrd);
		xCrd++;
		(*xCrdPtr)++;
		(*yCrdPtr) = yCrd;		
	}
	
}
void drawHorizontalLeft(short xCrd, short yCrd, short endingX) {
	while (xCrd > endingX) {
		drawItem(xCrd, yCrd);
		xCrd--;
		(*xCrdPtr)--;
		(*yCrdPtr) = yCrd;
	}

}
void drawVerticalUp(short xCrd, short yCrd, short endingY) {
	while (yCrd > endingY) {
		drawItem(xCrd, yCrd);
		yCrd--;
		(*xCrdPtr) = xCrd;
		(*yCrdPtr)--;
	}
}
void drawVerticalDown(short xCrd, short yCrd, short endingY) {
	while (yCrd < endingY-1) {
		drawItem(xCrd, yCrd);
		yCrd++;
		(*xCrdPtr) = xCrd;
		(*yCrdPtr)++;
	}
}



int main(void) {

	int i, j, counterY = 25 - 1, counterX = 80 - 10;
	int k;
	int counterXX = counterX;
	int color;
	short xCrd = 0, yCrd = 24;
	short x_LtUp = 0, x_RtUp = 80, x_LtDn = 0, x_RtDn = 80;
	short y_LtUp = 0, y_RtUp = 0, y_LtDn = 25, y_RtDn = 25;

	xCrdPtr = &xCrd;
	yCrdPtr = &yCrd;

	consHndlr = GetStdHandle(STD_OUTPUT_HANDLE);

	while (xCrd != 25/2) {		
		drawHorizontalRight(xCrd, yCrd, x_RtDn);
		drawVerticalUp(xCrd, yCrd, y_RtUp);
		drawHorizontalLeft(xCrd, yCrd, x_LtUp);
		drawVerticalDown(xCrd, yCrd, y_LtDn);
		xCrd++;
		yCrd--;
		x_RtDn--;
		y_RtUp++;
		x_LtUp++;
		y_LtDn--;
	}
	drawHorizontalRight(xCrd, yCrd, x_RtDn);
	drawItem(xCrd, yCrd);



	for (k = 0; k < 4; k++) {
		
		for (i = 0; i < 5; i++) {
			curPos.X = counterX;
			curPos.Y = counterY;
			counterXX++;
			switch ((counterXX) % 3) {
			case 0:
				color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
				break;
			case 1:
				color = BACKGROUND_BLUE | BACKGROUND_RED;
				break;
			case 2:
				color = BACKGROUND_RED;
				break;
			}
			for (j = 0; j < 5; j++) {
				SetConsoleCursorPosition(consHndlr, curPos);
				SetConsoleTextAttribute(consHndlr, color);
				printf("**********");
				Sleep(10);
				counterY--;
				curPos.Y = counterY;
			}
			counterX -= 10;
		}
		counterY = 24;
		counterX += 40;
	}

	curPos.X = 30;
	curPos.Y = 24;
	for (i = 0; i < 4; i++) {
		counterXX++;
		switch ((counterXX) % 3) {
		case 0:
			color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case 1:
			color = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case 2:
			color = BACKGROUND_RED;
			break;
		}
		for (j = 0; j < 5; j++) {
			SetConsoleCursorPosition(consHndlr, curPos);
			SetConsoleTextAttribute(consHndlr, color);
			printf("**********");
			Sleep(10);
			counterY--;
			curPos.Y = counterY;
		}
		curPos.X -= 10;
	}

	curPos.X = 70;
	curPos.Y = 19;
	counterY = 19;
	counterXX+=4;
	for (i = 0; i < 4; i++) {
		counterXX--;
		switch ((counterXX) % 3) {
		case 0:
			color = BACKGROUND_RED;
			break;
		case 1:
			color = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case 2:
			color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		}
		for (j = 0; j < 5; j++) {
			SetConsoleCursorPosition(consHndlr, curPos);
			SetConsoleTextAttribute(consHndlr, color);
			printf("**********");
			Sleep(10);
			counterY--;
			curPos.Y = counterY;
		}
		curPos.X -= 10;
	}

	curPos.X = 70;
	curPos.Y = 14;
	counterY = 14;
	counterXX--;
	for (i = 0; i < 3; i++) {
		counterXX++;
		switch ((counterXX) % 3) {
		case 0:
			color = BACKGROUND_RED;
			break;
		case 1:
			color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case 2:
			color = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		}
		for (j = 0; j < 5; j++) {
			SetConsoleCursorPosition(consHndlr, curPos);
			SetConsoleTextAttribute(consHndlr, color);
			printf("**********");
			Sleep(10);
			counterY--;
			curPos.Y = counterY;
		}
		curPos.X -= 10;
	}

	curPos.X = 70;
	curPos.Y = 9;
	counterY = 9;
	for (i = 0; i < 2; i++) {
		counterXX++;
		switch ((counterXX) % 3) {
		case 0:
			color = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case 1:
			color = BACKGROUND_RED;
			break;
		case 2:
			color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		}
		for (j = 0; j < 5; j++) {
			SetConsoleCursorPosition(consHndlr, curPos);
			SetConsoleTextAttribute(consHndlr, color);
			printf("**********");
			Sleep(10);
			counterY--;
			curPos.Y = counterY;
		}
		curPos.X -= 10;
	}

	curPos.X = 70;
	curPos.Y = 4;
	counterY = 4;
	for (j = 0; j < 5; j++) {
		color = BACKGROUND_BLUE | BACKGROUND_RED;
		SetConsoleCursorPosition(consHndlr, curPos);
		SetConsoleTextAttribute(consHndlr, color);
		printf("**********");
		Sleep(10);
		counterY--;
		curPos.Y = counterY;
	}

	curPos.X = 0;
	curPos.Y = 24;
	counterY = 24;
	for (j = 0; j < 5; j++) {
		color = BACKGROUND_BLUE | BACKGROUND_RED;
		SetConsoleCursorPosition(consHndlr, curPos);
		SetConsoleTextAttribute(consHndlr, color);
		printf("**********");
		Sleep(10);
		counterY--;
		curPos.Y = counterY;
	}

	curPos.X = 10;
	curPos.Y = 24;
	counterY = 24;
	for (i = 0; i < 2; i++) {
		counterXX++;
		switch ((counterXX) % 3) {
		case 0:
			color = BACKGROUND_RED;
			break;
		case 1:
			color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case 2:
			color = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		}
		for (j = 0; j < 5; j++) {
			SetConsoleCursorPosition(consHndlr, curPos);
			SetConsoleTextAttribute(consHndlr, color);
			printf("**********");
			Sleep(10);
			counterY--;
			curPos.Y = counterY;
		}
		curPos.X -= 10;
	}

	curPos.X = 20;
	curPos.Y = 24;
	counterY = 24;
	for (i = 0; i < 3; i++) {
		counterXX++;
		switch ((counterXX) % 3) {
		case 0:
			color = BACKGROUND_BLUE | BACKGROUND_RED;
			break;
		case 1:
			color = BACKGROUND_RED;
			break;
		case 2:
			color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		}
		for (j = 0; j < 5; j++) {
			SetConsoleCursorPosition(consHndlr, curPos);
			SetConsoleTextAttribute(consHndlr, color);
			printf("**********");
			Sleep(10);
			counterY--;
			curPos.Y = counterY;
		}
		curPos.X -= 10;
	}

	getchar();
	return EXIT_SUCCESS;
}