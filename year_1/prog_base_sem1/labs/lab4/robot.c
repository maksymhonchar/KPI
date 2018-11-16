#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>
#include "RobotsNWeapons.h"

void setPos(int x, int y) {
	COORD myCoord = { x, y };
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(cnsHndlr, myCoord);
}
void setColor(int color) {
	HANDLE cnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cnsHndlr, color);
}
void drawRectangle(int xStart, int xEnd, int yStart, int yEnd, int color) {
	int i, j;
	setColor(color);
	for (i = xStart; i <= xEnd; i++) {
		for (j = yStart; j <= yEnd; j++) {
			setPos(i, j);
			printf(" ");
		}
	}
	setColor(TEXTCOLOR);
}
void drawCoolBorders(int xStart, int xEnd, int yStart, int yEnd, int color) {
	int i;
	setColor(color);
	for (i = xStart; i < xEnd; i++) {
		setPos(i, yStart);
		putchar(' ');
		setPos(i, yEnd - 1);
		putchar(' ');
	}
	for (i = yStart; i < yEnd; i++) {
		setPos(xStart, i);
		putchar(' ');
		setPos(xEnd - 1, i);
		putchar(' ');
	}
}

void displayRobotInfo(struct Robot *rbtPtr, int x, int y) {
	setPos(x, y);
	printf("Robot Name : %s", rbtPtr->name);
	setPos(x, y + 1);
	printf("Strength : %d", rbtPtr->strength);
	setPos(x, y + 2);
	printf("Agility : %d", rbtPtr->agility);
	setPos(x, y + 3);
	printf("Intelligence : %d", rbtPtr->intelligence);
	setPos(x, y + 4);
	printf("Damage : %d", rbtPtr->damage);
	setPos(x, y + 5);
	printf("HP : %d", rbtPtr->hp);
	setPos(x, y + 6);
	printf("Robot weapon : %s", rbtPtr->robotWeapon.name);
}
void displayWeaponInfo(struct Weapon curWpn, int x, int y) {
	setPos(x, y);
	printf("%s +%d", curWpn.name, curWpn.damage);
}
void createRobotByParameters(struct Robot *rbtPtr, char *name, int strength, int agility, int intelligence, struct Weapon curWeapon) {
	strncpy_s(rbtPtr->name, ROBOT_NAME * sizeof(char), name, ROBOT_NAME);
	rbtPtr->strength = strength;
	rbtPtr->agility = agility;
	rbtPtr->intelligence = intelligence;
	rbtPtr->damage = 0;
	rbtPtr->hp = 100;
	rbtPtr->robotWeapon = curWeapon;
}
void deleteRobot(struct Robot *rbtPtr) {
	//delete robot = change name to '\0'
	rbtPtr->name[0] = '\0';
}

void readWpnLst(struct Weapon wpnLst[]) {
	FILE *fp;
	fp = fopen("weapons.txt", "r");
	char buff[100], *token, wpnName[WEAPON_NAME];
	int wpnDamage = 0, i = 0;
	//Check all lines in weapons.txt
	while (fgets(buff, 100 * sizeof(char), fp) != NULL) {
		token = strtok(buff, " ");
		strcpy(wpnName, token);
		token = strtok(NULL, " ");
		wpnDamage = atoi(token);
		//Add info to wpnLst
		strncpy_s(wpnLst[i].name, WEAPON_NAME*sizeof(char), wpnName, WEAPON_NAME*sizeof(char));
		wpnLst[i].damage = wpnDamage;
		//Go to the next line
		i++;
	}
	//Close file stream
	fclose(fp);	
	//Go through array and fill the other stuff with \0
	int j;
	for (j = i; j < WEAPONS_C; j++) {
		wpnLst[j].name[0] = '\0';
	}
}
void readRbtLst(struct Robot rbtLst [], struct Weapon wpnLst []) {
	FILE *fp;
	fp = fopen("robots.txt", "r");
	char buff[100], *token, rbtName[ROBOT_NAME], wpnName[WEAPON_NAME];
	int rbtStrength = 0, rbtAgil = 0, rbtIntell = 0, rbtDamage = 0, rbtHP = 0, i = 0, k, status = 0;
	//Check all lines in robots.txt
	while (fgets(buff, 100 * sizeof(char), fp) != NULL) {
		token = strtok(buff, " ");
		strcpy(rbtName, token);
		token = strtok(NULL, " ");
		strcpy(wpnName, token);
		token = strtok(NULL, " ");
		rbtStrength = atoi(token);
		token = strtok(NULL, " ");
		rbtAgil = atoi(token);
		token = strtok(NULL, " ");
		rbtIntell = atoi(token);
		token = strtok(NULL, " ");
		rbtDamage = atoi(token);
		token = strtok(NULL, " ");
		rbtHP = atoi(token);
		//Add info to rbtList
		for (k = 0; k < WEAPONS_C; k++) {
			if (strcmp(wpnName, wpnLst[k].name) == 0) {
				createRobotByParameters(&rbtLst[i], rbtName, rbtStrength, rbtAgil, rbtIntell, wpnLst[k]);
				rbtLst[i].damage += wpnLst[k].damage;
				status = 1;
			}
			else {
				continue;
			}
		}
		if (status == 0) {
			createRobotByParameters(&rbtLst[i], rbtName, rbtStrength, rbtAgil, rbtIntell, wpnLst[0]);
		}
		//Go to the next line
		i++;
	}
	//Close file stream
	fclose(fp);
	//Go through array and fill the other stuff with \0
	int j;
	for (j = i; j < ROBOTS_C; j++) {
		rbtLst[j].name[0] = '\0';
	}	
}
void writeWpnLst(struct Weapon wpnLst []) {
	FILE *fp;
	fp = fopen("weapons.txt", "w+");
	int i;
	for (i = 0; i < WEAPONS_C; i++) {
		if (wpnLst[i].name[0] != '\0') {
			fprintf(fp, "%s %d\n", wpnLst[i].name, wpnLst[i].damage);
		}
		else {
			continue;
		}
	}
	//Close file stream
	fclose(fp);
}
void writeRbtLst(struct Robot rbtLst []) {
	FILE *fp;
	fp = fopen("robots.txt", "w+");
	int i;
	for (i = 0; i < ROBOTS_C; i++) {
		if (rbtLst[i].name[0] != '\0') {
			fprintf(fp, "%s %s %d %d %d %d %d\n", rbtLst[i].name, rbtLst[i].robotWeapon.name, rbtLst[i].strength, rbtLst[i].agility, rbtLst[i].intelligence, rbtLst[i].damage, rbtLst[i].hp);
		}
		else {
			continue;
		}
	}
	//Close file stream
	fclose(fp);
}

