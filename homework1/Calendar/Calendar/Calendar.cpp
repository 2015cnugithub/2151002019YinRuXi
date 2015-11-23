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
	bool IsLeapYear(int y);//�ж��Ƿ�Ϊ����
	int FindStartDay();//����1800����µ�һ�������ڼ�
	int FindRealDay();//���������µ�һ�������ڼ�
	void DisplayMonth();//��ӡ�����·ݵ�����
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
	for(i=1;i<month;i++)//iΪ1800�����֮ǰ���·���
	{
		if(i==2)
		{
			CountMonth+=28;//1800��Ϊƽ��
		}
		else
		{
			if((i<8&&i%2==1)||(i>=8&&i%2==0)) CountMonth+=31;//����Ϊ����֮ǰ��������ż����ʱ�������ϸ��µ�31�죻����Ϊ����֮�󣬲�����������ʱ�������ϸ��µ�31��
			if((i<8&&i%2==0)||(i>=8&&i%2==1)) CountMonth+=30;//����Ϊ����֮ǰ��������������ʱ�������ϸ��µ�30�죻����Ϊ����֮�󣬲�����ż����ʱ�������ϸ��µ�30��
		}
	}
		return CountMonth;
}

int Calen::FindRealDay()
	//������֮�⣬ÿ��365�죬Ϊ52��������һ�죻�������ټ�һ
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
	int count_m=FindStartDay();//�·ݲ�
	int count_y=FindRealDay();//��ݲ�
	int count_d=count_m+count_y;//�����ڲ�
	int RealStartDay=count_d+3;//1800��1��1��Ϊ������
	if(IsLeapYear(year)&&month>2) RealStartDay++;//����1800����ƽ�꣬�����������֮����·ݣ��ټ�һ
	while(RealStartDay>7)
	{
		RealStartDay=RealStartDay%7;
	}
	cout<<"*********"<<year<<"��"<<month<<"��**********"<<endl<<endl;
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
	for(i=1;i<=RealStartDay;i++)//�������ո�
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
	cout<<"��������ݣ�"<<endl;//�������
	cin>>year;
	cout<<"�������·ݣ�"<<endl;//�����·�
	cin>>month;
	Calen calendar(year,month);
	if((year<1800)||(month<=0)||month>12)//�ж��������Ƿ�Ϸ�
		cout<<"�������"<<endl;
	else calendar.DisplayMonth();
	system("pause");
	return 0;
}
