#include "menu.h"
#include "file.h"
#include "PieChart.h"
Combine* cop;
extern struct PieChart *PieChartHead;
extern struct histogram  *HistogramHead;
extern struct LineChart  *LineChartHead;
extern int state;
extern bool isWarning;


void DrawBranch()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	static char lable_1[] = "请选择图表类型";
	static char lable_2[] = "条形图或折线图";
	static char lable_3[] = "饼图";
	SetPenColor("Brown");
	drawRectangle(0.3*x, 0.5*y, boxwidth, boxheight, 0);
	MovePen(0.3*x+0.5*(boxwidth -TextStringWidth(lable_1)), 0.5*y + 0.67*boxheight);
	DrawTextString(lable_1);
//	MovePen(0.3*x + TextStringWidth(lable_1), 0.7*y + 0.5*boxheight);
	if (button(GenUIID(0), 0.3*x+ 0.5*(boxwidth - 1.2*TextStringWidth(lable_2)), 0.5*y + 0.4*boxheight, 1.2*TextStringWidth(lable_2), buttonheight, lable_2))
	{
		isQuest_1 = TRUE;
		isBranch = FALSE;
	}
	if (button(GenUIID(0), 0.3*x + 0.5*(boxwidth - 1.2*TextStringWidth(lable_2)), 0.5*y + 0.25*boxheight, 1.2*TextStringWidth(lable_2), buttonheight, lable_3))
	{
		isQuest_2 = TRUE;
		isBranch = FALSE;
	}
}

void DrawQuest_1()
{
	static char text_1[100] = "";
	static char text_2[100] = "";
	static char text_3[10] = "";
	static char *lable_1 = "开始日期:";
	static char *lable_2 = "截止日期:";
	static char *lable_3 = "预测的天数:";
	setTextBoxColors("Brown", "Brown", "Dark Gray", "Dark Gray", 0);
	double x = GetWindowWidth()/3;
	double y = GetWindowHeight()/2;
	if (!cop)
		cop = (Combine*)malloc(sizeof(Combine));
	drawRectangle(x - boxwidth * 1.6, y, boxwidth, boxheight, 0);
	SetPenColor("Brown");
	MovePen(x- 1.55*boxwidth, y + 0.6*boxheight);
	DrawTextString(lable_1);
	textbox(GenUIID(0), x - 0.5*(2*boxwidth + 0.8*buttonwidth), y + 0.6*boxheight, 1.5*buttonwidth, buttonheight, text_1, sizeof(text_1));
	MovePen(x - 1.55*boxwidth, y + 0.6*boxheight - 2*buttonheight);
	DrawTextString(lable_2);
	textbox(GenUIID(0), x - 0.5*(2*boxwidth + 0.8*buttonwidth) , y + 0.6*boxheight - 2*buttonheight, 1.5*buttonwidth, buttonheight, text_2, sizeof(text_2));
	if (isForecast)
	{
		MovePen(x - 1.55*boxwidth, y + 0.6*boxheight - 4 * buttonheight);
		DrawTextString(lable_3);
		textbox(GenUIID(0), x - 0.5*(2 * boxwidth + 0.8*buttonwidth), y + 0.6*boxheight - 4 * buttonheight, 1.5*buttonwidth, buttonheight, text_3, sizeof(text_3));
	}
	if (button(GenUIID(0),x - boxwidth, y + 0.2*boxheight, 0.8*buttonwidth, buttonheight, "继续"))
	{
		if (strcmp(text_1, "") && strcmp(text_2, ""))
		{
//			isQuest_1 = FALSE;
			if (isForecast == FALSE)
			{
				showButton_1 = TRUE;
				isStateButton = TRUE;
				cop = (ReadSeries(text_1, text_2));
				memset(text_1, 0, sizeof(text_1));
				memset(text_2, 0, sizeof(text_2));
			}
			else {
				showButton_1 = TRUE;
				isStateButton = TRUE;
				Forecast(text_1, text_2, text_3);
//				cop = ReadSeries(text_2, text_1);
				memset(text_1, 0, sizeof(text_1));
				memset(text_2, 0, sizeof(text_2));
			}

		}
	}
	
}