void drawRobot(int x, int y, char ch) {
	//<x;y> - neck position
	int i;
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	setPos(x - 1, y - 4); //left eye
	setColor(128);
	putchar('°');
	setPos(x + 1, y - 4); //right eye
	putchar('°');
	setColor(124);
	setPos(x - 1, y - 2); //lips
	putchar('='); 
	setPos(x, y - 2);
	putchar('=');
	setPos(x + 1, y - 2);
	putchar('=');
	//Draw body
	drawRectangle(x - 2, x + 2, y + 1, y + 6, ROBOTCOLOR);
	//Draw arms
	drawRectangle(x - 5, x - 3, y + 2, y + 2, ROBOTCOLOR); //left arm
	drawRectangle(x + 3, x + 5, y + 2, y + 2, ROBOTCOLOR); //right arm
	//Draw legs
	drawRectangle(x - 1, x - 1, y + 7, y + 8, ROBOTCOLOR); //left leg
	drawRectangle(x + 1, x + 1, y + 7, y + 8, ROBOTCOLOR); //right leg
	//Print identificator
	setPos(x, y + 2);
	setColor(124);
	putchar(ch);
	//Set standart color
	setColor(007);
}
void robotHalfTurnLeft(int x, int y) {
	//<x;y> - neck position
	int i;
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	setPos(x - 1, y - 4); //left eye
	setColor(128);
	putchar('°');
	setPos(x + 1, y - 4); //right eye
	putchar('°');
	setColor(124);
	setPos(x - 1, y - 2); //lips
	putchar('=');
	setPos(x, y - 2);
	putchar('=');
	setPos(x + 1, y - 2);
	putchar('=');
	//draw body
	drawRectangle(x - 2, x + 1, y + 1, y + 6, ROBOTCOLOR);
	//draw arms
	drawRectangle(x - 5, x - 3, y + 2, y + 2, ROBOTCOLOR); //left arm
	drawRectangle(x + 2, x + 3, y + 2, y + 2, ROBOTCOLOR); //right arm
	//draw legs
	drawRectangle(x - 2, x - 2, y + 7, y + 8, ROBOTCOLOR); //left leg
	drawRectangle(x, x, y + 7, y + 8, ROBOTCOLOR); //right leg
	//Set standart color!
	setColor(007);
}
void robotHalfTurnRight(int x, int y) {
	//<x;y> - neck position
	int i;
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	setPos(x - 1, y - 4); //left eye
	setColor(128);
	putchar('°');
	setPos(x + 1, y - 4); //right eye
	putchar('°');
	setColor(124);
	setPos(x - 1, y - 2); //lips
	putchar('=');
	setPos(x, y - 2);
	putchar('=');
	setPos(x + 1, y - 2);
	putchar('=');
	//draw body
	drawRectangle(x - 1, x + 2, y + 1, y + 6, ROBOTCOLOR);
	//draw arms
	drawRectangle(x - 5, x - 4, y + 2, y + 2, ROBOTCOLOR); //left arm
	drawRectangle(x + 2, x + 4, y + 2, y + 2, ROBOTCOLOR); //right arm
	//draw legs
	drawRectangle(x - 1, x - 1, y + 7, y + 8, ROBOTCOLOR); //left leg
	drawRectangle(x + 2, x + 2, y + 7, y + 8, ROBOTCOLOR); //right leg
	//Set standart color!
	setColor(007);
}
void robotTurnLeftStep1(int x, int y) {
	//<x;y> - neck position
	int i;
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	//draw body
	drawRectangle(x - 2, x + 2, y + 1, y + 6, ROBOTCOLOR);
	drawRectangle(x, x, y + 3, y + 3, 199); //nashivka
	//draw arms
	drawRectangle(x - 3, x - 3, y + 2, y + 2, ROBOTCOLOR); //up arm
	drawRectangle(x - 5, x - 3, y + 3, y + 3, ROBOTCOLOR); //down arm
	//draw legs
	drawRectangle(x - 1, x - 1, y + 7, y + 7, ROBOTCOLOR); //left leg
	drawRectangle(x + 1, x + 1, y + 7, y + 8, ROBOTCOLOR); //right leg
	//Set standart color
	setColor(007);
}
void robotTurnLeftStep2(int x, int y) {
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	drawRectangle(x - 1, x - 1, y - 4, y - 4, 199);	//nashivka
	//draw body
	drawRectangle(x - 2, x + 2, y + 1, y + 6, ROBOTCOLOR);
	drawRectangle(x, x, y + 3, y + 3, 199);	//nashivka
	//draw arms
	drawRectangle(x - 5, x - 3, y + 2, y + 2, ROBOTCOLOR); //up arm
	drawRectangle(x - 3, x - 3, y + 3, y + 3, ROBOTCOLOR); //down arm
	//draw legs
	drawRectangle(x - 1, x - 1, y + 7, y + 8, ROBOTCOLOR); //left leg
	drawRectangle(x + 1, x + 1, y + 7, y + 7, ROBOTCOLOR); //right leg
	//Set standart color!
	setColor(007);
}
void robotTurnRightStep1(int x, int y) {
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	//draw body
	drawRectangle(x - 2, x + 2, y + 1, y + 6, ROBOTCOLOR);
	drawRectangle(x, x, y + 3, y + 3, 199); //nashivka
	//draw arms
	drawRectangle(x + 3, x + 3, y + 2, y + 2, ROBOTCOLOR); //up arm
	drawRectangle(x + 3, x + 5, y + 3, y + 3, ROBOTCOLOR); //down arm
	//draw legs
	drawRectangle(x - 1, x - 1, y + 7, y + 7, ROBOTCOLOR); //left leg
	drawRectangle(x + 1, x + 1, y + 7, y + 8, ROBOTCOLOR); //right leg
	//Set standart color!
	setColor(007);
}
void robotTurnRightStep2(int x, int y) {
	//draw neck
	setPos(x, y);
	setColor(ROBOTCOLOR);
	putchar(' ');
	//draw head
	drawRectangle(x - 2, x + 2, y - 5, y - 1, ROBOTCOLOR);
	drawRectangle(x + 1, x + 1, y - 4, y - 4, 199); //nashivka
	//draw body
	drawRectangle(x - 2, x + 2, y + 1, y + 6, ROBOTCOLOR);
	drawRectangle(x, x, y + 3, y + 3, 199); //nashivka
	//draw arms
	drawRectangle(x + 3, x + 5, y + 2, y + 2, ROBOTCOLOR); //up arm
	drawRectangle(x + 3, x + 3, y + 3, y + 3, ROBOTCOLOR); //down arm
	//draw legs
	drawRectangle(x - 1, x - 1, y + 7, y + 8, ROBOTCOLOR); //left leg
	drawRectangle(x + 1, x + 1, y + 7, y + 7, ROBOTCOLOR); //right leg
	//Set standart color!
	setColor(007);
}
void robotGoNalevo(int border, int X, int Y, int *xPtr, int *yPtr) {
	//Move robot to the border
	while (X >= border) {
		robotTurnLeftStep1(X, Y);
		Sleep(100);
		drawRectangle(X - 5, X + 5, Y - 5, Y + 11, 0x00);
		X -= 2;
		robotTurnLeftStep2(X, Y);
		Sleep(100);
		drawRectangle(X - 5, X + 5, Y - 5, Y + 11, 0x00);
		X -= 2;
	}
	//Save position
	*xPtr = X;
	*yPtr = Y;
	//Print the robot again!
	drawRobot(X, Y, 'O');
}
void robotGoNapravo(int border, int X, int Y, int *xPtr, int *yPtr) {
	while (X < border) {
		robotTurnRightStep1(X, Y);
		Sleep(100);
		drawRectangle(X - 5, X + 5, Y - 5, Y + 11, 0x00);
		X += 2;
		robotTurnRightStep2(X, Y);
		Sleep(100);
		drawRectangle(X - 5, X + 5, Y - 5, Y + 11, 0x00);
		X += 2;
	}
	//Save position
	*xPtr = X;
	*yPtr = Y;
	//Print the robot again!
	drawRobot(X, Y, 'O');
}
void robotTalks(char *str, size_t len, int x, int y, int textX, int textY) {
	int i, status = 1;
	time_t t;
	srand((unsigned int) time(&t));
	for (i = 0; i < (int) len; i++) {
		setPos(textX, textY);
		setColor(TEXTCOLOR);
		printf("%c", str[i]);
		//Change lips
		if (status%2 == 0) {
			setColor(124);
			setPos(x - 1, y - 2);
			putchar('=');
			setPos(x, y - 2);
			putchar('=');
			setPos(x + 1, y - 2);
			putchar('=');
			status+=rand()%10;
			Sleep(rand() % 100);
		}
		else if (status%2 == 1) {
			setColor(ROBOTCOLOR);
			setPos(x - 1, y - 2);
			putchar(' ');
			setPos(x + 1, y - 2);
			putchar(' ');
			status += rand() % 10;
			Sleep(rand() % 100);
		}
		textX++;		
	}
	//set lips to default nigga
	setColor(124);
	setPos(x - 1, y - 2);
	putchar('=');
	setPos(x, y - 2);
	putchar('=');
	setPos(x + 1, y - 2);
	putchar('=');
}

