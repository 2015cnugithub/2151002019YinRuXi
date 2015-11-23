#include<iostream>
#include<string>

using namespace std;

class Worker
{
protected:
	string name;
	int age;
	char sex;
	float pay_per_hour;
	float pay;
	int choice;
public:
	Worker();
	Worker(string n, int a, char s, float p)
	{
		name=n;
		age=a;
		sex=s;
		pay_per_hour=p;
	}

	~Worker()
	{
	}

	void Name()
	{
		cout<<this->name<<endl;
	}

	virtual void Compute_pay(double hours)=0;
	friend ostream&operator<<(ostream&out,Worker&Worker);
};

ostream&operator<<(ostream&output,Worker&w)
{
	output<<w.name<<" "<<w.age<<" "<<w.sex<<" "<<w.pay_per_hour<<endl;
	return output;
}

class HourlyWorker:public Worker
{
public:
	HourlyWorker();
	HourlyWorker(string n,int a, char s, float p):Worker(n,a,s,p){}
	void Compute_pay(double hours)
	{
		if(hours<40) pay=pay_per_hour*hours;
		else pay=pay_per_hour*40+1.5*pay_per_hour*(hours-40);
		cout<<pay<<endl;
	}
	friend ostream&operator<<(ostream&output,HourlyWorker&h_w);
};

ostream&operator<<(ostream&output,HourlyWorker&h_w)
{
	output<<h_w.name<<" "<<h_w.sex<<" "<<h_w.pay_per_hour<<" "<<endl;
	return output;
}

class SalariedWorker:public Worker
{
public:
	SalariedWorker();
	SalariedWorker(string n, int a,char s,float p):Worker(n,a,s,p){}
	void Compute_pay(double hours)
	{
		if(hours>=35) pay=pay_per_hour*40;
		else pay=pay_per_hour*hours+0.5*pay_per_hour*(35-hours);
		cout<<pay<<endl;
	}
	friend ostream&operator<<(ostream&output,SalariedWorker&s);
};

ostream&operator<<(ostream&output,SalariedWorker&s_w)
{
	output<<s_w.name<<" "<<s_w.sex<<" "<<s_w.pay_per_hour<<" "<<endl;
	return output;
}

int main()
{
	Worker *workers[5];
	int i;
	string name;
	int age;
	char sex;
	double pay_per_hour;
	char con='y';//控制退出操作
	cout<<"请输入工人信息："<<endl;
	for(i=1;i<=5;i++)
	{
		cin>>name;
		cin>>age;
		cin>>sex;
		cin>>pay_per_hour;

		if(i<4) workers[i]=new HourlyWorker(name,age,sex,pay_per_hour);
		else workers[i]=new SalariedWorker(name,age,sex,pay_per_hour);
	}
	cout<<endl;
	
	cout<<"***全部工人信息如下***"<<endl;
	for(i=1;i<=5;i++)
	{
		cout<<i<<". ";
		workers[i]->Name();
		//cout<<i<<". "<<*workers[i];
	}
	cout<<endl;
	while(con=='y')
	{
		int choice;
		cout<<"请选择一名工人：";
		cin>>choice;
		int hours;
		cout<<"请输入工作时长：";
		cin>>hours;
		cout<<"该名工人周薪：";
		if(choice<=3)
			workers[choice]->Compute_pay(hours);
		else workers[choice]->Compute_pay(hours);
		cout<<"是否继续计算？ (y/n)：";
		cin>>con;
		cout<<endl;
	}
	system("pause");
	return 0;
}