void DrawQuest_2()
{
	static char text_3[100] = "";
	static char lable_3[] = "你想看哪一天的数据呢?";
	double x = GetWindowWidth()/3;
	double y = GetWindowHeight()/2;
	setTextBoxColors("Brown", "Brown", "Dark Gray", "Dark Gray", 0);
	if (!cop)
		cop = (Combine*)malloc(sizeof(Combine));
	drawBox(x - boxwidth*1.5, y, boxwidth, boxheight, 0, lable_3, 'c', "Brown");
	MovePen(x - boxwidth * 1.25, y + boxheight * 0.7);
	DrawTextString("输入格式:02-10");
	MovePen(x - boxwidth * 1.3, y + 0.9*boxheight * 0.7);
	DrawTextString("数据范围:01-22至02-25");
	textbox(GenUIID(0), x + 0.3*boxwidth - boxwidth*1.55, y + 0.3*boxheight, 0.5*boxwidth, 1.2*buttonheight, text_3, sizeof(text_3));
	if (button(GenUIID(0), x + 0.5*(1.3*boxwidth) - boxwidth*1.5, y + 0.1*boxheight, buttonwidth, buttonheight, "继续"))
	{
		if (strcmp(text_3, ""))
		{
//			isQuest_2 = FALSE;
			strcpy_s(cop->date, sizeof(cop->date), text_3);
			cop = ReadData(text_3);
			memset(text_3, 0, sizeof(text_3));
			showButton_2 = TRUE;
			isPieChart = TRUE;
			isStateButton = TRUE;
		}
	}
}

void DrawButton_1()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	if (button(GenUIID(0), 0.5*(x - 2 * buttonwidth), 0.75*y, buttonwidth, buttonheight, "条形图"))
	{
		isHistogram = TRUE;
		isPieChart = FALSE;
		isLineChart = FALSE;
	}
	if (button(GenUIID(0), 0.5*(x + 2 * buttonwidth), 0.75*y, buttonwidth, buttonheight, "折线图"))
	{
		isLineChart = TRUE;
		isPieChart = FALSE;
		isHistogram = FALSE;
	}

}

void DrawButton_2()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	if (button(GenUIID(0), 0.5*(x - 4 * buttonwidth), 0.75*y, 2 * buttonwidth, buttonheight, "湖北与湖北以外"))
	{
		isHubei = TRUE;
		if (PieChartHead != NULL)
		{
			free(PieChartHead);
			PieChartHead = NULL;
		}
	}
	if (button(GenUIID(0), 0.5*(x + 4 * buttonwidth), 0.75*y, 2 * buttonwidth, buttonheight, "湖北以外"))
	{
		isHubei = FALSE;
		if (PieChartHead != NULL)
		{
			free(PieChartHead);
			PieChartHead = NULL;
		}
	}

}

void DrawStateButton()
{
	double x = GetWindowWidth();
	double y = GetWindowHeight();
	if (button(GenUIID(0), 0.8 * x, 0.7 * y, 1.5*buttonwidth, 1.2*buttonheight, "确诊"))
	{
		state = CONFIRM;
		FreeHead();
	}
	if (!isForecast && button(GenUIID(0), 0.8*x, 0.7*y - 2*buttonheight, 1.5*buttonwidth, 1.2*buttonheight, "死亡"))
	{
		state = DEATH;
		FreeHead();
	}
	if (button(GenUIID(0), 0.8*x, 0.7*y - 4 * buttonheight, 1.5*buttonwidth, 1.2*buttonheight, "治愈"))
	{
		state = RECOVERED;
		FreeHead();
	}
}

