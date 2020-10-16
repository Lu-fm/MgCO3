/*------------------------------------------------
This file is mainly used to deal with the .csv file
*----------------------------------------------------
*/ 

#include "file.h"
//#include "menu.h" //include了它就报错
static int sum_1;
bool isUsed;
extern bool isWarning;
extern bool isSuccess;
extern bool isForecast;
extern Combine* cop;
extern double basic(char *start, char *end, int district);
extern double E(int t, double R0, int district);
extern double I(int t, double R0, int district);
extern double R(int t, double R0, int district);

/*
*Function: ReadData
*Usage: ReadData(char *filename)
*Return type: Data
* ---------------------
* This function reads data from a file.
*/
Combine *ReadData(char *date)
{
    FILE *ptr;
    Data *p, *head, *tail;
	Combine *List;
    bool flag = FALSE;
    bool firstline = TRUE;
  	int i, index, line; 
	char *column = NULL;
    char delimit[] = ",", filename[100] = "";
	i = index = line = 0;
	List = (Combine*)malloc(sizeof(Combine));
    head = tail = NULL;
	if(isForecast && isUsed)
		sprintf(filename, "%s-2020y.csv", date);
	else
		sprintf(filename, "%s-2020.csv", date);
    if ((ptr = fopen(filename, "r")) == NULL)
    {
		isWarning = TRUE;
		return NULL;
//		exit(0);
    }
    fseek(ptr, 0L, SEEK_SET);
    while (fgets(buffer, MAXLINE, ptr))
    {
        if (firstline == TRUE) //跳过第一行
        {
            firstline = FALSE;
            continue;
        }
        p = (Data *)malloc(sizeof(Data));
        index = i = 0;
        flag = FALSE;
        while (buffer[index] == ',') //去除开头的空单元格
        {
            column = "/";
            strcpy(p->column[i++], column);
            index++;
        }
        for (; i < L; i++) //读前几列的地名(包括Province, Country等)
        {
            if (!flag)
            {
				column = my_strtok(buffer + index, delimit);
                flag = TRUE;
            }
            else
                column = my_strtok(NULL, delimit);
			if(column)
				strcpy(p->column[i], column);
			else strcpy(p->column[i], "/");
        }
        for (i = 0; i < N; i++) //读后几列的数据, 包括Confirmed, Death等
        {
            figure[i] = my_strtok(NULL, delimit);
			if(figure[i])
				p->figure[i] = atoi(figure[i]); //从指定位置开始, 将字符串转化成整型
			else p->figure[i] = 0;
        }
        p->next = NULL;
        if (!head)
            head = p;
        else
            tail->next = p;
        tail = p;
		line++;      //count the number of lines;
    }
    if (fclose(ptr))
    {
        printf("Cannot close file!\n");
        exit(0);
    }
	List->head = head;
	List->line = line;
	MaxAndFrac(List);
	return List;
}

/*
*Function: AddData
*Usage: AddData(char *date);
*-----------------------------
*This function is used to add a new
*record into a file.
*/
void AddData(char *date, Data *target)
{
    FILE *fp = NULL;
	char filename[40] = "", way[]="a+";
    int n;
	if(isForecast && isUsed)
		sprintf(filename, "%s-2020y.csv", date);
	else 
		sprintf(filename, "%s-2020.csv", date);
    if ((fp = fopen(filename, way)) == NULL)
    {
		isWarning = TRUE;
        exit(0);
    }
	fseek(fp, 0L, SEEK_SET);
	if (!fgets(buffer, MAXLINE, fp))
	{
		fprintf(fp, "%s,%s,%s,%s,%s,%s\n", "Province/State", "Country/Rigeon", "Last Update", "Confirmed", "Death", "Recovered");
	}
    fseek(fp, 0L, SEEK_END);
    fprintf(fp, "%s,%s,%s,", target->column[PRO_STA], target->column[COU_RIG], target->column[UPDATE_TIME]);
    fprintf(fp, "%d,%d,%d\n", target->figure[CONFIRM], target->figure[DEATH], target->figure[RECOVERED]);
    if (fclose(fp))
    {
		isWarning = TRUE;
        exit(0);
    }
	else
	{
		isSuccess = TRUE;
	}
}

