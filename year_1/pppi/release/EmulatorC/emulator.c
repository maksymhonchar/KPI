#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "emulator.h"

//Set cursor position on (x,y) coordinate.
void setCoord(int x, int y)
{
    COORD myCoord = { x, y };
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, myCoord);
}

//Set the color for printing out data.
void setColor(int color)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}

//Print the borders with the certain color.
void drawBorders(int xStart, int yStart, int xEnd, int yEnd)
{
    int i;
    for (i = xStart; i < xEnd; i++)
        prStr_CrdClr(i, yStart, BORDER_COLOR, " ");
    for(i = xStart; i < xEnd; i++)
        prStr_CrdClr(i, yEnd - 1, BORDER_COLOR, " ");
    for (i = yStart; i < yEnd; i++)
        prStr_CrdClr(xStart, i, BORDER_COLOR, " ");
    for(i = yStart; i < yEnd; i++)
        prStr_CrdClr(xEnd - 1, i, BORDER_COLOR, " ");
}

//Draw all borders on the console
void drawAllBorders()
{
    //Print DUSO
    prStr_CrdClr(CONSOLE_WIDTH / 2 - 2, CONSOLE_HEIGHT -1, STANDART_COLOR, "DUSO");
    //Print all borders
    drawBorders(0,0,CONSOLE_WIDTH, CONSOLE_HEIGHT - 1);
    drawBorders(COMMAND_WINDOW_X_END, 0, COMMAND_WINDOW_X_END, CONSOLE_HEIGHT - 1);
    drawBorders(0, COMMAND_WINDOW_Y_END, COMMAND_WINDOW_X_END, COMMAND_WINDOW_Y_END + 1);
    setCoord(USER_INPUT_X, USER_INPUT_Y);
}

//Print the string on the certain position (x,y) with the certain color.
void prStr_CrdClr(int x, int y, int color, char * line)
{
    setCoord(x,y);
    setColor(color);
    printf("%s", line);
    setColor(STANDART_COLOR);
}

//Print the integer on the certain position (x,y) with the certain color.
void prInt_CrdClr(int x, int y, int color, int number)
{
    setCoord(x,y);
    setColor(color);
    printf("%d", number);
    setColor(STANDART_COLOR);
}

