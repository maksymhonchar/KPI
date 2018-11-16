#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#include "emulator.h"

int main()
{
    LampList_T lampList;
    char userInput_function;
    int userInput_curX, userInput_curY;
    //if 0 - turn the lights off. if 1 - turn the lights on.
    int switchAll_ON_OFF = 1;
    //Initialize the main set of lamps.
    lampList_constructor(&lampList);
    //Initialize the default console size.
    system(CONSOLE_SIZE);
    //Draw the console
    drawAboutMenu();
    drawAllBorders();
    drawLampList(&lampList);
    //Get the user input and do the main algorithm
    prStr_CrdClr(2,2, STANDART_COLOR, "DUSO - ThreeAxesGang");
    userInput_curX = 4;
    userInput_curY = 3;
    prStr_CrdClr(2,3, STANDART_COLOR, ">>");
    setCoord(userInput_curX, userInput_curY);
    while(tolower((userInput_function = getchar())) != 'x')
    {
        userInput_curY++;
        //Take only the first character.
        while(getchar() != '\n') continue;
        //Turn all lamps on/off
        if(tolower(userInput_function) == '1')
        {
            if(switchAll_ON_OFF == 1)
            {
                prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching on all lamps...");
                userInput_curY++;
                lampList_turnOnAll(&lampList);
                switchAll_ON_OFF = 0;
            }
            else if (switchAll_ON_OFF == 0)
            {
                prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching off all lamps...");
                userInput_curY++;
                lampList_turnOffAll(&lampList);
                switchAll_ON_OFF = 1;
            }
            else
            {
                system("cls");
                prStr_CrdClr(0,0,STANDART_COLOR, "Fatal error in the \"userInput_function == '1'\" function");
                userInput_curX = 0;
                userInput_curY = 1;
            }
        }
        //turn one lamp on/off
        else if (tolower(userInput_function) == '2')
        {
            int userInput_lampID;
            drawAboutMenu_TurnOnOffOne();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching on/off n-th lamp");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "What lamp to switch:");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, ">>");
            userInput_curX+=2;
            //get the user input
            setCoord(userInput_curX, userInput_curY);
            userInput_curX-=2;
            char ch;
            while(scanf("%d", &userInput_lampID) != 1 || userInput_lampID < 1 || userInput_lampID > 8)
            {
                while((ch = getchar()) != '\n') continue; //read only the first symbol.
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_turnOnOffOne(&lampList, userInput_lampID);
            //In the end - redraw 'about' menu.
            drawAboutMenu();
        }
        //change brightness for all lamps
        else if (tolower(userInput_function) == '3')
        {
            int userInput_brght;
            drawAboutMenu_ChangeBrght();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching brightness - all lamps");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "What brightness:");
            userInput_curY++;
            //get the user input - id
            setCoord(userInput_curX, userInput_curY);
            char ch;
            while(scanf("%d", &userInput_brght) != 1 || userInput_brght > 1 || userInput_brght < 0)
            {
                while((ch = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_changeBrightnessAll(&lampList, userInput_brght);
            drawAboutMenu();
        }
        //change brightness for one lamp
        else if (tolower(userInput_function) == '4')
        {
            int userInput_brght;
            int userInput_id;
            drawAboutMenu_ChangeBrghtOne();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching brightness - one lamps");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Lamp id:");
            userInput_curY++;
            //get the user input - lamp id
            setCoord(userInput_curX, userInput_curY);
            char ch;
            while(scanf("%d", &userInput_id) != 1 || userInput_id > 8 || userInput_id < 1)
            {
                while((ch = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Lamp brightness:");
            userInput_curY++;
            //get the user input - brightness
            setCoord(userInput_curX, userInput_curY);
            char ch2;
            while(scanf("%d", &userInput_brght) != 1 || userInput_brght > 1 || userInput_brght < 0)
            {
                while((ch2 = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_changeBrightnessOne(&lampList, userInput_brght, userInput_id - 1);
            drawAboutMenu();
        }
        //change color for one lamp
        else if (tolower(userInput_function) == '5')
        {
            int userInput_color;
            drawAboutMenu_ChangeColorAll();
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Switching color - one lamp");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Lamp color:");
            userInput_curY++;
            //get the user input - brightness
            setCoord(userInput_curX, userInput_curY);
            char ch;
            while(scanf("%d", &userInput_color) != 1 || userInput_color > 4 || userInput_color < 0)
            {
                while((ch = getchar()) != '\n') continue; //read only first symbol
                clearWorkspace(userInput_curX, userInput_curY, COMMAND_WINDOW_X_END - 1, userInput_curY + 3);
                setCoord(userInput_curX, userInput_curY);
            }
            userInput_curY++;
            lampList_changeColorAll(&lampList, userInput_color);
            drawAboutMenu();
        }
        //New year mode :3
        else if (tolower(userInput_function) == '6')
        {
            int SleepTime = 0;
            drawAboutMenu_Modes();
            setCoord(userInput_curX, userInput_curY);
            scanf("%i", &SleepTime);
            if(SleepTime == 1)
            {
                while(1)
                {
                    if(kbhit())
                    {
                        if(getch() == 27)
                        {
                            break;
                        }
                    }
                    ModeStep1(&lampList);
                    drawLampList(&lampList);
                    Sleep(100);
                    ModeStep2(&lampList);
                    drawLampList(&lampList);
                    Sleep(100);
                    ModeStep3(&lampList);
                    drawLampList(&lampList);
                    Sleep(100);
                    ModeStep4(&lampList);
                    drawLampList(&lampList);
                    Sleep(100);
                    prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR,"Press ESC to stop this stuff");
                }
            }
            else if(SleepTime == 2){
                while(1)
                {
                    if(kbhit())
                    {
                        if(getch() == 27)
                        {
                            break;
                        }
                    }
                    ModeStep1(&lampList);
                    drawLampList(&lampList);
                    Sleep(10);
                    ModeStep2(&lampList);
                    drawLampList(&lampList);
                    Sleep(10);
                    ModeStep3(&lampList);
                    drawLampList(&lampList);
                    Sleep(10);
                    ModeStep4(&lampList);
                    drawLampList(&lampList);
                    Sleep(10);
                    prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR,"Press ESC to stop this stuff");
                }
            }
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Enabling New Year mode...");
            userInput_curY++;
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Done by BorzychV & LemeshkoB");
            userInput_curY++;
        }
        //wrong input
        else
        {
            prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Wrong input. Look at the list below.");
            userInput_curY++;
        }
        //End of the user Input.
        prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, "Press [enter] to continue...");
        while(getchar() != '\n') continue;
        //Clear the workspace. Redraw lampList.
        clearWorkspace(USER_INPUT_X, USER_INPUT_Y, COMMAND_WINDOW_X_END - 1, COMMAND_WINDOW_Y_END - 1);
        drawAboutMenu();
        drawAllBorders();
        drawLampList(&lampList);
        //Set userInput (x,y) by default. Print '>' again.
        userInput_curX = 4;
        userInput_curY = 3;
        prStr_CrdClr(userInput_curX, userInput_curY, STANDART_COLOR, ">>");
    }
    //Clear the screen, when user wants to exit the program.
    system("cls");
    return (0);
}
