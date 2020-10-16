#include"R0.h"
double mx; //指数增长率//
extern double Tg;
double scale = 0.48148;
extern double I1[3];
extern double I2[3];
extern double R00[3];

double basic(char *start,char *end, int district)//计算基本自然传染数R0//
{
    double Rtotal = 0;
	Combine* p = NULL;
    double Rx;
    int i;
    int *a;
    Data* dp[3];
    int duration;
	if (!p)
	{
		p = (Combine*)malloc(sizeof(Combine));
		p = ReadSeries(start, end);
	}
    duration = p->line; 
    a = (int*)malloc(duration*sizeof(int));
    for (int i = 0; i < 3; i++)
        dp[i] = p->dp[i];

    for ( i = 0; i < duration && dp[0]; i++)
    {
			a[i] = dp[district]->figure[CONFIRM];
			dp[district] = dp[district]->next;
			if (i == 0)
			{
				I1[district] = dp[district]->figure[CONFIRM];
				I2[district] = dp[district]->figure[CONFIRM];
				R00[district] = dp[district]->figure[CONFIRM];
			}
			if (i == 1)
				I2[district] = dp[district]->figure[CONFIRM];
    }
    for (i = 0; i < duration; i++)
    {
        mx = log(a[i]) * 1.0 / duration;
            Rx = 1 + mx * Tg + scale * (1 - scale) * (mx * Tg) * (mx * Tg);
        Rtotal += Rx;
    }
    return Rtotal*1.0/duration;
}