//Clear a workspace from (x1,y1) to (x2, y2)
void clearWorkspace(int x1, int y1, int x2, int y2)
{
    int i, j;
    for(i = x1; i<x2; i++)
    {
        for(j = y1; j< y2; j++)
        {
            prStr_CrdClr(i,j, STANDART_COLOR, " ");
        }
    }
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw a 5x5 lamp on the (x,y) position.
void drawLamp(int x, int y, Lamp_T self)
{
    int i,j;
    if(self.state == OFF)
    {
        for (i = y; i < y+3; i++)
        {
            for (j = x; j < x+3; j++)
            {
                prStr_CrdClr(j, i, NOCOLOR, " ");
            }
        }
        prStr_CrdClr(x-1, y+1, NOCOLOR, " ");
        prStr_CrdClr(x+1, y-1, NOCOLOR, " ");
        prStr_CrdClr(x+1, y+3, NOCOLOR, " ");
        prStr_CrdClr(x+3, y+1, NOCOLOR, " ");
    }
    else if(self.state == ON)
    {
        for (i = y; i < y+3; i++)
        {
            for (j = x; j < x+3; j++)
            {
                prStr_CrdClr(j, i, self.color - DARK * (1 - self.brght), " ");
            }
        }
        prStr_CrdClr(x-1, y+1, self.color - DARK * (1 - self.brght), " ");
        prStr_CrdClr(x+1, y-1, self.color - DARK * (1 - self.brght), " ");
        prStr_CrdClr(x+1, y+3, self.color - DARK * (1 - self.brght), " ");
        prStr_CrdClr(x+3, y+1, self.color - DARK * (1 - self.brght), " ");
    }
    else
    {
        printf("FATAL ERROR");
        exit(1);
    }
}

//Draw all lamps + their id`s
void drawLampList(LampList_T * lamp_list)
{
    int x = DRAW_ALL_LAMPS_START_POS_X, y = DRAW_ALL_LAMPS_START_POS_Y;
    int i;
    //Draw 1-4 lamps
    for(i = 0; i < LAMPS_MAX_COUNT / 2; i++)
    {
        drawLamp(x, y, lamp_list->list[i]);
        x += 7;
    }
    //Draw 5-8 lamps
    x = DRAW_ALL_LAMPS_START_POS_X, y = DRAW_ALL_LAMPS_START_POS_Y;
    y += 8;
    for(i = 0; i < LAMPS_MAX_COUNT / 2; i++)
    {
        drawLamp(x, y, lamp_list->list[i + 4]);
        x += 7;
    }
    //Draw 1-4 id`s
    x = DRAW_ALL_LAMPS_START_POS_X + 1, y = DRAW_ALL_LAMPS_START_POS_Y + 4;
    for(i = 0; i<LAMPS_MAX_COUNT / 2; i++)
    {
        prInt_CrdClr(x, y, ID_COLOR, lamp_list->list[i].id);
        x+= 7;
    }
    //Draw 5-8 id`s
    x = DRAW_ALL_LAMPS_START_POS_X + 1, y = DRAW_ALL_LAMPS_START_POS_Y + 4;
    y += 8;
    for(i = 0; i<LAMPS_MAX_COUNT / 2; i++)
    {
        prInt_CrdClr(x, y, ID_COLOR, lamp_list->list[i+4].id);
        x+= 7;
    }
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw 'About' menu with help for user.
void drawAboutMenu()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("\"1\"-switch all lamps on/off.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("\"2\"-switch one lamp on/off.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("\"3\"-switch brightness for all lamps");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("\"4\"-switch brightness for one lamp.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 6);
    printf("\"5\"-switch color for all lamps.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 7);
    printf("\"6\"-Start Mode.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

//Draw 'About' menu for on-off function
void drawAboutMenu_TurnOnOffOne()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("\"n\"- to switch on/off n-th lamp.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("n here is the lamp id.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("Example: | >4 [enter] |");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

void drawAboutMenu_ChangeBrght()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("0 for dark color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("1 for bright color.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

void drawAboutMenu_ChangeBrghtOne()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("First number - id (from 1 to 8).");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("Second number:");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("0 - dark color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("1 - bright color.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

void drawAboutMenu_ChangeColorAll()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("0 - default white color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("1 -  red color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("2 - green color.");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 5);
    printf("3 - blue color.");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}

void drawAboutMenu_Modes()
{
    clearWorkspace(USER_INPUT_X, COMMAND_WINDOW_Y_END + 1, COMMAND_WINDOW_X_END - 1, CONSOLE_HEIGHT - 2);
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 2);
    setColor(STANDART_COLOR);
    printf("Which mode do u like to turn on?:");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 3);
    printf("1 - NEW YEAR mode\n");
    setCoord(USER_INPUT_X, COMMAND_WINDOW_Y_END + 4);
    printf("2 - PARTY mode");
    setCoord(USER_INPUT_X,USER_INPUT_Y);
}
//Initialize the lamp list with default numbers.
void lampList_constructor(LampList_T * lamp_list)
{
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lamp_list->list[i].id = i + 1;
        lamp_list->list[i].brght = HIGH;
        lamp_list->list[i].color = WHITE;
        lamp_list->list[i].state = OFF;
    }
}

//Turn on all the lamps.
void lampList_turnOnAll(LampList_T * lamp_list)
{
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lamp_list->list[i].state = ON;
    }
}

//Turn off all the lamps.
void lampList_turnOffAll(LampList_T * lamp_list)
{
    int i;
    for(i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lamp_list->list[i].state = OFF;
    }
}

//Turn on/off only the one lamp.
void lampList_turnOnOffOne(LampList_T * lamp_list, int id)
{
    if(id < 1 || id > LAMPS_MAX_COUNT)
        return;
    if(lamp_list->list[id - 1].state == OFF)
    {
        lamp_list->list[id - 1].state = ON;
    }
    else
    {
        lamp_list->list[id - 1].state = OFF;
    }
}

//Change brightness for all lamps at one time.
void lampList_changeBrightnessAll(LampList_T * lamp_list, int id_brightness)
{
    for (int i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lampList_changeBrightnessOne(lamp_list, id_brightness, i);
    }
}

//Change brightness for a single lamp.
void lampList_changeBrightnessOne(LampList_T * lamp_list, int id_brightness, int id)
{
    lamp_list->list[id].brght=id_brightness;
}


void lampList_changeColorOne(LampList_T * lamp_list, int id, int self_color)
{
    if(id < 0 || id > LAMPS_MAX_COUNT)
        return;
    switch(self_color)
    {
    case 0:
        lamp_list->list[id].color = WHITE;
        break;

    case 1:
        lamp_list->list[id].color = RED;
        break;

    case 2:
        lamp_list->list[id].color = GREEN;
        break;

    case 3:
        lamp_list->list[id].color = BLUE;
        break;

    default:
        break;
    }
}

void lampList_changeColorAll(LampList_T * lamp_list, int self_color)
{
    for(int i = 0; i < LAMPS_MAX_COUNT; i++)
    {
        lampList_changeColorOne(lamp_list, i, self_color);
    }
}

void  ModeStep1(LampList_T * lamp_list)
{
    lamp_list->list[0].color = BLUE;
    lamp_list->list[1].color = RED;
    lamp_list->list[2].color = GREEN;
    lamp_list->list[3].color = RED;
    lamp_list->list[4].color = GREEN;
    lamp_list->list[5].color = BLUE;
    lamp_list->list[6].color = RED;
    lamp_list->list[7].color = GREEN;

}
void ModeStep2(LampList_T * lamp_list)
{
    lamp_list->list[0].color = GREEN;
    lamp_list->list[1].color = BLUE;
    lamp_list->list[2].color = RED;
    lamp_list->list[3].color = GREEN;
    lamp_list->list[4].color = RED;
    lamp_list->list[5].color = GREEN;
    lamp_list->list[6].color = BLUE;
    lamp_list->list[7].color = RED;
}

void ModeStep3(LampList_T * lamp_list)
{
    lamp_list->list[0].color = RED;
    lamp_list->list[1].color = GREEN;
    lamp_list->list[2].color = BLUE;
    lamp_list->list[3].color = RED;
    lamp_list->list[4].color = GREEN;
    lamp_list->list[5].color = RED;
    lamp_list->list[6].color = GREEN;
    lamp_list->list[7].color = BLUE;
}
void ModeStep4(LampList_T * lamp_list)
{
    lamp_list->list[0].color = BLUE;
    lamp_list->list[1].color = RED;
    lamp_list->list[2].color = GREEN;
    lamp_list->list[3].color = BLUE;
    lamp_list->list[4].color = RED;
    lamp_list->list[5].color = GREEN;
    lamp_list->list[6].color = RED;
    lamp_list->list[7].color = GREEN;
}
