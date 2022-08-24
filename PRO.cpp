
//*********************************************************
// START OF PROJECT
//*********************************************************
//*********************************************************
// HEADER FILE USED IN PROJECT
//*********************************************************
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
using namespace std;
//*********************************************************
// CLASS USED IN PROJECT
//*********************************************************
class hotel
{
	int day;
	int total;
	int pay;
	int room_no;
	char name[30];
	char address[50];
	char phone[10];
	int dd1,dd2,mm1,mm2,yy1,yy2,dd,mm,yy;
	char cc,ec;
	char cd;
	public:
	void bill();
	void checkin();
	void checkout();
	void main_menu();		//to dispay the main menu
	void add();			//to book a room
	void display(); 		//to display the customer record
	void rooms();			//to display alloted rooms
	void edit();			//to edit the customer record
	int check(int);			//to check room status
	void modify(int);		//to modify the record
	void delete_rec(int);		//to delete the record
};
//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT
//*********************************************************
void hotel::checkin()
{
	struct date d;
	getdate(&d);
	dd1=d.da_day;
	mm1=d.da_mon;
	yy1=d.da_year;
	cout<<"\nCHECK IN DATE(DD/MM/YYYY):"<<dd1<<"/"<<mm1<<"/"<<yy1;
}
void hotel::checkout()
{
	struct date d;
	getdate(&d);
	dd2=d.da_day;
	mm2=d.da_mon;
	yy2=d.da_year;
	cout<<"\nCHECK OUT DATE(DD/MM/YYYY):"<<dd2<<"/"<<mm2<<"/"<<yy2;
	bill();
}
void hotel::bill()
{
  int d1,m1,y1,d2,m2,y2;
  d1=dd1;
  m1=mm1;
  y1=yy1;
  d2=dd2;
  m2=mm2;
  y2=yy2;
  while(y2!=y1)
	{
	m2=m2+12;
	y2--;
	}
  while(m2!=0)
	{
	d2=d2+30;
	m2--;
	}
  while(m1!=0)
	{
	d1=d1+30;
	m1--;
	}
 day=d2-d1;
 cout<<"ENTER FEE PER DAY:";
 cin>>pay;
 total=day*pay;
 cout<<"TOTAL FEE IS:"<<total;
 if(dd2>30)
  {dd2=dd2-30;
  }
 if(mm2>12)
  {mm2=mm2-12;
  yy2++;
  }
 else
 {
 day=0;
 pay=0;
 total=0;
 }
}
//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT  TO ADD //RECORD
//*********************************************************
void hotel::add()
{
	clrscr();
	int r,flag;
	ofstream fout("Record.dat",ios::app);

	cout<<"\n ENTER CUSTOMER DETAILS";
	cout<<"\n ----------------------";
	cout<<"\n\n ROOM NO: ";
	cin>>r;
	flag=check(r);

	if(flag)
		cout<<"\n SORRY..!!!ROOM IS ALREADY BOOKED";

	else
	{
		room_no=r;
		cout<<" NAME: ";
		gets(name);
		cout<<" ADDRESS: ";
		gets(address);
		cout<<" PHONE NO: ";
		gets(phone);
		cout<<"DO YOU WANT TO CHECK IN(Y/N):";
		cin>>cc;
		if(cc=='Y')
		{
		checkin();
		}
		dd2=0; mm2=0; yy2=0;
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n ROOM IS BOOKED...!!!";
	}

	cout<<"\n PRESS ANY KEY TO CONTINUE.....!!";
	getch();
	fout.close();
}
//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT TO  DISPLAY //RECORD
//*********************************************************
void hotel::display()
{
	clrscr();
	ifstream fin("Record.dat",ios::in);
	int r,flag;
	cout<<"\n ENTER ROOM NO: ";
	cin>>r;

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			clrscr();
			cout<<"\n CUSTOMER DETAILS";
			cout<<"\n ----------------";
			cout<<"\n\nROOM NO: "<<room_no;
			cout<<"\nNAME: "<<name;
			cout<<"\nADDRESS: "<<address;
			cout<<"\nPHONE NO: "<<phone;
			cout<<"\nCHECKIN DATE:"<<dd1<<"/"<<mm1<<"/"<<yy1;
			cout<<"\nCHECK OUT DATE:"<<dd2<<"/"<<mm2<<"/"<<yy2;
			cout<<"\nTOTAL DAY:"<<day;
			cout<<"\nTOTAL PAY:"<<total;
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n SORRY ROOM NO NOT FOUND OR VACENT....!!";

	cout<<"\n\n PRESS ANY KEY TO CONTINUE....!!";
	getch();
	fin.close();

}
//*********************************************************
// FUNCTION  OF CLASS USED IN PROJECT TO SHOW ALLOTED ROOM
//*********************************************************

