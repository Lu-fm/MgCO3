#ifndef FILE_H_
#define FILE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"genlib.h"
#include"my_strtok.h"

#define N 3   			//The amount of the figure
#define L 3   			//The amount of the column
#define MAXLINE 1024  	//The string length we read each row.

/*
--------------------------
*CONFERM, DEATH, RECOVERED
*expends to the orders of the figure
--------------------------
*/
#define CONFIRM 0
#define DEATH 1
#define RECOVERED 2

/*
--------------------------------------
*PRO_STA means "Province/State" column
*COU_RIG means "Country/Rigion" column
*UPDATA_TIME means "Last Updata" column
They expend to their order.
---------------------------------------
*/
#define PRO_STA 0
#define COU_RIG 1
#define UPDATE_TIME 2

/*
------------------------------------
*UPDATE and DELETE represent their state
------------------------------------
*/
#define UPDATE 0
#define DELETE_P 1

char *figure[N];
char buffer[1024];

/*
----------------------------------
*Data is a struct to store the data read
*from the file.
----------------------------------
*/
typedef struct Data
{
	char column[L][100];
	int  figure[N];
	double fraction[N];
	struct Data *next;
} Data;

/*
----------------------------------
*This is a struct for returning the
*head node of the data we read and
*the number of lines and the max figure.
-------------------------------------
*/
typedef struct Combine
{
	int max[N];
	int line;
	Data *head;
	Data *dp[3];
	char date[100];
}Combine;

/*
*Function: ReadData
*Usage: Data *ptr = ReadData(filename)
*Return type: Data
* -----------------------------
* This function reads data from a file and then retuen
*the head of the linklist.
*/
Combine *ReadData(char *filename);

/*
*Function: EditData
*Usage: EditData(date, choice);
*Return type: void
*----------------------------------------------
*It can both update a record and delete a
*record, and it differs by inputing different choice
*if the choice is UPDATE, and it is in updating state,
*when it is DELETE, it will be in deleting state.
*"date" value is the date of file you want.
*/


/*
*Function: MaxAndFrac
*Usage: MaxAndFrac(Combine *List);
*Return type: void
--------------------------------------
*This function is used to find the max
*value in each figure column and the fraction 
*of each figure.
*/
void MaxAndFrac(Combine *List);

/*
*Function: EditData
*Usage: EditData*=(date, choice, target)
---------------------------------------
*This function is used to edit data, to delete
*(choice == 1), or tp update(choice == 0). 
*/
void EditData(char *date, int choice, Data*target);

/*
*Function: AddData
*Usage: AddData(date, target);
---------------------------
*Add a record including several 
*data into a target file.
*/
void AddData(char *date, Data *target);
/*
*Function: UpdateData
*Usage: UpdateData(date, target)
*-------------------------------
Updata a single record with several 
*data information.
*/
void UpdateData(char *date, Data *target);
/*
Function: DeleteData
*Usage: DeleteData(date, target)
*-------------------------------
Delete a single record with several 
*data information.
*/
void DeleteData(char *date, Data *target);

/*
*Function: Search()
*Usage: ptr = Search(name, head, col);
*-----------------------------------
*This Function is to find a record matching
*the name of the column
*/
Data *Search(char *name, Data *head, int col);
/*
*Function: ReadSeries
*Usage: ptr = ReadSeries(start, end);
*-----------------------------------
*This function can return a  ptr(type Combine*)
*with the range of date is from start to end
*/
Combine *ReadSeries(char *start, char *end);
/*
*Function: DateRange
*Usage: ptr = DateRange(start, end, dur)
*If you want to return a string array with 
*the date is from start to end, the dur should 
*be 0. But if you want to give a satrt date and 
*a duration, you can input your duration, and the 
*end date at this time is useless.
*/
char **DateRange(char *start, char *end, int dur);
/*
*Function: Forecast
*Usage: Forecast(start, end, day)
*-----------------------------------
*This function is to forecast several 
*days' data based on the data from start
*to end.
*/
void Forecast(char *start, char *end, char *day);
#endif