void showHelpMenu(int x, int y) {
	setColor(HELPCOLOR);
	setPos(x, y + 1);	printf("angar - show angar"); //+
	setPos(x, y + 2);	printf("weaponary - show weaponary"); //+
	setPos(x, y + 3);	printf("createRbt - create robot"); //+
	setPos(x, y + 4);	printf("createWpn - create weapon"); //+
	setPos(x, y + 5);	printf("changeRbt - change robot"); //+
	setPos(x, y + 6);	printf("deleteRbt - delete robot"); //+
	setPos(x, y + 7);	printf("dynMem - ?!?intriga?"); //+
	setPos(x, y + 8);	printf("battle - go battle boyz");
	setPos(x, y + 9);	
	setPos(x, y + 10);	printf("exit - exit from the program"); //+
	setPos(x, y + 11);	printf("help - show help"); //+
	setPos(x, y + 12);	
	setPos(x, y + 13);	
}
void showWeaponaryMenu(int x, int y, struct Weapon weaponsList[]) {
	int i;
	for (i = 0; i < WEAPONS_C; i++) {
		if (weaponsList[i].name[0] != '\0') {
			setColor(TEXTCOLOR);
			setPos(x - 2, i + 25);
			printf("%d)", i+1);
			displayWeaponInfo(weaponsList[i], x, i + 25);
		}
		else {
			continue;
		}
	}
}
void showAngarMenu(int x, int y, struct Robot robotsList []) {
	setColor(HELPCOLOR);
	int i;
	char ch[100];
	for (i = 1; i < ROBOTS_C; i++) {
		if (robotsList[i].name[0] != '\0') {
			setColor(TEXTCOLOR);
			displayRobotInfo(&robotsList[i], x, y);
			setPos(x, y + 9);
			printf("Next robot - Y/N");
			setPos(x, y + 10);
			printf(">>");
			setPos(x + 3, y + 10);
			gets_s(ch, 100 * sizeof(char));
			if (tolower(ch[0]) == 'n') {
				break;
			}
			else if (tolower(ch[0]) == 'y') {
				drawRectangle(3, 30, 25, 45, 0x00);
				drawRectangle(3, 44, 25, 25, 0x00);
				drawRectangle(3, 32, 31, 31, 0x00);
				continue;
			}
			else {
				setPos(x, y + 11);
				printf("Please, enter Y or N");
				break;
			}
		}
		else {
			continue;
		}
	}
}