/*
*Function: UpdateData
*Usage: UpdateData();
------------------------
*This function is used to update the data exists in
*the file.
*/
void UpdateData(char *date, Data *target)
{
    
	 Data *p, *t, *m;
	 Combine *cp = NULL; 	
	 if (target)
		 t = target->next;
	 if (strcmp(target->column[PRO_STA], "Hubei") && strcmp(target->column[COU_RIG], "ForeignCountry"))
	 {
		 cp = ReadData(date);
		 if (cp)
		{
			p = Search("OtherProvince", cp->head, PRO_STA);
			m = Search(target->column[PRO_STA], cp->head, PRO_STA);
		}
		 if (p && t && m)
			 for (int i = 0; i < 3; i++)
				 p->figure[i] += (t->figure[i] - m->figure[i]);
		 p->next = NULL;
		 EditData(date, UPDATE, p);	 
	 } 
	 EditData(date, UPDATE, target);

}


/*
*Function: DeleteData
*Usage: DeleteData();
-----------------------
*This function is used to delete a record
*from a file.
*/
void DeleteData(char *date, Data *target)
{
   
	Data *p, *t;
	Combine *cp = NULL;
	if (strcmp(target->column[PRO_STA], "Hubei") && strcmp(target->column[COU_RIG], "ForeignCountry"))
	{
		cp = ReadData(date);
		if (cp)
		{
			p = Search("OtherProvince", cp->head, PRO_STA);
			t = Search(target->column[PRO_STA], cp->head, PRO_STA);
		} if (p && t)
			for (int i = 0; i < 3; i++)
				p->figure[i] -= t->figure[i];
		p->next = NULL;
		EditData(date, UPDATE, p);
	}
	EditData(date, DELETE_P, target);
}

/*
*Function: EditData
*Usage: EditData(date, choice, target);
*---------------------------------------------- 
*It can both update a record and delete a 
*record, and it differs by inputing different choice
*if the choice is UPDATE, and it is in updating state,
*when it is DELETE, it will be in deleting state.
*"date" value is the date of file you want.
*/
void EditData(char *date, int choice, Data *target)
{

    FILE *fp, *nfp;
	Data *update = NULL; 
	char filename[40] = "";
    char *t1, *t2, *t3; //target feature
    int flag = 0, n, row = 1, i, len;
	if (target)    update = target->next;
	if (!update)    update = target;
    sprintf(filename, "%s-2020.csv", date);
    if ((fp = fopen(filename, "r+")) == NULL)
    {
		isWarning = TRUE;
        exit(0);
    }
    flag = 0;
 
    while (fgets(buffer, MAXLINE, fp))
    {
        t1 = my_strtok(buffer, ",");
        t2 = my_strtok(NULL, ",");
        if (strcmp(target->column[PRO_STA], t1) == 0)
            if (strcmp(target->column[COU_RIG], t2) == 0)
            {
                flag = 1;
                break;
            }
        row++;
    }
	if (flag)
	{
		
		if (choice == UPDATE && update == NULL)
			return;
			
			fseek(fp, 0L, SEEK_SET);
			if ((nfp = fopen("tempfile.csv", "w+")) == NULL)
			{
				isWarning = TRUE;
				exit(0);
			}

			while (fgets(buffer, MAXLINE, fp))
			{

				t1 = my_strtok(buffer, ",");
				if (!strcmp(t1, "0"))
					t1 = "";
				t2 = my_strtok(NULL, ",");
				if (!(strcmp(t1, target->column[PRO_STA]) || strcmp(t2, target->column[COU_RIG])) && choice == DELETE_P)
					continue;
				fprintf(nfp, "%s,%s,", t1, t2);
				if (!(strcmp(t1, target->column[PRO_STA]) || strcmp(t2, target->column[COU_RIG])) && choice == UPDATE)
					fprintf(nfp, "%s,%d,%d,%d\n", update->column[UPDATE_TIME], update->figure[CONFIRM], update->figure[DEATH], update->figure[RECOVERED]);
				else
				{
					i = 0;
					t3 = my_strtok(NULL, ",");
					while (i < L + N - 3)
					{
						fprintf(nfp, "%s,", t3);
						t3 = my_strtok(NULL, ",");
						if (!strcmp(t3, "\n"))
							t3 = "0\n";
						i++;
					}
					fprintf(nfp, "%s", t3);
				}
			}
			if (fclose(nfp))
			{
				isWarning = TRUE;
				exit(0);
			}
			if (fclose(fp))
			{
				isWarning = TRUE;
				exit(0);
			}
			remove(filename);
			if (rename("tempfile.csv", filename) == 0)
				isSuccess = TRUE;
		}
		else
		{
			isWarning = TRUE;
			return;
		}
		//	printf("Record Not Found! Please try another one:\n");
	
}