void DrawEdit()
{

	double x = GetWindowWidth();
	double y = GetWindowHeight();
	static char text_1[50], text_2[50], text_3[50], text_4[50], text_5[50], text_6[50], text_7[50];
	static char *lable_1 = "你想编辑哪一天的数据呢?";
	static char *lable_2 = "你想做什么?";
	static char *lable_3 = "更新一行数据";
	static char *lable_4 = "删除一行数据";
	static char *lable_5 = "添加一行数据";
	Data *tar, *upd;
	tar = (Data*)malloc(sizeof(Data));
	upd = (Data*)malloc(sizeof(Data));
	tar->next = upd;
	upd->next = NULL;
	drawRectangle(0.5*(x - 2 * boxwidth), 0.5*(y - 1.5*boxheight), 2 * boxwidth, 1.5*boxheight, 0);
	setTextBoxColors("Brown", "Black", "Dark Gray", "Dark Gray", 0);
	MovePen(0.5*(x - TextStringWidth(lable_1)), 0.5*(y + boxheight));
	DrawTextString(lable_1);
	textbox(GenUIID(0), 0.5*(x - 3 * buttonwidth), 0.5*(y + 0.7*boxheight), 3 * buttonwidth, 1.3*buttonheight, text_1, sizeof(text_1));
	MovePen(0.5*(x - TextStringWidth(lable_2)), 0.5*y - 0.45*boxheight);
	DrawTextString(lable_2);

	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 0.7*buttonheight);
	DrawTextString("目标省份名:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 2.2*buttonheight);
	DrawTextString("目标国家名:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 3.7 * buttonheight);
	DrawTextString("更新时间:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 5.2*buttonheight);
	DrawTextString("确诊人数:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 6.7* buttonheight);
	DrawTextString("死亡人数:");
	MovePen(0.5*x - 0.6*boxwidth, 0.6*y - 8.2*buttonheight);
	DrawTextString("治愈人数:");

	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_2, sizeof(text_2));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 2.5*buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_3, sizeof(text_3));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 4 * buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_4, sizeof(text_4));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 5.5*buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_5, sizeof(text_5));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 7 * buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_6, sizeof(text_6));
	textbox(GenUIID(0), 0.5*x + 0.2*boxwidth, 0.6*y - 8.5*buttonheight, 1.8*buttonwidth, 1.2*buttonheight, text_7, sizeof(text_7));


	if (button(GenUIID(0), 0.5*x - 2.6*buttonwidth, 0.5*y - 9 * buttonheight, 1.7*buttonwidth, 1.5*buttonheight, lable_3))
	{
		strcpy(tar->column[PRO_STA], text_2);
		strcpy(tar->column[COU_RIG], text_3);
		strcpy(upd->column[UPDATE_TIME], text_4);
		if (text_5)
			upd->figure[CONFIRM] = atoi(text_5);
		if (text_6)
			upd->figure[DEATH] = atoi(text_6);
		if (text_7)
			upd->figure[RECOVERED] = atoi(text_7);
				UpdateData(text_1, tar);
		isUpdate = TRUE;
		isEdit = FALSE;
	}

	if (button(GenUIID(0), 0.5*x - 0.6*buttonwidth, 0.5*y - 9 * buttonheight, 1.7*buttonwidth, 1.5*buttonheight, lable_5))
	{
		strcpy(tar->column[PRO_STA], text_2);
		strcpy(tar->column[COU_RIG], text_3);
		strcpy(tar->column[UPDATE_TIME], text_4);
		if (text_5)
			tar->figure[CONFIRM] = atoi(text_5);
		if (text_6)
			tar->figure[DEATH] = atoi(text_6);
		if (text_7)
			tar->figure[RECOVERED] = atoi(text_7);
		AddData(text_1, tar);
		isAdd = TRUE;
		isEdit = FALSE;
	}	
	if (button(GenUIID(0), 0.5*x + 1.4*buttonwidth, 0.5*y - 9 * buttonheight, 1.7*buttonwidth, 1.5*buttonheight, lable_4))
	{
		strcpy(tar->column[PRO_STA], text_2);
		strcpy(tar->column[COU_RIG], text_3);
				DeleteData(text_1, tar);
		isDelete = TRUE;
		isEdit = FALSE;
	}

}

void DrawForecast()
{
	DrawQuest_1();
}

