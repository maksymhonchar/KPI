#pragma once

#define CONSOLE_SIZE "MODE CON: COLS=75 LINES=25"

#define STANDART_COLOR 007
#define ID_COLOR 260
#define HELP_COLOR 014
#define CONSOLE_WIDTH 75
#define CONSOLE_HEIGHT 25
#define COMMAND_WINDOW_X_END 43
#define COMMAND_WINDOW_Y_END 15
#define BORDER_COLOR 66
#define LAMPS_MAX_COUNT 8
#define DRAW_ALL_LAMPS_START_POS_X 47
#define DRAW_ALL_LAMPS_START_POS_Y 5
#define USER_INPUT_X 2
#define USER_INPUT_Y 3
#define DARK 128

typedef enum LAMP_BRGHT_E{
    LOW = 0,
    HIGH = 1
} LAMP_BRGHT_ET;

typedef enum LAMP_COLOR_E{
    NOCOLOR = 256,
    WHITE = 240,
    RED = 192,
    GREEN = 160,
    BLUE = 144
} LAMP_COLOR_ET;

typedef enum LAMP_STATE_E{
    OFF = 0,
    ON = 1
}LAMP_STATE_ET;

typedef struct Lamp_S {
    int id;
    LAMP_COLOR_ET color;
    LAMP_BRGHT_ET brght;
    LAMP_STATE_ET state;

} Lamp_T;

typedef struct LampList_S {
    Lamp_T list[LAMPS_MAX_COUNT];
} LampList_T;

//Console drawing functions
void setCoord(int x, int y);
void setColor(int color);
void drawBorders(int xStart, int yStart, int xEnd, int yEnd);
void drawAllBorders();
void prStr_CrdClr(int x, int y, int color, char * line);
void prInt_CrdClr(int x, int y, int color, int number);
void clearWorkspace(int x1, int y1, int x2, int y2);

//Lamp drawing functions
void drawLamp(int x, int y, Lamp_T self);
void drawLampList(LampList_T * lamp_list);

//About functions
void drawAboutMenu();
void drawAboutMenu_TurnOnOffOne();
void drawAboutMenu_ChangeBrght();
void drawAboutMenu_ChangeBrghtOne();
void drawAboutMenu_ChangeColorAll();

//Lamp logic functions
void lampList_constructor(LampList_T * lamp_list);

void lampList_turnOnAll(LampList_T * lamp_list);
void lampList_turnOffAll(LampList_T * lamp_list);
void lampList_turnOnOffOne(LampList_T * lamp_list, int id);
void lampList_changeBrightnessAll(LampList_T * lamp_list, int id_brightness);
void lampList_changeBrightnessOne(LampList_T * lamp_list, int id_brightness, int id);
void lampList_changeColorAll(LampList_T * lamp_list, int self_color);
void lampList_changeColorOne(LampList_T * lamp_list, int id, int self_color);

//Some cool stuff here!
void drawAboutMenu_Modes();
void ModeStep1(LampList_T * lamp_list);
void ModeStep2(LampList_T * lamp_list);
void ModeStep3(LampList_T * lamp_list);