void MaxAndFrac(Combine *List)
{
	if (!List)
		return;
	Data *p = List->head, *pp = NULL;
	int *max = List->max, i, j = 0;
	int sum[N];
	memset(sum, 0, N * sizeof(int));
	memset(max, -1, N);
	while (p)
	{
		for (i = 0; i < N; i++)
		{
			if (p->figure[i] > max[i])
				max[i] = p->figure[i];
		}
		p = p->next;
	}
	
	p = List->head;
	pp = Search("OtherProvince", p, PRO_STA);
	while (p && pp && strcmp("OtherProvince", p->column[PRO_STA]))
	{
		for (i = 0; i < N; i++)
			p->fraction[i] = 1.0 * p->figure[i] / (pp->figure[i]);
		p = p->next;
	}
}

Data *Search(char *name, Data *head, int col)
{
	Data *res = head;
//	res = (Data*)malloc(sizeof(Data));
	while (res)
	{
		if (strcmp(res->column[col], name) == 0)
			break;
		res = res->next;
	}
	return res;
}

Combine *ReadSeries(char *start, char *end)
{
	Combine *List, *Chead;
	Data *dp[3] = { NULL }, *head[3] = { NULL }, *tail[3] = { NULL }, *td;
	char lable[][30] = { "Hubei", "OtherProvince", "ForeignCountry" };
	char **daterange;
	int i, j, temp[3];
	memset(temp, -1, sizeof(temp));
 	Chead = (Combine*)malloc(sizeof(Combine));
	daterange = DateRange(start, end, 0);
	for (i = 0; i <sum_1; i++)
	{
		List = ReadData(daterange[i]);
		if (!List) continue;
		for (j = 0; j < 3; j++)
		{
			if (temp[j] < List->max[j])
				temp[j] = List->max[j];
			dp[j] = (Data*)malloc(sizeof(Data));
			if (j < 2)
			{
				if ((td = Search(lable[j], List->head, PRO_STA)) != NULL)
					*(dp[j]) = *td;
			}
			else{
					if ((td = Search(lable[j], List->head, COU_RIG)) != NULL)
						*(dp[j]) = *td;
				}
//修改日期
			memset(dp[j]->column[UPDATE_TIME], 0, sizeof(dp[j]->column[UPDATE_TIME]));
			strcpy(dp[j]->column[UPDATE_TIME], daterange[i]);

			if (!head[j])
				head[j] = dp[j];
			else
				tail[j]->next = dp[j];
			tail[j] = dp[j];
		}
		if(List)
			free(List);
		List = NULL;
	}

	Chead->dp[0] = head[0];
	Chead->dp[1] = head[1];
	Chead->dp[2] = head[2];
	Chead->line = sum_1;

	for (j = 0; j < 3; j++)
		Chead->max[j] = temp[j];
	return Chead;
	
}

