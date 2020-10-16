#include"forcast.h"
//double R0;//基本自然传染数//
double TE = 6.5;//潜伏期的天数，暂定//
double TL = 7;//传染期天数，暂定//
double Tg = 13.5;//TE+TL//
double E1[3] ;//第一天的潜伏人数//
double E2[3];//第二天的潜伏人数//
double I1[3];//第一天的传染人数，第一天的确诊人数，需要从数据库中得到//
double I2[3];//第二天的传染人数//
double  R00[3];//第一天的治愈人数//
//网上数据：非湖北地区水平大约为2.3562~4.7124；湖北地区为5.30026~10.60052。//

double E(int t, double R0, int district)    //单位时间内潜伏期人群（E）的变化等于新增加的感染者减去由潜伏期过渡到传染期的数量。(潜伏期)//
{
	double r1, r2, b;
//	R0 = basic(start, end);
	r1 = 1.0 / TE;
	r2 = 1.0 / TL;
	b = R0 * 1.0 / TL;
	if (t >=2)
		return (2 - r1 - r2) * E(t - 1, R0, district) + (b * r1 - r2 * r1 + r1 + r2 - 1) * E(t - 2, R0, district);
	else if (t == 1)
		return E2[district];
	else if (t == 0)
		return E1[district];
}
double I(int t, double R0, int district)    //单位时间内传染期人群（I）的变化等于新由潜伏期过渡到传染期的人数，减去从传染期进入到隔离态的人数。(传染期)//
{
	double r1, r2, b;
	r1 = 1.0 / TE;
	r2 = 1.0 / TL;
	b = R0 * 1.0 / TL;
	if (t > 2)
		return (2 - r1 - r2) * I(t - 1, R0, district) + (b * r2 - r1 * r2 + r1 + r2 - 1) * I(t - 2,R0, district);
	else if (t == 2)
		return 	I2[district];
	else if (t == 1)
		return I1[district];
	else return 0;
}
double R(int t, double R0, int district)   //单位时间隔离态的人数等于新增的从传染期进入隔离态的人数。(隔离态)//
{
	double r1, r2, b;
	r1 = 1.0 / TE;
	r2 = 1.0 / TL;
	b = R0 * 1.0 / TL;
	if (t > 0)
		return R(t - 1, R0, district) + r2 * I(t - 1, R0, district);
	else
		return R00[district];

}