#include<graphics.h>//引用EasyX图形库
#include <conio.h>
#include <dos.h>
#include <iostream>
#include<stdio.h>
#include<Windows.h>

using namespace std;

enum TYPE {CIRCLE, RECTANGLE, TRIANGLE};

class FigureLink;//超前声明
class Figure
{
	friend class FigureLink;
protected:
	TYPE type;
	int center_x,center_y;
	static Figure *ptr;//指向将要插入链表的图形绘制对象
	Figure *next;//指向链表中的下一个图形绘制对象
public:
	Figure(int x, int y,TYPE tp)
	{
		center_x=x;
		center_y=y;
		type = tp;
		next=0;
	}
	virtual void DrawPic()=0;//图形绘制操作的接口规则
	virtual void Insert()=0;//图形绘制类对象插入链表的借口规则
	void Hide();
	void Move();
	//void operator()(int style, int width, int Incol, int pattern, int fcol);
	//void operator()(int Incol, int pattern, int fcol);//为消隐图形修改相应属性
	//void operator()(int dx, int dy);//为移动图形修改图形位置坐标
};

Figure *Figure::ptr=0;

void Figure::Hide()
{
	unsigned int sc=getcolor();
	setcolor(BLACK);
	DrawPic();
	setcolor(sc);
}

void Figure::Move()
{
	unsigned int sc=getcolor();
	setcolor(BLACK);
	DrawPic();
	setcolor(sc);
	center_x+=1;
	DrawPic();
}

class Circle:public Figure	//圆形类
{
private:
	int radius;//半径
public:
	Circle(int x, int y,int r):Figure(x,y,CIRCLE)
	{
		radius=r;
	}
	void DrawPic();
	void Insert();
};

void Circle::DrawPic()
{
	circle(center_x,center_y,radius);
}

void Circle::Insert()
{
	Figure::ptr=new Circle(center_x,center_y,radius);
}

class Rect:public Figure	//矩形
{
private:
	int width;
	int length;
public:
	Rect(int w, int l, int x, int y):Figure(x,y,RECTANGLE)
	{
		width=w;
		length=l;
	}
	void DrawPic();
	void Insert();
};

void Rect::DrawPic()
{
	rectangle(center_x-width/2,center_y-length/2,center_x+width/2,center_y+length/2);
}

void Rect::Insert()
{
	Figure::ptr=new Rect(width,length,center_x,center_y);
}

class Triangle:public Figure	//三角形
{
private:
	int RightAngleFlag;
	int bottomSide;
	int height;
public:
	Triangle(int b,int h,int flag,int x,int y):Figure(x,y,TRIANGLE)
	{
		bottomSide=b;
		height=h;
		RightAngleFlag=flag;
	}
	void DrawPic();
	void Insert();
};

void Triangle::DrawPic()
{
	if(RightAngleFlag==1)
	{
		int points[8]={center_x-bottomSide/2,center_y+height/2,center_x+bottomSide/2,center_y+height/2,
				center_x+bottomSide/2,center_y-height/2,center_x-bottomSide/2,center_y+height/2};
		drawpoly(4,points);
	}
	else
	{
		int points[8]={center_x-bottomSide/2,center_y+height/2,center_x+bottomSide/2,center_y+height/2,
				center_x-bottomSide/2,center_y-height/2,center_x-bottomSide/2,center_y+height/2};
		drawpoly(4,points);
	}
}

void Triangle::Insert()
{
	Figure::ptr=new Triangle(bottomSide,height,RightAngleFlag,center_x,center_y);
}

class FigureLink
{
protected:
	Figure *head;
public:
	FigureLink(){head=0;}
	~FigureLink(){Empty();}
	void Empty();
	void Insert(Figure *figureNode);
	void Draw();
	void Hide();
	void Move();
};

void FigureLink::Empty()
{
	Figure *current;
	Figure *next;
	current=head;
	while(current)
	{
		next=current->next;
		delete current;
		current=next;
	}
}

void FigureLink::Insert(Figure *figureNode)
{
	figureNode->Insert();
	if(head)
	{
		figureNode->ptr->next=head;
		head=figureNode->ptr;
	}
	else head=figureNode->ptr;
}