void DrawSuccess()
{
	double x = GetWindowWidth() / 3;
	double y = GetWindowHeight() / 2;
	static char *lable_1 = "更新成功!";
	static char *lable_2 = "删除成功!";
	static char *lable_3 = "添加成功!";
	if(isUpdate)
		drawBox(x, y, boxwidth, boxheight, 0, lable_1, 'C', "Dark Gray");
	else if(isDelete)
		drawBox(x, y, boxwidth, boxheight, 0, lable_2, 'C', "Dark Gray");
	else if (isAdd)
		drawBox(x, y, boxwidth, boxheight, 0, lable_3, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.5*(boxwidth - buttonwidth), y + 0.2*boxheight, buttonwidth, buttonheight, "知道啦"))
	{
		isSuccess = FALSE;
		isUpdate = isDelete = isAdd = FALSE;
	}
}

void FreeHead()
{
	while(PieChartHead != NULL)
	{
		free(PieChartHead);
		PieChartHead = NULL;
	}
	while (HistogramHead != NULL)
	{
		free(HistogramHead);
		HistogramHead = NULL;
	}
	while (LineChartHead != NULL)
	{
		free(LineChartHead);
		LineChartHead = NULL;
	}
}

void DrawWarning()
{
	char lable[] = "File Not Found! Please Retry";
	double x = GetWindowWidth() / 3;
	double y = GetWindowHeight() / 2;
	drawBox(x, y, boxwidth, boxheight, 0, lable, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.5*(boxwidth - buttonwidth), y + 0.2*boxheight, buttonwidth, buttonheight, "知道啦"))
		isWarning = FALSE;
}

void DrawHelp()
{
	char lable[500] = "/0";
	double x = 0.1;
	double y = 0.1;
	drawBox(x, y, GetWindowWidth()*0.8, GetWindowHeight() - 0.5, 0, lable, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.1, y + 0.1, 1.2*buttonwidth, buttonheight, "知道啦"))
		showHelp = FALSE;
	SetPenColor("Black");
	MovePen(0.2, GetWindowHeight() - 0.6);
	strcpy(lable, "File        选择要进行的操作：");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - GetFontHeight()*1.5);
	strcpy(lable, "1.NewFile（快捷键Ctrl+N）        建立新的图表：");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 2 * GetFontHeight() * 1.5);
	strcpy(lable, "选择条形图或折线图可以呈现条形图和折线图，在开始日期框输入开始日期,在截止日期框");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 3 * GetFontHeight() * 1.5);
	strcpy(lable, "输入截止日期，按下继续，再选择   条形图   或者   折线图   分别呈现条形图和折线图，");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 4 * GetFontHeight() * 1.5);
	strcpy(lable, "选择确诊可查看确诊人数，选择死亡可查看死亡人数，选择治愈可查看治愈");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 5 * GetFontHeight() * 1.5);
	strcpy(lable, "人数。");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 6 * GetFontHeight() * 1.5);
	strcpy(lable, "选择饼图呈现饼状图，输入想查看的日期，按下继续,再选择查看湖北或者湖北以外");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 7 * GetFontHeight() * 1.5);
	strcpy(lable, "的饼状图，选择确诊可查看确诊人数，选择死亡可查看死亡人数，选择治愈");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 8 * GetFontHeight() * 1.5);
	strcpy(lable, "可选择治愈人数。");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 9 * GetFontHeight() * 1.5);
	strcpy(lable, "2.Edit（快捷键Ctrl+E）        编辑，在你下输入想编辑的日期，在");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 10 * GetFontHeight() * 1.5);
	strcpy(lable, "目标省份右侧选择省份，在目标国家右侧选择国家，在更新时间右侧输入录");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 11 * GetFontHeight() * 1.5);
	strcpy(lable, "入数据的最新时间，在确诊人数右侧选择确诊人数，在死亡人数选择死亡");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 12 * GetFontHeight() * 1.5);
	strcpy(lable, "人数，在治愈人数右侧框选择治愈人数。选择更新一行数据更新数据，选择添加一行数据");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 13 * GetFontHeight() * 1.5);
	strcpy(lable, "添加数据，选择删除一行数据删除数据。");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 14 * GetFontHeight() * 1.5);
	strcpy(lable, "3.Forecast（快捷键Ctrl+F）        对数据进行预测，在开始日期框输入开始日期,在截止日期框输入截");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 15 * GetFontHeight() * 1.5);
	strcpy(lable, "止日期，在预测天数输入想预测的天数，按下继续，再选择   条形图   或者   折线图   ");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 16 * GetFontHeight() * 1.5);
	strcpy(lable, "分别呈现条形图和折线图，选择确诊可查看确诊人数，选择治愈可查看治愈人");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 17 * GetFontHeight() * 1.5);
	strcpy(lable, "数。");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 18 * GetFontHeight() * 1.5);
	strcpy(lable, "4.Close（快捷键Ctrl+C）        关闭当前进行的窗口。");
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 19 * GetFontHeight() * 1.5);
	strcpy(lable, "5.Exit        关闭本程序。");
	MovePen(0.2, GetWindowHeight() - 0.6 - 20 * GetFontHeight() * 1.5);
	DrawTextString(lable);
	MovePen(0.2, GetWindowHeight() - 0.6 - 21 * GetFontHeight() * 1.5);
	DrawTextString("注意, 本应用目前数据范围在01-22至02-25, 输入超出范围的数据会自动退出!");
}	