void hotel::rooms()
{
	clrscr();
	ifstream fin("Record.dat",ios::in);
	cout<<"\n\t\t\t    LIST OF ROOM ALLOTED";
	cout<<"\n\t\t\t    ----------------------";
	cout<<"\n\n ROOM NO.\tNAME\t\tADDRESS\t  PHONE NO.    CHECKIN    CHECKOUT\n";

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		cout<<"\n\n "<<room_no<<"\t"<<name;
		cout<<"\t"<<address<<"  "<<phone<<"   "<<dd1<<"/"<<mm1<<"/"<<yy1<<"  "<<dd2<<"/"<<mm2<<"/"<<yy2;
	}
	cout<<"\n\n\n\t\t\tPRESS ANY KEY TO CONTINUE.....!!";
	getch();
	fin.close();
}
//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT TO EDIT RECORD
//*********************************************************
void hotel::edit()
{
	clrscr();
	int choice,r;

	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.MODIFY CUSTOMER RECORD";
	cout<<"\n 2.DELETE CUSTOMER RECORD";

	cout<<"\n ENTER YOUR CHOICE: ";
	cin>>choice;
	clrscr();
	cout<<"\n ENTER ROOM NO: " ;
	cin>>r;

	switch(choice)
	{
		case 1:	modify(r);
			break;
		case 2:	delete_rec(r);
			break;
		default: cout<<"\n WRONG CHOICE.....!!";
	}
	cout<<"\n PRESS ANY KEY TO CONTINUE....!!!";
	getch();
}

//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT TO CHECK
//*********************************************************
int hotel::check(int r)
{
	int flag=0;
	ifstream fin("Record.dat",ios::in);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			flag=1;
			break;
		}
	}

	fin.close();
	return(flag);
}
//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT TO MODIFY
//*********************************************************

void hotel::modify(int r)
{
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);
	while(!file.eof())
	{
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n ENTER NEW DETAILS";
			cout<<"\n -----------------";
			cout<<"\n NAME: ";
			gets(name);
			cout<<" ADDRESS: ";
			gets(address);
			cout<<" PHONE NO: ";
			gets(phone);
			cout<<"DO YOU WANT TO CHECK OUT(Y/N):";
			cin>>ec;
			if(ec=='Y')
			{
			checkout();
			}
			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n RECORD IS MODIFIED....!!";
			flag=1;
			break;
			}
	}

	if(flag==0)
		cout<<"\n SORRY ROOM NO IS NOT FOUND OR VACENT...!!";
	file.close();
}
//*********************************************************
// FUNCTION DEFINITIONS OF CLASS USED IN PROJECT TO DELETE
//*********************************************************
void hotel::delete_rec(int r)
{
	int flag=0;
	char ch;
	ifstream fin("Record.dat",ios::in);
	ofstream fout("temp.dat",ios::out);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r)
		{
			cout<<"\n NAME: "<<name;
			cout<<"\n ADDRESS: "<<address;
			cout<<"\n PHONE NO:"<<phone;
			cout<<"\n\n DO YOU WANT TO DELETE THIS RECORD(Y/N): ";
			cin>>ch;

			if(ch=='n')
				fout.write((char*)this,sizeof(hotel));
			flag=1;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}

	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n SORRY ROOM NO IS NOT FOUND OR VACENT...!!";
	else
	{
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
}


//*********************************************************
// MAIN_MENU FUNCTION OF CLASS USED IN PROJECT
//*********************************************************
void hotel::main_menu()
{
	int choice;
	while(choice!=5)
	{
		clrscr();
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\n\n";
		cout<<"\n\t\t\t    *********************";
		cout<<"\n\t\t\t    * 1.BOOK A ROOM     *";
		cout<<"\n\t\t\t    * 2.CUSTOMER RECORD *";
		cout<<"\n\t\t\t    * 3.ROOMS ALLOTED   *";
		cout<<"\n\t\t\t    * 4.EDIT RECORD     *";
		cout<<"\n\t\t\t    * 5.EXIT            *";
		cout<<"\n\t\t\t    *********************";
		cout<<"\n\n\t\t\tENTER YOUR CHOICE: ";
		cin>>choice;

		switch(choice)
		{
			case 1:	add();
				break;
			case 2: display();
				break;
			case 3: rooms();
				break;
			case 4:	edit();
				break;
			case 5: break;
			default:
				{
				cout<<"\n\n\t\t\tWRONG CHOICE.....!!!";
				cout<<"\n\t\t\tPRESS ANY KEY TO CONTINUE....!!";
					getch();
				}
		}
	}
}

//*********************************************************
// MAIN FUNCTION USED IN PROJECT
//*********************************************************
void main()
{
	hotel h;
	clrscr();
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t*      COMPUTER PROJECT    *";
	cout<<"\n\t\t\t*             ON           *";
	cout<<"\n\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout<<"\n\t\t\t*          WITH C++        *";
	cout<<"\n\t\t\t****************************";
	cout<<"\n\n\n";
	cout<<"\n\t\t\t\b********************************";
	cout<<"\n\t\t\t\b********************************";
	cout<<"\n\t\t\t\b**                       :MADE BY:                   **";
	cout<<"\n\t\t\t\b**          TIRTHANKAR KABIRAJ       **";
	cout<<"\n\t\t\t\b********************************";
	cout<<"\n\t\t\t\b********************************";
	cout<<"\n\n\n\n\n\n\n\t\t\tPRESS ANY KEY TO CONTINUE....!!";
	getch();
	h.main_menu();
}

//*********************************************************
// END OF PROJECT
//********************************************************