char **DateRange(char *start, char *end, int dur)
{
	int date[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day, month, i = 0;
	char **res, *subres, *str;
	char ts[30]="", te[30]="";
	if(start)
	strcpy(ts, start);
	if(end)
	strcpy(te, end);
	sum_1 = 0;
	typedef struct my_date
	{
		int day;
		int month;
		struct my_date *next;
	}my_date;
	my_date *head, *tail, *p;
	head = tail = p = NULL;
	my_date stend[2];

	if((str = strtok(ts, "-")))
		stend[0].month = atoi(str);
	if((str = strtok(NULL, "-")))
		stend[0].day = atoi(str);
	if((str = strtok(te, "-")))
		stend[1].month = atoi(str);
	if((str = strtok(NULL, "-")))
		stend[1].day = atoi(str);
	day = stend[0].day;
	month = stend[0].month;
	if (dur)
	{
		stend[1].day = 0;
		stend[1].month = 0;
	}
	while (day != stend[1].day || month != stend[1].month)
	{
		p = (my_date*)malloc(sizeof(my_date));
		p->day = day;
		p->month = month;
		p->next = NULL;
		if (day == date[month])
		{
			month = month++;
			month %= 12;
			day = 1;
		}
		else
			day++;
		if (!head)
			head = p;
		else
		{
			tail->next = p;
		}
		tail = p;
		sum_1++;
		if (dur && sum_1 == dur + 1)
			break;
	} 
	if (tail && !dur)
	{
		p = (my_date*)malloc(sizeof(my_date));
		p->day = stend[1].day;
		p->month = stend[1].month;
		p->next = NULL;
		tail->next = p;
		sum_1++;
	}

	res = (char**)malloc(sum_1*sizeof(char*));
	for (i = 0; i < sum_1; i++)
	{
		subres = (char*)malloc(40 * sizeof(char));
		res[i] = subres;
	}
	i = 0;
	p = head;
	while (p && i < sum_1)
	{
		sprintf(res[i++], "%02d-%02d", p->month, p->day);
		p = p->next;
	}
	return res;
}

void Forecast(char *start, char *end, char *day)
{
	int n = 10, i,j;
	double R0[3];
	Data *dp[3] = { NULL }, *enddata[3];
	char *col_1[] = { "Hubei", "OtherProvince", "/" };
	char *col_2[] = { "Mainland China", "China", "ForeignCountry" };
	char **date, tend[30], tstart[30], temp[30];
	Combine *end_0, *start_0;
	int test[3];
	isUsed = FALSE;
	end_0 = ReadData(end);
	start_0 = ReadData(start);
	if (!end_0 || !start_0) return;
	strcpy(tend, end);
	if (day)
		n = atoi(day);	
	date = DateRange(tend, 0, n);
	for (i = 0; i < 3; i++)
	{
		strcpy(tstart, start);
		strcpy(tend, end);
		R0[i] = basic(tstart, tend, i);
//		R0[i] = 5.98;
		if (i < 2)
			enddata[i] = Search(col_1[i], end_0->head, PRO_STA);
		else
			enddata[i] = Search(col_2[i], end_0->head, COU_RIG);
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < 3; j++)
		{
			dp[j] = (Data*)malloc(sizeof(Data));
			strcpy(dp[j]->column[PRO_STA], col_1[j]);
			strcpy(dp[j]->column[COU_RIG], col_2[j]);
			strcpy(dp[j]->column[UPDATE_TIME], date[i]);
			if (enddata[j])
			{
				dp[j]->figure[CONFIRM] = I(i, R0[j], j) + enddata[j]->figure[CONFIRM];
				dp[j]->figure[RECOVERED] = R(i, R0[j], j) + enddata[j]->figure[RECOVERED];
				test[0] = I(i, R0[j], j);
				test[1] = R(i, R0[j], j);
				dp[j]->figure[DEATH] = 0;
			}
			isUsed = TRUE;
			AddData(date[i], dp[j]);
		}
	}
		cop = ReadSeries(date[1], date[n]);
		isUsed = FALSE;
	for (i = 1; i <= n; i++)
	{
		sprintf(temp, "%s-2020y.csv", date[i]);
		remove(temp);
	}

}