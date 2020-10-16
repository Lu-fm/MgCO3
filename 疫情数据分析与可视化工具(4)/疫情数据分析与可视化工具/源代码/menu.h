#ifndef MENU_H_
#define MENU_H_

//#include "file.h"
#include "imgui.h"
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <time.h>

#define REFRESH_WINDOW 1
#define buttonwidth 0.5
#define buttonheight 0.2
#define boxwidth 2
#define boxheight 2.8

extern showHelp;
extern showAbout;
extern isNew;
extern showButton;
extern isHistogram;
extern isPieChart;
extern isLineChart;
extern bool isBranch;
extern bool isQuest_1;
extern bool isQuest_2;
extern bool showButton_1;
extern bool showButton_2;
extern bool isConfirm;
extern bool isDeath;
extern bool isRecovered;
extern bool isHubei;
extern bool isOutsideHubei;
extern bool isStateButton;
extern bool isEdit;
extern bool isUpdate;
extern bool isDelete;
extern bool isSuccess;
extern bool isWarning;
extern bool isAdd;
extern bool isForecast;

/*
*Function:DrawMenu
*Usage: DrawMenu()
*---------------------
*This function draws the main menu;
*/
void DrawMenu();
/*
*Function: DrawAbout
*Usage: DrawAbout();
*-----------------
*This function draws about window;
*/
void DrawAbout();
/*
*Function: DrawHelp
*Usage: Drawhelp();
*-----------------
*This function draws help window;
*/
void DrawHelp();

/*
*Function: Display
*Usage: Display();
*-----------------
*This function generates all drawing
*functions, can be used to refresh.
*/

void Display();
/*
*Function: DrawBranch
*Usage: DrawBranch()
*-----------------
*This function draws a branch window, 
*to choose piechart or linechart & histogram.
*/
void DrawBranch();
/*
*Function: DrawQuest_1
*Usage: DrawQuest_1();
*-----------------
*This function draws a window
*to get information of forecast 
*and linechart & histogram
*/
void DrawQuest_1();
/*
*Function: DrawQuest_2
*Usage: DrawQuest_2();
*-----------------
*This function draws a window
*to get information of piechart
*/
void DrawQuest_2();
/*
*Function: DrawButton_1
*Usage: DrawButton_1();
*-----------------
*This function draws the "histogram" and "linechart"
*button
*/
void DrawButton_1();
/*
*Function: DrawButton_2
*Usage: DrawButton_2();
*-----------------
*This function draws the "Hubei vs OutsideHubei" and 
*"OutsideHubei" button.
*/
void DrawButton_2();
/*
*Function: DrawStateButton
*Usage: DrawStateButton();
*-----------------
*This function draws a window
*to show the "histogram" and "linechart"
*button
*/
void DrawStateButton();
/*
Function:FreeHead
*Usage: FreeHead()
*This function is uesd to free
*all of the nodes.
*/
void FreeHead();
/*
Function: RefreshAll
*Usage: RefreshAll();
*initialize all the bool variable.
*to refresh window
*/
void RefreshAll();
/*
*Function: DrawEdit
*Usage: DarwEdit()
*This function draws the edit window
*for updating, adding or deleting data.
*/
void DrawEdit();
/*
*Function: DrawSuccess
*Usage: DrawSuccess()
*This function draws a window
*to mark your success in editing 
*the data.
*/
void DrawSuccess();
/*
*Function:DrawForecast
*Usage: DrawForecast()
*This function draws the forecast
*window to get the start date , end date
* and duration with calling DrawQuest_1().
*/
void DrawForecast();
#endif