void DrawAbout()
{
	char about[] = "Pandemic 1.0";
	double x = GetWindowWidth() / 3;
	double y = GetWindowHeight() / 2;
	drawBox(x, y, boxwidth, boxheight, 0, about, 'C', "Dark Gray");
	if (button(GenUIID(0), x + 0.5*(boxwidth - buttonwidth), y + 0.2*boxheight, buttonwidth, buttonheight, "Got it"))
		showAbout = FALSE;
}

void DrawMenu()
{
	static char *main_menu[] =
	{
		"File",
		"NewFile  | Ctrl-N",
		"Edit     | Ctrl-E",
		"Forcast  | Ctrl-F",
		"Close    | Ctrl-C",
		"Exit",
	};

	static char *help[] =
	{
		"Help",
		"Read Help | Ctrl-H",
		"About"
	};

	double x, y, w, h, wlist, n;
	h = GetFontHeight() * 1.5;
	w = 0.5;
	x = 0;
	y = GetWindowHeight();
	wlist = TextStringWidth(main_menu[0]) * 4;
	w = TextStringWidth(main_menu[0]) * 1.5;
	n = 4;
	int choice;
	setMenuColors("Black", "Brown", "Dark Gray", "Light Gray", 0);
	setTextBoxColors("Black", "Brown", "Dark Gray", "Light Gray", 0);
	setButtonColors("Black", "Brown", "Dark Gray", "Light Gray", 0);
	choice = menuList(GenUIID(0), x, y-h, w, wlist*1.5, h, main_menu, sizeof(main_menu)/sizeof(main_menu[0]));
	switch (choice)
	{
	case 1:
		RefreshAll();
		isBranch = TRUE;
		break;
	case 2:
		RefreshAll();
		isEdit = TRUE;
		break;
	case 3:
		RefreshAll();
		isForecast = TRUE;
		break;
	case 4:
		RefreshAll();
		break;
	case 5:
		exit(-1);
		break;
	}

	choice = menuList(GenUIID(0), x + w, y-h, w*1.2, wlist*1.5, h, help, sizeof(help) / sizeof(help[0]));
	switch (choice)
	{ 
	case 1:
		showHelp = TRUE;
		break;
	case 2:
		showAbout = TRUE;
		break;
	}
}

void RefreshAll()
{
	showButton_1 = FALSE;
	showButton_2 = FALSE;
	showAbout = FALSE;
	isHistogram = FALSE;
	isPieChart = FALSE;
	isLineChart = FALSE;
	isStateButton = FALSE;
	isBranch = FALSE;
	isQuest_1 = FALSE;
	isQuest_2 = FALSE;
	isEdit = FALSE;
	isUpdate = FALSE;
	isDelete = FALSE;
	isSuccess = FALSE;
	isForecast = FALSE;
	free(cop);
	cop = NULL;
	DisplayClear();
}



