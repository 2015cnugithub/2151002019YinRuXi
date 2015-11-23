#include<iostream>
#include<iomanip>
using namespace std;
	
class Calen
{
private:
	int SpaceSize;
	int year,month;
public:
	Calen(int y, int m);
	~Calen();
	bool IsLeapYear(int y);//判断是否为闰年
	int FindStartDay();//计算1800年该月第一天是星期几
	int FindRealDay();//计算该年该月第一天是星期几
	void DisplayMonth();//打印输入月份的日历
};

Calen::Calen(int y, int m)
{
	year=y;
	month=m;
}
Calen::~Calen()
{

}

bool Calen::IsLeapYear(int year)
{
	if((year%4==0&&year%100!=0)||(year%400==0))
		return true;
	else return false;
}

int Calen::FindStartDay()
{
	int CountMonth=0;
	int i;
	for(i=1;i<month;i++)//i为1800年该月之前的月份数
	{
		if(i==2)
		{
			CountMonth+=28;//1800年为平年
		}
		else
		{
			if((i<8&&i%2==1)||(i>=8&&i%2==0)) CountMonth+=31;//该月为八月之前，并且是偶数月时，增加上个月的31天；该月为八月之后，并且是奇数月时，增加上个月的31天
			if((i<8&&i%2==0)||(i>=8&&i%2==1)) CountMonth+=30;//该月为八月之前，并且是奇数月时，增加上个月的30天；该月为八月之后，并且是偶数月时，增加上个月的30天
		}
	}
		return CountMonth;
}

int Calen::FindRealDay()
	//除闰年之外，每年365天，为52个星期零一天；闰年则再加一
{
	int CountYear=0;
	int j;
	for(j=1800;j<year;j++)
	{
		if(!IsLeapYear(j)) CountYear++;
		else CountYear+=2;
	}
	return CountYear;
}

void Calen::DisplayMonth()
{
	int count_m=FindStartDay();//月份差
	int count_y=FindRealDay();//年份差
	int count_d=count_m+count_y;//总日期差
	int RealStartDay=count_d+3;//1800年1月1日为星期三
	if(IsLeapYear(year)&&month>2) RealStartDay++;//由于1800年是平年，所以闰年二月之后的月份，再加一
	while(RealStartDay>7)
	{
		RealStartDay=RealStartDay%7;
	}
	cout<<"*********"<<year<<"年"<<month<<"月**********"<<endl<<endl;
	cout<<setw(SpaceSize)<<" SUN"<<setw(SpaceSize)<<" MON"<<setw(SpaceSize)<<" TUE"
		<<setw(SpaceSize)<<" WED"<<setw(SpaceSize)<<" THU"<<" FRI"
		<<setw(SpaceSize)<<" SAT"<<endl;
	SpaceSize=4;
	int TotalDays;
	if((month<8&&month%2==1)||(month>=8&&month%2==0)) TotalDays=31;
	else if(month==2)
	{
		if(IsLeapYear(year)) TotalDays=29;
		else TotalDays=28;
	}
	else TotalDays=30;
	//cout<<TotalDays<<endl;
	//cout<<RealStartDay<<endl;
	int i,j;
	for(i=1;i<=RealStartDay;i++)//输出多余空格
		cout<<setw(SpaceSize)<<" ";
	for(j=1;j<=TotalDays;j++)
	{
		cout<<setw(SpaceSize)<<j;
		if((j+RealStartDay)%7==0)
			cout<<endl;
	}
	cout<<endl;
}

int main()
{
	int year, month;
	cout<<"请输入年份："<<endl;//输入年份
	cin>>year;
	cout<<"请输入月份："<<endl;//输入月份
	cin>>month;
	Calen calendar(year,month);
	if((year<1800)||(month<=0)||month>12)//判断输年月是否合法
		cout<<"输入错误！"<<endl;
	else calendar.DisplayMonth();
	system("pause");
	return 0;
}
