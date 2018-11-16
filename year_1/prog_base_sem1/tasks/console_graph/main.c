#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <ctype.h>

#define F1_COLOR FOREGROUND_RED | FOREGROUND_INTENSITY
#define F2_COLOR FOREGROUND_BLUE | FOREGROUND_INTENSITY

void setPos(int x, int y) {
	COORD myCoord = { x, y };
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(cnsHndlr, myCoord);
}
void setColor(int color) {
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cnsHndlr, color);
}
void drawSystem() {
	setPos(0, 0);
	setColor(007);
	puts("RED - F(x)=-2/(4*x-1)-1");
	puts("BLUE - F(x)=cos(x^2)+sn(2*x)^2+1");
	puts("WASD - move axis");
	puts("QE - scale");
	puts("X - exit");
	puts("ALWAYS PRESS ENTER");
	puts(">>");
}
void drawAxis(int x, int y, double scale) {
	double curX = 0, curY = 0;
	setPos(x, 0);
	while (curY <= 74) {
		putchar('|');
		curY = curY + 2 / scale;
		setPos(x, curY);
	}
	setPos(0, y);
	while (curX <= 149) {
		putchar('-');
		curX = curX + 2 / scale;
		setPos(curX, y);
	}
}
//F(x)=-2/(4*x-1)-1
void drawFunction1(int x, int y, double scale) {
	int i;
	double curX, curY;
	setColor(F1_COLOR);
	for (i = 0; i < 149; i+=1) {
		curX = i*0.5 - x / 2;
		curY = (-2 / (4 * curX * scale - 1) - 1) * 25 / 3 / scale;
		setPos(i, y - curY);
		putchar('*');
	}
}
//F(x)=cos(x^2)+sn(2*x)^2+1
void drawFunction2(int x, int y, double scale) {
	double i;
	double curX, curY;
	setColor(F2_COLOR);
	for (i = 0; i < 149; i+=0.1) {
		curX = i*0.5 - x / 2;
		curY = (cos(curX*scale) + pow(sin(2 * curX*scale), 2) + 1) * 25 / 3 / scale;
		setPos(i, y - curY);
		putchar('*');
	}
}

int main(void) {
	int xStart = 75, yStart = 38;
	double scale = 2;
	//Set standart stuff
	system("MODE CON: COLS=150 LINES=75");
	drawSystem();
	//Draw functions
	drawAxis(xStart, yStart, scale);
	drawFunction1(xStart, yStart, scale);
	drawFunction2(xStart, yStart, scale);
	//Get user answer
	char ch = '0';
	while (ch != 'x') {
		setPos(4, 6);
		ch = getchar();
		ch = tolower(ch);
		switch (ch) {
		case 'w':
			system("cls");
			yStart--;
			drawSystem();
			drawAxis(xStart, yStart, scale);
			drawFunction1(xStart, yStart, scale);
			drawFunction2(xStart, yStart, scale);
			break;
		case 's':
			system("cls");
			yStart++;
			drawSystem();
			drawAxis(xStart, yStart, scale);
			drawFunction1(xStart, yStart, scale);
			drawFunction2(xStart, yStart, scale);
			break;
		case 'a':
			system("cls");
			xStart -= 2;
			drawSystem();
			drawAxis(xStart, yStart, scale);
			drawFunction1(xStart, yStart, scale);
			drawFunction2(xStart, yStart, scale);
			break;
		case 'd':
			system("cls");
			xStart += 2;
			drawSystem();
			drawAxis(xStart, yStart, scale);
			drawFunction1(xStart, yStart, scale);
			drawFunction2(xStart, yStart, scale);
			break;
		case 'e':
			system("cls");
			drawSystem();
			scale = scale * sqrt(2);
			drawAxis(xStart, yStart, scale);
			drawFunction1(xStart, yStart, scale);
			drawFunction2(xStart, yStart, scale);
			break;
		case 'q':
			system("cls");
			drawSystem();
			scale = scale / sqrt(2);
			drawAxis(xStart, yStart, scale);
			drawFunction1(xStart, yStart, scale);
			drawFunction2(xStart, yStart, scale);
			break;
		default:
			continue;
		}
	}
	//End of the program
	return EXIT_SUCCESS;
}