void behavior() {
	system("cls");
	//Main lists of robots & weapons, that will be printed to file
	struct Weapon weaponsList[WEAPONS_C];
	struct Robot robotsList[ROBOTS_C];
	//Set weaponsList and robotsList from file
	readWpnLst(weaponsList);
	readRbtLst(robotsList, weaponsList);
	//Set new console size and default stuff
	system(CONSOLESIZE);
	drawCoolBorders(0, 100, 0, 48, BORDERCOLOR);
	setPos(40, 48);
	setColor(252);
	printf("Gonchar Maxim KP51 Lab4");
	//Robot animation
	int xStart_robotGreetings = 12, yStart_robotGreetings = 30;
	//Middle robot
	drawRobot(xStart_robotGreetings, yStart_robotGreetings, 'L');
	Sleep(1000);
	drawRectangle(xStart_robotGreetings - 5, xStart_robotGreetings + 5, yStart_robotGreetings - 5, yStart_robotGreetings + 11, 0x00);
	robotHalfTurnLeft(xStart_robotGreetings, yStart_robotGreetings);
	Sleep(100);
	drawRectangle(xStart_robotGreetings - 5, xStart_robotGreetings + 5, yStart_robotGreetings - 5, yStart_robotGreetings + 11, 0x00);	
	robotGoNapravo(45, xStart_robotGreetings, yStart_robotGreetings, &xStart_robotGreetings, &yStart_robotGreetings);
	//Right robot
	int temp1, temp2;
	robotGoNalevo(60, 87, 32, &temp1, &temp2);
	//Left robot
	robotGoNapravo(35, 12, 32, &temp1, &temp2);
	//Middle robot talks
	char *str = "Greetings, traveler. Welcome to the valley of old robots.";
	robotTalks(str, strlen(str), xStart_robotGreetings, yStart_robotGreetings, xStart_robotGreetings-(strlen(str)/2), yStart_robotGreetings-10);
	char *str2 = "Now, choose what you want to do!";
	robotTalks(str2, strlen(str2), xStart_robotGreetings, yStart_robotGreetings, xStart_robotGreetings - (strlen(str2) / 2), yStart_robotGreetings - 9);
	char *str3 = "Type 'help' if you don`t understand some things.";
	robotTalks(str3, strlen(str3), xStart_robotGreetings, yStart_robotGreetings, xStart_robotGreetings - (strlen(str3) / 2), yStart_robotGreetings - 8);
	//User choses some stuff
	char userInput_greetings[100];
	//Check or user input
	while (strcmp(userInput_greetings, "exit") != 0) {
		setColor(TEXTCOLOR);
		setPos(38, 9);
		printf("Your input:");
		setPos(38, 10);
		printf(">>");	
		setPos(41, 10);
		gets_s(userInput_greetings, 100 * sizeof(char));
		//tolower input
		int i;
		for (i = 0; i < 100; i++) {
			userInput_greetings[i] = tolower(userInput_greetings[i]);
		}
		//Show help menu on the greetings window
		if (strcmp(userInput_greetings, "help") == 0) {
			//Move right robot. Wave a hand
			for (i = 0; i < 15; i++) {
				if (i % 2 == 0) {
					drawRectangle(62, 64, 32, 35, 0x00);
					setColor(ROBOTCOLOR);
					setPos(62, 34);
					printf(" ");
					setPos(63, 34);
					printf(" ");
					setPos(64, 33);
					printf(" ");
					Sleep(100);
				}
				if (i % 2 == 1) {
					drawRectangle(62, 64, 32, 35, 0x00);
					setColor(ROBOTCOLOR);
					setPos(62, 34);
					printf(" ");
					setPos(63, 34);
					printf(" ");
					setPos(64, 34);
					printf(" ");
					Sleep(100);
				}
			}
			//Show help menu
			showHelpMenu(70, 25);
			setPos(70, 40);
			printf("Press any key to continue");
			getchar();
			//In the end - restore robot`s hand!
			setColor(ROBOTCOLOR);
			setPos(64, 34);
			printf(" ");
			setColor(0x00);
			setPos(64, 33);
			printf(" ");
			//In the end - clear help info
			drawRectangle(69, 98, 24, 45, 0x00);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
		}
		//Show weaponary menu on the greetings window
		else if (strcmp(userInput_greetings, "weaponary") == 0) {
			//Move left robot. Wave a hand
			for (i = 0; i < 15; i++) {
				if (i % 2 == 0) {
					drawRectangle(31, 33, 32, 35, 0x00);
					setColor(ROBOTCOLOR);
					setPos(31, 33);
					printf(" ");
					setPos(32, 34);
					printf(" ");
					setPos(33, 34);
					printf(" ");
					Sleep(100);
				}
				if (i % 2 == 1) {
					drawRectangle(31, 33, 32, 35, 0x00);
					setColor(ROBOTCOLOR);
					setPos(31, 34);
					printf(" ");
					setPos(32, 34);
					printf(" ");
					setPos(33, 34);
					printf(" ");
					Sleep(100);
				}
			}
			//Show weaponary menu
			showWeaponaryMenu(5, 25, weaponsList);
			setPos(5, 40);
			printf("Press any key to continue");
			getchar();
			//In the end - restore robot`s hand!
			setColor(ROBOTCOLOR);
			setPos(31, 34);
			printf(" ");
			setColor(0x00);
			setPos(31, 33);
			printf(" ");
			//In the end - clear weaponary info
			drawRectangle(3, 30, 25, 45, 0x00);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
		}
		//Show robots
		else if (strcmp(userInput_greetings, "angar") == 0) {
			//Move left robot. Wave a hand
			for (i = 0; i < 15; i++) {
				if (i % 2 == 0) {
					drawRectangle(31, 33, 32, 35, 0x00);
					setColor(ROBOTCOLOR);
					setPos(31, 33);
					printf(" ");
					setPos(32, 34);
					printf(" ");
					setPos(33, 34);
					printf(" ");
					Sleep(100);
				}
				if (i % 2 == 1) {
					drawRectangle(31, 33, 32, 35, 0x00);
					setColor(ROBOTCOLOR);
					setPos(31, 34);
					printf(" ");
					setPos(32, 34);
					printf(" ");
					setPos(33, 34);
					printf(" ");
					Sleep(100);
				}
			}
			//Show angar menu
			showAngarMenu(5, 25, robotsList);
			setColor(TEXTCOLOR);
			setPos(5, 39);
			printf("That was the last robot.");
			setPos(5, 40);
			printf("Press any key to continue");
			getchar();
			//In the end - restore robot`s hand!
			setColor(ROBOTCOLOR);
			setPos(31, 34);
			printf(" ");
			setColor(0x00);
			setPos(31, 33);
			printf(" ");
			//In the end - clear angar info
			drawRectangle(3, 30, 25, 45, 0x00);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
		}
		//Create robot option
		else if (strcmp(userInput_greetings, "createrbt") == 0) {
			//Clear user input area
			drawRectangle(2, 98, 2, 23, 0x00);
			//Draw 'angar' border
			int i;
			setColor(013);
			for (i = 2; i < 50; i++) {
				setPos(i, 22);
				printf("*");
				setPos(98 - i, 22);
				printf("*");
				Sleep(50);
			}
			//print ">>ANGAR SECTION<<"
			char *angarTitle = ">>ROBOTS_CREATE SECTION<<";
			for (i = 0; i < (int)strlen(angarTitle); i++) {
				setPos(i + 38, 21);
				printf("%c", angarTitle[i]);
				Sleep(rand() % 100);
			}
			//Init robot by user
			//get name
			setColor(TEXTCOLOR);
			setPos(35, 10);
			printf("Enter robot name :");
			setPos(35, 11);
			printf(">>");
			setPos(38, 11);
			char robotName_user[ROBOT_NAME];
			gets_s(robotName_user, ROBOT_NAME*sizeof(char));
			//Clear user input area. Do it every time.
			drawRectangle(2, 98, 2, 20, 0x00);
			//get strength
			setPos(35, 10);
			printf("Enter robot strength");
			setPos(35, 11);
			printf(">>");
			setPos(38, 11);
			int strength;
			scanf_s("%d", &strength);
			getchar();
			drawRectangle(2, 98, 2, 20, 0x00);
			//get agility
			setPos(35, 10);
			printf("Enter robot agility");
			setPos(35, 11);
			printf(">>");
			setPos(38, 11);
			int agility;
			scanf_s("%d", &agility);
			getchar();
			drawRectangle(2, 98, 2, 20, 0x00);
			//get intelligence
			setPos(35, 10);
			printf("Enter robot intelligence");
			setPos(35, 11);
			printf(">>");
			setPos(38, 11);
			int intelligence;
			scanf_s("%d", &intelligence);
			getchar();
			drawRectangle(2, 98, 2, 20, 0x00);
			//get weapon
			setPos(35, 10);
			printf("Enter robot weapon");
			setPos(35, 11);
			printf(">>");
			setColor(TEXTCOLOR);
			//Show weaponary menu
			showWeaponaryMenu(5, 25, weaponsList);
			//Get the weapon name
			setPos(38, 11);
			char weaponName[WEAPON_NAME];
			gets_s(weaponName, WEAPON_NAME * sizeof(char));
			//Add a weapon
			int status = 0;
			//check for free sections for robot
			int freeRobot_Num;
			for (i = 0; i < ROBOTS_C; i++) {
				if (robotsList[i].name[0] != '\0') {
					freeRobot_Num = i + 1;
				}
				else {
					continue;
				}
			}
			for (i = 0; i < WEAPONS_C; i++) {
				if (strcmp(weaponsList[i].name, weaponName) == 0) {
					createRobotByParameters(&robotsList[freeRobot_Num], robotName_user, strength, agility, intelligence, weaponsList[i]);
					robotsList[freeRobot_Num].damage += weaponsList[i].damage;
					status = 1;
				}
				else {
					continue;
				}
			}
			if (status == 0) {
				setPos(35,13);
				setColor(TEXTCOLOR);
				printf("You`ve putted wrong name of weapon");
				Sleep(1000);
				createRobotByParameters(&robotsList[freeRobot_Num], robotName_user, strength, agility, intelligence, weaponsList[0]);
			}
			//Clear the area! And return stuff
			drawRectangle(2, 98, 2, 22, 0x00);
			setColor(TEXTCOLOR);
			setPos(20, 20);
			printf("%s", str);
			setPos(32, 21);
			printf("%s", str2);
			setPos(25, 22);
			printf("%s", str3);
			//In the end - clear weaponary section
			drawRectangle(3, 30, 25, 45, 0x00);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
		}
		//Create weapon option
		else if (strcmp(userInput_greetings, "createwpn") == 0) {
			//Clear user input area
			drawRectangle(2, 98, 2, 23, 0x00);
			//Draw 'WEAPONS' border
			int i;
			setColor(013);
			for (i = 2; i < 50; i++) {
				setPos(i, 22);
				printf("*");
				setPos(98 - i, 22);
				printf("*");
				Sleep(50);
			}
			//print ">>ANGAR SECTION<<"
			char *angarTitle = ">>WEAPON_CREATE SECTION<<";
			for (i = 0; i < (int) strlen(angarTitle); i++) {
				setPos(i + 40, 21);
				printf("%c", angarTitle[i]);
				Sleep(rand() % 100);
			}
			//Init weapon by user - get name
			setColor(TEXTCOLOR);
			setPos(35, 10);
			printf("Enter weapon name :");
			setPos(35, 11);
			printf(">>");
			setPos(38, 11);
			char weaponName_user[WEAPON_NAME];
			gets_s(weaponName_user, WEAPON_NAME*sizeof(char));
			drawRectangle(2, 98, 2, 20, 0x00);
			//get damage
			setColor(TEXTCOLOR);
			setPos(35, 10);
			printf("Enter weapon damage :");
			setPos(35, 11);
			printf(">>");
			setPos(38, 11);
			int weaponDamage_user = 0;
			scanf_s("%d", &weaponDamage_user);
			getchar();
			drawRectangle(2, 98, 2, 20, 0x00);
			//Create new weapon:
			for (i = 0; i < WEAPONS_C; i++) {
				if (weaponsList[i].name[0] == '\0') {
					strncpy_s(weaponsList[i].name, WEAPON_NAME * sizeof(char), weaponName_user, WEAPON_NAME);
					weaponsList[i].damage = weaponDamage_user;
					break;
				}
				else {
					continue;
				}
			}
			//Clear the area! And return stuff
			drawRectangle(2, 98, 2, 22, 0x00);
			setColor(TEXTCOLOR);
			setPos(20, 20);
			printf("%s", str);
			setPos(32, 21);
			printf("%s", str2);
			setPos(25, 22);
			printf("%s", str3);
			//clear screen
			drawRectangle(3, 30, 25, 45, 0x00);
		}
		//Exit option
		else if (strcmp(userInput_greetings, "exit") == 0) {
			break;
		}
		//Delete robot option
		else if (strcmp(userInput_greetings, "deleterbt") == 0) {
			setPos(38, 12);
			printf("Which one you want to delete?");
			setPos(38, 13);
			printf("Look for the list below");
			int x_Temp = 5, y_Temp = 25;
			//Show the list of robots names
			for (i = 1; i < ROBOTS_C; i++) {
				if (robotsList[i].name[0] != '\0') {
					setPos(x_Temp, y_Temp);
					printf("%s", robotsList[i].name);
					y_Temp++;
				}
				else {
					continue;
				}
			}
			setPos(38, 14);
			printf(">>");
			setPos(41, 14);
			char deleteRbt_user[100];
			int status = 0;
			gets_s(deleteRbt_user, 100 * sizeof(char));
			for (i = 1; i < ROBOTS_C; i++) {
				if (strcmp(robotsList[i].name, deleteRbt_user) == 0) {
					deleteRobot(&robotsList[i]);
					status++;
				}
				else {
					continue;
				}
			}
			if (status == 0) {
				setPos(35, 16);
				printf("No robots with name like yours found.");
				setPos(35, 17);
				printf("Press a key to continue");
				getchar();
			}
			//Clear the area
			drawRectangle(2, 98, 2, 22, 0x00);
			//Clear weaponary info
			drawRectangle(3, 30, 25, 45, 0x00);
			//Print strings back
			setColor(TEXTCOLOR);
			setPos(20, 20);
			printf("%s", str);
			setPos(32, 21);
			printf("%s", str2);
			setPos(25, 22);
			printf("%s", str3);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
		}
		//DynMem
		else if (strcmp(userInput_greetings, "dynmem") == 0) {
			struct Weapon *myDynWeapon = (struct Weapon *)calloc(1, sizeof(struct Weapon));
			strncpy_s(myDynWeapon->name, WEAPON_NAME*sizeof(char), "OMG_WEAPON", WEAPON_NAME*sizeof(char));
			myDynWeapon->damage = 100500;
			//Clear user input area
			drawRectangle(2, 98, 2, 23, 0x00);
			//Say something			
			setPos(20, 10);
			printf("Hello ruslan anat.");
			Sleep(1000);
			setPos(20, 11);
			printf("In lab you wrote, that i must write smth with dynamic memory allocation");
			Sleep(1000);
			setPos(20, 12);
			printf("Here you go! This weapon was created by amazing malloc function:");
			Sleep(1000);
			setPos(20, 13);
			printf("%s +over%d", myDynWeapon->name, myDynWeapon->damage);
			Sleep(2000);
			setPos(20, 15);
			printf("press smth");
			getchar();
			//Clear that shit
			drawRectangle(2, 98, 2, 22, 0x00);
			//Free memory
			free(myDynWeapon);
			setColor(TEXTCOLOR);
			setPos(20, 20);
			printf("%s", str);
			setPos(32, 21);
			printf("%s", str2);
			setPos(25, 22);
			printf("%s", str3);
		}
		//Battle
		else if (strcmp(userInput_greetings, "battle") == 0) {
			//Clear user input area
			drawRectangle(2, 98, 2, 23, 0x00);
			//Draw 'battle' border
			setColor(013);
			for (i = 2; i < 50; i++) {
				setPos(i, 22);
				printf("*");
				setPos(98 - i, 22);
				printf("*");
				Sleep(50);
			}
			//print ">>BATTLE_ROBOT SECTION<<"
			char *angarTitle = ">>BATTLE_CHANGE SECTION<<";
			for (i = 0; i < (int) strlen(angarTitle); i++) {
				setPos(i + 38, 21);
				printf("%c", angarTitle[i]);
				Sleep(rand() % 100);
			}
			//indexes for robots xd
			int frstRbt_index, secRbt_index;
			//Show the list of robots names
			setColor(TEXTCOLOR);
			int x_Temp = 5, y_Temp = 25;
			for (i = 1; i < ROBOTS_C; i++) {
				if (robotsList[i].name[0] != '\0') {
					setPos(x_Temp, y_Temp);
					printf("%s", robotsList[i].name);
					y_Temp++;
				}
				else {
					continue;
				}
			}
			//Get user info about first robot
			char frstRbt[ROBOT_NAME];
			setPos(38, 12);
			printf("Enter name of the first robot : ");
			setPos(38, 13);
			printf(">>");
			//check if this stuff exists
			int status_frstRbt = 0;
			while (status_frstRbt == 0) {
				setPos(41, 13);
				gets_s(frstRbt, ROBOT_NAME*sizeof(char));
				for (i = 0; i < ROBOTS_C; i++) {
					if (strcmp(robotsList[i].name, frstRbt) == 0 && robotsList[i].name[0] != '\0') {
						status_frstRbt++;
						frstRbt_index = i;
						break;
					}
					else {
						continue;
					}
				}
				if (status_frstRbt == 0) {
					drawRectangle(40, 98, 13, 13, 0x00);
				}
			}			
			drawRectangle(2, 98, 2, 15, 0x00);
			//Get user info about second robot
			char secRbt[ROBOT_NAME];
			setPos(38, 12);
			printf("Enter name of the second robot : ");
			setPos(38, 13);
			printf(">>");
			//check if this stuff exists
			int status_secRbt = 0;
			while (status_secRbt == 0) {
				setPos(41, 13);
				gets_s(secRbt, ROBOT_NAME*sizeof(char));
				for (i = 0; i < ROBOTS_C; i++) {
					if (strcmp(robotsList[i].name, secRbt) == 0 && robotsList[i].name[0] != '\0' && robotsList[i].name != robotsList[frstRbt_index].name) {
						status_secRbt++;
						secRbt_index = i;
						break;
					}
					else {
						continue;
					}
				}
				if (status_secRbt == 0) {
					drawRectangle(40, 98, 13, 13, 0x00);
				}
			}			
			drawRectangle(2, 98, 2, 15, 0x00);
			//Clear robots list info
			drawRectangle(3, 27, 25, 45, 0x00);
			//Print who is fighting
			setPos(2, 5);
			printf("%s vs %s", robotsList[frstRbt_index].name, robotsList[secRbt_index].name);
			//Draw calculation stuff
			time_t t;
			srand((unsigned int) time(&t));
			int status = 0;
			setPos(40, 13);
			printf("Calculating");
			for (i = 0; i < 500; i++) {
				int randX = rand() % 40 + 30, randY = rand() % 6 + 5;
				setColor(TEXTCOLOR);
				setPos(randX, randY);
				printf("*");
				Sleep(rand()%20);
				status += rand() % 100;
				if (status % 10 < 5) {
					setPos(randX, randY);
					setColor(0x00);
					printf(" ");
					setColor(TEXTCOLOR);
				}
				if (status % 50 < 2) {
					setPos(52, 13);
					putchar('.');
					Sleep(50);
					setPos(54, 13);
					putchar('.');
					Sleep(50);
					setPos(56, 13);
					putchar('.');
					Sleep(50);
					//clear that dots
					drawRectangle(52, 56, 13, 13, 0x00);
				}
				//print percentage
				setPos(42, 14);
				printf("%i%%", i / 5);
			}
			//clear 'calculating' and 'percentage'
			drawRectangle(40, 55, 13, 13, 0x00);
			drawRectangle(40, 55, 14, 14, 0x00);
			//print ready and 100%
			setPos(42, 13);
			setColor(TEXTCOLOR);
			printf("Calculation ready.");
			//Calculate result!
			int result = 0; //0 - friendship, 1 - first, 2 - second
			for (i = 0; i < 10; i++) {
				robotsList[frstRbt_index].hp -= robotsList[secRbt_index].damage;
				robotsList[secRbt_index].hp -= robotsList[frstRbt_index].damage;
				if (robotsList[frstRbt_index].hp <= 0) {
					setPos(38, 15);
					printf(" '%s' robot wins!", robotsList[secRbt_index].name);
					deleteRobot(&robotsList[frstRbt_index]);
					break;
				}
				else if (robotsList[secRbt_index].hp <= 0) {
					setPos(40, 15);
					printf(" '%s' robot wins!", robotsList[frstRbt_index].name);
					deleteRobot(&robotsList[secRbt_index]);
					break;
				}
				else {
					continue;
				}
			}
			setPos(40, 16);
			printf("Press a key to continue");
			getchar();
			//clear all stuff!
			drawRectangle(2, 98, 2, 22, 0x00);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
			setPos(20, 20);
			printf("%s", str);
			setPos(32, 21);
			printf("%s", str2);
			setPos(25, 22);
			printf("%s", str3);
			setColor(TEXTCOLOR);			
		}
		else if (strcmp(userInput_greetings, "changerbt") == 0) {
			//Clear user input area
			drawRectangle(2, 98, 2, 23, 0x00);
			//Draw 'changerobot' border
			setColor(013);
			for (i = 2; i < 50; i++) {
				setPos(i, 22);
				printf("*");
				setPos(98 - i, 22);
				printf("*");
				Sleep(50);
			}
			//print ">>CHANGE_ROBOT SECTION<<"
			char *angarTitle = ">>ROBOTS_CHANGE SECTION<<";
			for (i = 0; i < (int) strlen(angarTitle); i++) {
				setPos(i + 38, 21);
				printf("%c", angarTitle[i]);
				Sleep(rand() % 100);
			}
			//Show robotsList
			int x_Temp = 5, y_Temp = 25;
			//Show the list of robots names
			setColor(TEXTCOLOR);
			for (i = 1; i < ROBOTS_C; i++) {
				if (robotsList[i].name[0] != '\0') {
					setPos(x_Temp, y_Temp);
					printf("%s", robotsList[i].name);
					y_Temp++;
				}
				else {
					continue;
				}
			}
			//get user choose - what robot does he want to change
			setColor(TEXTCOLOR);
			setPos(35, 10);
			printf("What robot do you want to change?");
			setPos(35, 11);
			printf(">>");
			setPos(37, 11);
			char robotName_ChangeRobot[ROBOT_NAME];
			gets_s(robotName_ChangeRobot, ROBOT_NAME*sizeof(char));
			int status = 0;
			for (i = 0; i < ROBOTS_C; i++) {
				if (strcmp(robotsList[i].name, robotName_ChangeRobot) == 0) {
					status++; //DON`T USE STATUS VAR ANYMORE
					//Clear area for work
					drawRectangle(2, 98, 2, 20, 0x00);
					//get user choose - what field does he want to change
					setColor(TEXTCOLOR);
					setPos(35, 9);
					printf("Changing robot %s", robotsList[i].name);
					setPos(35, 10);
					printf("What do you want to change?");
					setPos(25, 11);
					printf("Name/strength/agility/intelligence/damage/weapon\n");
					setPos(38, 12);
					printf(">>");
					setPos(41, 12);
					char userChoice_ChangeRobot[USER_INPUT];
					gets_s(userChoice_ChangeRobot, USER_INPUT*sizeof(char));
					int counter;//DON`T USER COUNTER AFTER THIS
					//Tolower items in userChoice
					for (counter = 0; counter < USER_INPUT; counter++) {
						userChoice_ChangeRobot[counter] = tolower(userChoice_ChangeRobot[counter]);
					}
					//Do something depenging on the userChoice_ChangeRobot
					if (strcmp(userChoice_ChangeRobot, "name") == 0) {
						char newName_RobotChange[ROBOT_NAME];
						setPos(35, 13);
						printf("Enter the new name : ");
						gets_s(newName_RobotChange, ROBOT_NAME*sizeof(char));
						strncpy(robotsList[i].name, newName_RobotChange, ROBOT_NAME*sizeof(char));
					}
					else if (strcmp(userChoice_ChangeRobot, "strength") == 0) {
						int newStrength = 0;
						setPos(35, 13);
						printf("Enter new strength: ");
						scanf_s("%d", &newStrength);
						robotsList[i].strength = newStrength;
					}
					else if (strcmp(userChoice_ChangeRobot, "agility") == 0) {
						int newAgility = 0;
						setPos(35, 13);
						printf("Enter new agility: ");
						scanf_s("%d", &newAgility);
						robotsList[i].agility = newAgility;
					}
					else if (strcmp(userChoice_ChangeRobot, "intelligence") == 0) {
						int newIntell = 0;
						setPos(35, 13);
						printf("Enter new intelligence: ");
						scanf_s("%d", &newIntell);
						robotsList[i].intelligence = newIntell;
					}
					else if (strcmp(userChoice_ChangeRobot, "damage") == 0) {
						int newDamage = 0;
						setPos(35, 13);
						printf("Enter new damage: ");
						scanf_s("%d", &newDamage);
						robotsList[i].damage = newDamage;
					}
					else if (strcmp(userChoice_ChangeRobot, "weapon") == 0) {
						char newWeapon[WEAPON_NAME];
						setPos(15, 13);
						printf("What kind of weapon do you want to choose?");
						//print weaponary
						showWeaponaryMenu(70, 25, weaponsList);
						//get type of weapon
						setPos(15, 14);
						printf("Your choose: ");
						gets_s(newWeapon, WEAPON_NAME*sizeof(char));
						int status2 = 0, counter2;
						for (counter2 = 0; counter2 < WEAPONS_C; counter2++) {
							if (strcmp(weaponsList[counter2].name, newWeapon) == 0) {
								robotsList[i].robotWeapon = weaponsList[counter2];
								robotsList[i].damage += weaponsList[counter2].damage;
								status2++;
							}
							else {
								continue;
							}
						}
						//check if the weapon exists
						if (status2 == 0) {
							setPos(37, 15);
							printf("No weapon like found");
							setPos(37, 16);
							printf("Press a key to continue");
							getchar();
						}
					}
					//Incorrect input
					else {
						setPos(37, 15);
						printf("You put not correct operation");
						setPos(37, 16);
						printf("Press a key to continue");
						getchar();
					}
					//In the end - get out of the for loop!
					break;
				}
				else {
					continue;
				}
			}
			if (status == 0) {
				setPos(37, 15);
				printf("No robot like %s", robotName_ChangeRobot);
				setPos(37, 16);
				printf("Press a key to continue");
				getchar();
			}
			//Clear the area
			drawRectangle(2, 98, 2, 22, 0x00);
			//Clear weaponary&help info
			drawRectangle(3, 27, 25, 45, 0x00);
			drawRectangle(68, 98, 24, 45, 0x00);
			//Chtobi bilo xd
			setColor(TEXTCOLOR);
			setPos(20, 20);
			printf("%s", str);
			setPos(32, 21);
			printf("%s", str2);
			setPos(25, 22);
			printf("%s", str3);
			setColor(TEXTCOLOR);
		}
		//Incorrect input
		else {
			setPos(27, 13);
			setColor(TEXTCOLOR);
			printf("Incorrect input! Press a key and try again");
			getchar();
		}
		//Clear user input
		drawRectangle(41, 98, 10, 10, 0x00);
		drawRectangle(5, 95, 11, 14, 0x00);
	}
	
	//Clear input stuff
	drawRectangle(5, 95, 3, 24, 0x00);
	//Middle robot tells ending
	char *str4 = "Thank you traveler! Come back soon.";
	robotTalks(str4, strlen(str4), xStart_robotGreetings, yStart_robotGreetings, xStart_robotGreetings - (strlen(str4) / 2), yStart_robotGreetings - 10);
	setPos(99, 49);
	Sleep(4000);
	//Save the result.
	writeWpnLst(weaponsList);
	writeRbtLst(robotsList);
}