void FigureLink::Draw()
{
	Figure *current;
	current=head;
	while(current)
	{
		current->DrawPic();
		current=current->next;
	}
}

void FigureLink::Hide()
{
	Figure *current;
	current=head;
	while(current)
	{
		current->Hide();
		current=current->next;
	}
}

void FigureLink::Move()
{
	Figure *current;
	current=head;
	while(current)
	{
		current->Move();
		current=current->next;
	}
}

class Vehicle
{
protected:
	FigureLink contents;
	int WheelSize;
	int x;
	int y;
public:
	void Draw();
	void Hide();
	void Move();
};

void Vehicle::Draw()
{
	contents.Draw();
}

void Vehicle::Hide()
{
	contents.Hide();
}

void Vehicle::Move()
{
	int i=0;
	int seconds=100;
	int speed=10;
	int choice;
	while(i<500)
	{
		contents.Move();
		Sleep(seconds/speed);
		if(kbhit())
		{
			choice=getch();
			if(choice=='+'||choice=='=') seconds-=10;
			else if(choice=='-'||choice=='_') seconds+=10;
			else if(choice=='E'||choice=='e') return;
			else if(choice=='P'||choice=='p')
			{
				while(1)
				{
					choice=0;
					if(kbhit()) choice=getch();//检查此时是否有键盘输入，若有，返回非零值
					if(choice=='P'||choice=='p') break;//若再次按P，继续运动
				}
			}
		}
		i++;
	}
}

class Car:public Vehicle
{
public:
	Car(int d, int xstart, int ystart);
};

Car::Car(int d,int xstart,int ystart)
{
	WheelSize=d;
	x=xstart;
	y=ystart;
	Figure *f;
	f=new Triangle(d,d,1,x+1.75*d,y-2.5*d);
	contents.Insert(f);
	f=new Rect(3.5*d,d,x+4*d,y-2.5*d);
	contents.Insert(f);
	f=new Triangle(d,d,2,x+6.25*d,y-2.5*d);
	contents.Insert(f);
	f=new Rect(8*d,d,x+4*d,y-1.5*d);
	contents.Insert(f);
	f=new Circle(x+1.75*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+6.25*d,y-0.5*d,0.5*d);
	contents.Insert(f);
}

class Truck:public Vehicle
{
public:
	Truck(int d, int xstart, int ystart);
};

Truck::Truck(int d,int xstart,int ystart)
{
	WheelSize=d;
	x=xstart;
	y=ystart;
	Figure *f;
	f=new Rect(9*d,4*d,x+4.5*d,y-3*d);
	contents.Insert(f);
	f=new Rect(2*d,3*d,x+2+10*d,y-2.5*d);
	contents.Insert(f);
	f=new Circle(x+d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+2.25*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+6.75*d,y-0.5*d,0.5*d);
	contents.Insert(f);
	f=new Circle(x+8*d,y-0.5*d,0.5*d);
	contents.Insert(f);
}

int main()
{
	int gDriver=DETECT,gmode;
	Vehicle *v=0;
	Car car(10,30,350);
	Truck truck(10,30,350);
	int choice;

	initgraph(640,450);
	outtextxy(10,10,"1  Car  2  Truck  3  Exit");
	rectangle(20,30,625,430);
	outtextxy(25,35,"Press <S> key to start moving");
	outtextxy(25,50,"Press <P> key to pause/continue moving");
	outtextxy(25,65,"Press <E> key to end moving");
	outtextxy(25,80,"Press <+> key to speed up");
	outtextxy(25,95,"Press <-> key to speed down");
	line(20,351,625,354);

	choice=getch();
	while(choice!='3')
	{
		if(choice=='1')
		{
			if(v) v->Hide();
			v=&car;
			v->Draw();
		}
		else if(choice=='2')
		{
			if(v) v->Hide();
			v=&truck;
			v->Draw();
		}
		else if(choice=='S'||choice=='s')
		{
			if(v) v->Move();
		}
		choice=getch();
	}
		closegraph();
		return 0;
}