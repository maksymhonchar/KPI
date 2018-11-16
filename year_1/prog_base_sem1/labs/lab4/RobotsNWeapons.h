#ifndef __ROBOTS
#define __ROBOTS

#define WEAPONS_C 20
#define ROBOTS_C 20
#define WEAPON_NAME 20
#define ROBOT_NAME 50
#define USER_INPUT 50
#define CONSOLESIZE "MODE CON: COLS=100 LINES=50"

#define BORDERCOLOR 071
#define TEXTCOLOR 007
#define ROBOTCOLOR 120
#define HELPCOLOR 014

struct Weapon {
	char name[WEAPON_NAME];
	int damage;
};

struct Robot {
	char name[ROBOT_NAME];
	int strength;
	int agility;
	int intelligence;
	int damage;
	int hp;
	struct Weapon robotWeapon;
};

void setPos(int, int);
void setColor(int);
void drawRectangle(int, int, int, int, int);
void drawCoolBorders(int, int, int, int, int);

void displayRobotInfo(struct Robot *, int, int);
void displayWeaponInfo(struct Weapon, int, int);
void initRobotsListDefault(struct Robot [], struct Weapon []);
void initWeaponsDefault(struct Weapon []);
void initRobotDefault(struct Robot *, struct Weapon []);
void createRobotByParameters(struct Robot *, char *, int, int, int, struct Weapon);
void createWeapon(struct Weapon []);
void createRobotByUser(struct Robot *, struct Weapon []);
void changeRobot(struct Robot *, struct Weapon []);
void deleteRobot(struct Robot *);

void readWpnLst(struct Weapon []);
void readRbtLst(struct Robot [], struct Weapon []);
void writeWpnLst(struct Weapon []);
void writeRbtLst(struct Robot []);

void drawRobot(int, int, char);
void robotHalfTurnLeft(int, int);
void robotHalfTurnRight(int, int);
void robotTurnLeftStep1(int, int);
void robotTurnLeftStep2(int, int);
void robotTurnRightStep1(int, int);
void robotTurnRightStep2(int, int);

void robotGoNalevo(int, int, int, int *, int *);
void robotGoNapravo(int, int, int, int *, int *);
void robotTalks(char *, size_t, int, int, int, int);

void showHelpMenu(int, int);
void showWeaponaryMenu(int, int, struct Weapon []);
void showAngarMenu(int, int, struct Robot []);

void behavior();

#endif