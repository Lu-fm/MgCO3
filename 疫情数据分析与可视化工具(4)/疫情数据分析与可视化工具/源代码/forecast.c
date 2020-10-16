#include"forcast.h"
//double R0;//������Ȼ��Ⱦ��//
double TE = 6.5;//Ǳ���ڵ��������ݶ�//
double TL = 7;//��Ⱦ���������ݶ�//
double Tg = 13.5;//TE+TL//
double E1[3] ;//��һ���Ǳ������//
double E2[3];//�ڶ����Ǳ������//
double I1[3];//��һ��Ĵ�Ⱦ��������һ���ȷ����������Ҫ�����ݿ��еõ�//
double I2[3];//�ڶ���Ĵ�Ⱦ����//
double  R00[3];//��һ�����������//
//�������ݣ��Ǻ�������ˮƽ��ԼΪ2.3562~4.7124����������Ϊ5.30026~10.60052��//

double E(int t, double R0, int district)    //��λʱ����Ǳ������Ⱥ��E���ı仯���������ӵĸ�Ⱦ�߼�ȥ��Ǳ���ڹ��ɵ���Ⱦ�ڵ�������(Ǳ����)//
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
double I(int t, double R0, int district)    //��λʱ���ڴ�Ⱦ����Ⱥ��I���ı仯��������Ǳ���ڹ��ɵ���Ⱦ�ڵ���������ȥ�Ӵ�Ⱦ�ڽ��뵽����̬��������(��Ⱦ��)//
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
double R(int t, double R0, int district)   //��λʱ�����̬���������������ĴӴ�Ⱦ�ڽ������̬��������(����̬)//
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