#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>
#include<stdlib.h>
#include"c:\\tc\\bin\\hang.cpp"
#include"c:\\tc\\bin\\newsnake.cpp"
#include"c:\\tc\\bin\\outline.cpp"


   void displayall();
   void displaycheck();
   void displayrooms();
   void empty();
   int giveroomtype();
   int assignroom();

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

   void frontpage()
   {
    clrscr();
    int c;
    randomize();
    for (int x=20; x<=63; x++)
     {
      LOOP:
      c=random(100);
      if ((c>=10 && c<=20) || (c>=90 && c<=100))
       {
	 gotoxy(x,18);
	 delay(c);
	 cout<<(char)219;
       }
      else
       goto LOOP;

     }
    gotoxy(20,22);
    cout<<"          Press a key to continue ";
    getch();

   }


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////
  ///////CLASS
  //////////////////////////////////////////////////////////////

   class hotel
   {
     char name[20], phone[11],roomtype[30];
     long charge;
     int nights, roomtypeno;

     roomcharge()
     {


     switch(roomtypeno)
       {
	 case 1: strcpy(roomtype,"Royal Suite");
		 charge+=30000; break;
	 case 2: strcpy(roomtype,"Super Deluxe");
		 charge+=20000; break;
	 case 3: strcpy(roomtype,"Deluxe");
		 charge+=10000; break;
	 case 4: strcpy(roomtype,"Double Bed");
		 charge+=5000;  break;
	 case 5: strcpy(roomtype,"Single Bed");
		 charge+=2500;  break;
	 default: charge+=0; break;
       }
       charge*=nights;
      return 0;
     }

    public:


    int roomno;

     hotel() //constructor
     {
       charge=0;
     }

    void foodbill(int bill)
    {
      charge+=bill;
    }
    void getdata()
     {
	gotoxy(25,7); cout<<"Enter name: "; gets(name);
	gotoxy(25,8); cout<<"Enter phone number: "; cin>>phone;
	gotoxy(25,9); cout<<"Enter the number of nights: "; cin>>nights;
	      roomtypeno=giveroomtype();
	      roomno=assignroom();
	      charge=0;
	      roomcharge();
     }

    void display()
     {

       gotoxy(25,7); cout<<"Name: "<<name;
       gotoxy(25,8); cout<<"Phone number: "<<phone;
       gotoxy(25,9); cout<<"No.of nights staying: "<<nights;
       gotoxy(25,10); cout<<"Charge: "<<charge;
       gotoxy(25,11); cout<<"Room number: "<<roomno;
       getch();
     }

   char *getname()
   {
     return name;
   }

   int getroomno()
   {
    return roomno;
   }
 };
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


   class room
   {
     public:
     char array[100];

   };
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


   int giveroomtype()
   {

     clrscr();

     int rmtype;
     cout<<"\n\n\n\t\t\tSelect your room type:";
     cout<<"\n\n\t\t\tROOM TYPES  "<<"\t"
	    <<"CODES"<<"\t"<<"CHARGE PER DAY\n"
	    <<"\t\t\tROYAL SUITE "<<"\t"<<"1.   "<<"\t"<<"Rs 30,000\n"
	    <<"\t\t\tSUPER DELUXE"<<"\t"<<"2.   "<<"\t"<<"Rs 20,000\n"
	    <<"\t\t\tDELUXE      "<<"\t"<<"3.   "<<"\t"<<"Rs 10,000\n"
	    <<"\t\t\tDOUBLE BED  "<<"\t"<<"4.   "<<"\t"<<"Rs  5,000\n"
	    <<"\t\t\tSINGLE BED  "<<"\t"<<"5.   "<<"\t"<<"Rs  2,500\n";
	    outline();
      //cout<<"\t\t\t";
      gotoxy(25,13); cout<<"Enter code: "; cin>>rmtype;
      return rmtype;
   }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

   int assignroom()
   {
     room r;
     int c=0,roomnum;
     fstream aroom("roomno.dat", ios::in|ios::binary);
     aroom.read((char*)&r, sizeof(r));

       while(r.array[c]!='e') c++;
       r.array[c]='o';
     aroom.close();


    fstream asroom("roomno.dat", ios::out|ios::binary);
     asroom.write((char*)&r, sizeof(r));
     asroom.close();
     roomnum=c+100;
     gotoxy(25,16); cout<<"Your room number : "<<roomnum;
     getch();

     return roomnum;
   }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

   void booking()
   {
      textcolor(7);
      clrscr();
       outline();
      fstream book("booking.dat",ios::app|ios::binary);
      hotel b;

       gotoxy(30,5);cout<<"ENTER YOUR DETAILS"<<endl<<endl;
      b.getdata();
      book.write((char*)&b, sizeof(b));
      book.close();

   }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

   void checkin()
   {

      clrscr();
      outline();
      char newname[20];
      int con=0;
	   hotel ci,co;

      gotoxy(25,4); cout<<"Enter name to confirm: "; gets(newname);
      fstream booki("booking.dat", ios::in|ios::binary);
      fstream check("checkin.dat",ios::app|ios::binary);
      while(!booki.eof())
      {
	booki.read((char*)&ci, sizeof(ci));
	if(booki.eof()) break;
	 if(strcmpi(newname,ci.getname())==0)
	   {
	      gotoxy(25,5); cout<<"Booking confirmed!";
	     check.write((char*)&ci, sizeof(ci));
	     ci.display();
	/////////////////////////////////////////////////////////
	     fstream book("booking.dat", ios::in|ios::binary);
	     fstream altbook("altbooking.dat", ios::out|ios::binary);
       while(!book.eof())
       {
	 book.read((char*)&co, sizeof(co));
	    if(book.eof()) break;
	    if(strcmpi(newname,co.getname())!=0)
	      altbook.write((char*)&co, sizeof(co));


       }
       book.close();
       altbook.close();

       remove("booking.dat");
       rename("altbooking.dat","booking.dat");

	     con++;
	   }
      }
	 if(con==0)
	   {
	    cout<<"\n\t\t\tNo booking!";
	    getch();
	   }
      booki.close();
      check.close();
   }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

  void checkout()
  {
     clrscr();
	 outline();	  //roomno - 100=c
     hotel co;
     room r;
     char *newname;
     int counter=0;

      gotoxy(25,4);cout<<"Enter name to check out: ";
     gets(newname);

     fstream book("checkin.dat", ios::in|ios::binary);

     fstream altbook("altbooking.dat", ios::out|ios::binary);

       while(!book.eof())
       {
	 if(book.eof()) break;

	   book.read((char*)&co, sizeof(co));
	     if(book.eof()) break;

	    if(strcmpi(newname,co.getname())!=0)
	      altbook.write((char*)&co, sizeof(co));

	      else
	     { counter++;
	       fstream aroom("roomno.dat",ios::in|ios::binary);
	       aroom.read((char*)&r, sizeof(r));
	       r.array[co.roomno-100]='e';
	       aroom.close();

	       fstream asroom("roomno.dat",ios::out|ios::binary);
	       asroom.write((char*)&r, sizeof(r));
	       asroom.close();
	       co.display();
	       gotoxy(25,13); cout<<"SUCCESSFULY CHECKED OUT !! ";
	       break;
	     }
       }//while
       if(counter==0)
	 gotoxy(25,6); cout<<"You need to checkin first!";

       book.close();
       altbook.close();

       remove("checkin.dat");
       rename("altbooking.dat","checkin.dat");
       //co.display();

       getch();
  }

  void restaurant()
  {
	 textcolor(10);
 clrscr();
 int  vegprice[24]={260,250,270,280,260,250,240,250,230,220,200,240,250,240,
		    220,260,260,200,250,240,230,220,230,210};

 char veg[113][30]={"SHAHI PANEER","KADAI PANEER","CHEESE KORMA",
	"MALAI KOFTA","MATAR PANEER","PALAK PANEER","PANEER TIKKA",
	"MIX VEG.","ALOO GOBI","ALOO JEERA","CHANA MASALA","MATAR MUSHROOM",
	"RAJMA MAKHANI","DAL MAKHANI","MIXED RAITA","BUNDI RAITA",
	"PINEAPPLE RAITA","SALAD(GREEN)","DUM ALOO","MUSHROOM PANEER",
	"PANEER PULAO","VEG.PULAO","JEERA RICE","STEAMED RICE"};

 int nonvegprice[24]={260,250,270,280,260,250,240,250,230,220,200,240,250,
		      240,220,260,260,200,250,240,230,220,230,210};

 char nonveg[113][30]={"MUTTON MASALA","MUTTON MUGHLAI","MUTTON KORMA",
	"MUTTON DO PYAZA","MUTTON SAGH","MUTTON DAHI","MUTTON ROGAN JOSH",
	"MUTTON CURRY","KADAI MUTTON","KEEMA LEVER","KEEMA EGG","BRAIN CURRY",
	"EGG CURRY","BUTTER CHICKEN","KADAI CHICKEN","BUTTER CHICKEN(BL)",
	"CHICKEN MUGHLAI","CHICKEN MASALA","CHICKEN SAGH","CHICKEN DAHI",
	"CHICKEN KORMA","CHICKEN DO PYAZA","FISH CURRY","CHICKEN CURRY"};

 int dessertprice[20]={90,130,160,100,100,100,100,200,300,50,100,100,100,100,
			100,100,100,100,100,100};

 char dessert[50][30]={"TEA","COFFEE","COLD COFFEE","PINEAPPLE ICECREAM",
	"STRAWBERRY ICECREAM","CHOCOLATE ICECREAM","BLACK FOREST ICECREAM",
	"DOUBLE STORIED ICECREAM","TRIPLE STORIED ICECREAM","SOFT CONE",
	"VANILLA ICECREAM","STRAWBERRY ICECREAM","CHOCOLATE ICECREAM",
	"CHOCO CHIPS ICECREAM","MANGO ICECREAM","TUTTI FRUITY ICECREAM",
	"LICHI ICECREAM","PISTA BADAM ICECREAM","CHOCO DIP ICECREAM",
	"CHOCOLATE LICHI ICECREAM"};

 int breadprice[15]={80,70,90,100,130,150,80,90,100,120,80,130,90,100,90};

 char bread[50][30]={"RUMALI ROTI","ROTI","NAN","ALOO NAN","PANEER NAN",
	"KEEMA NAN","PARANTHA","ALOO PARANTHA","PANEER PARANTHA",
	"PUDINA PARANTHA","BUTTER NAN","LACHCHA PARANTHA","MISSI ROTI",
	"KHASTA ROTI"};

char ch,ext;
	int bill=0,n;
	mainmenu:
	clrscr();

	cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t1) Veg"
	    <<"\n\t\t\t\t2) Nonveg"
	    <<"\n\t\t\t\t3) Bread "
	    <<"\n\t\t\t\t4) Dessert"
	    <<"\n\t\t\t\t5) Exit";
	    outline();
	/////////////////////////////////
	/////////////////////////////////

	ch=getch();
	clrscr();
	switch(ch)
	{

	  case '1':  vegmen:
		     clrscr();
		     for (int c=0; c<=23; c++)
			{
			  cout<<c+1<<"   "<<veg[c];
			  gotoxy(37,c+1);
			  cout<<vegprice[c]<<endl;
			}
		       gotoxy(60,25);
		       cout<<"PRESS 0 TO GO BACK";
		       ext=getch();
		       if (ext=='0')
			  goto mainmenu;
		       clrscr();
		       cout<<"Enter number to order: ";
		       cin>>n;
		       if( n>=1 && n<=24)
		       {
			  bill+=vegprice[n-1];
			  cout<<" Your order has been confirmed ";
			  getch();
			  goto mainmenu;
		       }

		       if (n==0)
			  break;

		       else
		       {
			  cout<<" Wrong choice try again ";
			  getch();
			  clrscr();
			  goto vegmen;
		       }

	  case '2':  nonvegmen:
		     clrscr();
		     for (c=0; c<=23; c++)
		       {
			  cout<<c+1<<"   "<<nonveg[c];
			  gotoxy(47,c+1);
			  cout<<nonvegprice[c]<<endl;
		       }
		      gotoxy(60,25);
		      cout<<"PRESS 0 TO GO BACK";
		      ext=getch();
		       if (ext=='0')
			   goto mainmenu;
		      clrscr();
		      cout<<"Enter number to order: ";
		      cin>>n;
		      if( n>=1 && n<=24)
		       {
			  bill+=nonvegprice[n-1];
			  cout<<" Your order has been confirmed ";
			  getch();
			  goto mainmenu;
		       }

		       if (n==0)
			  break;

		       else
		       {
			  cout<<" Wrong choice try again ";
			  getch();
			  clrscr();
			  goto nonvegmen;
		       }

	  case '3':  breadmen:
		     clrscr();
		     for (c=0; c<=13; c++)
		      {
			cout<<c+1<<"   "<<bread[c];
			gotoxy(47,c+1);
			cout<<breadprice[c]<<endl;
		      }
		      gotoxy(60,25);
		      cout<<"PRESS 0 TO GO BACK";
		      ext=getch();
		       if (ext=='0')
			  goto mainmenu;
		      clrscr();
		      cout<<"Enter number to order: ";
		      cin>>n;
		      if( n>=1 && n<=14)
		       {
			  bill+=breadprice[n-1];
			  cout<<" Your order has been confirmed ";
			  getch();
			  goto mainmenu;
		       }

		       if (n==0)
			  break;

		       else
		       {
			  cout<<" Wrong choice try again ";
			  getch();
			  clrscr();
			  goto breadmen;
		       }

	  case '4':  dessertmen:
		     clrscr();
		     for (c=0; c<=19; c++)
		     {
			cout<<c+1<<"   "<<dessert[c];
			gotoxy(47,c+1);
			cout<<dessertprice[c]<<endl;
		      }
		      gotoxy(60,25);
		      cout<<"PRESS 0 TO GO BACK";
		      ext=getch();
		       if (ext=='0')
			  goto mainmenu;
		      clrscr();
		      cout<<"Enter number to order: ";
		      cin>>n;
		      if( n>=1 && n<=20)                   		       {
			  bill+=dessertprice[n-1];
			  cout<<" Your order has been confirmed ";
			  getch();
			  goto mainmenu;
		       }

		       if (n==0)
			  break;

		       else
		       {
			  cout<<" Wrong choice try again ";
			  getch();
			  clrscr();
			  goto dessertmen;
		       }
	  case '5': break;

	  default: cout<<"Wrong Choice, Enter again";
		   getch();
		   goto mainmenu;

	}//switch

	  char yn,newname[40];
	  int counter=0;
	  class hotel h;
	  retryfood:
	  counter=0;
	  clrscr();
	  cout<<"Are you staying in the hotel? (Y/N): ";
	  cin>>yn;

	  if(yn=='y' || yn=='Y')
	  {
	    cout<<"Enter your booking name: ";
	    gets(newname);
	    fstream abc("checkin.dat", ios::in|ios::out|ios::binary);
	    while(!abc.eof())
	    {
	      abc.read((char*)&h, sizeof(h));
	      if(abc.eof()) break;
	      if(strcmpi(newname,h.getname())==0)
	       {
		 counter++;
		 h.foodbill(bill);
		 //h.display();

	       abc.seekg(abc.tellg()-sizeof(h));
	       abc.write((char*)&h, sizeof(h));
	       abc.close();

	       cout<<endl<<bill<<" Rs has been added to your hotel bill! Thank you!";
	       getch();
	       }//
	    }//while
	       if (counter==0)
		 {
		   cout<<"Name entered was incorrect! Enter again!";
		   getch();
		   goto retryfood;
		  }

	  }//if yn y

	  else if(yn=='n' || yn=='N')
	  {
	     cout<<"Pay "<<bill<<" Rs and have a nice day!";
	     getch();
	  }
}


  void bar()
  {
    char bottle[32][20]	={"RED LABEL","BLACK LABEL","GOLD LABEL",
	"SIGNATURE","SEAGRAMS","8 PM","CHIVAS REGAL","MC DOWELL","BLACK DOG",
	"BAGPIPER","PETER SCOT","JOHNY WALKER","KINGFISHER","FOSTERS",
	"BUD WEISER","HAYWARD 2000","HAYWARD 5000","VORIAN 6000","RED WINE",
	"WHITE WINE","PORT WINE","IRISH CREAM","OLD MONK","BACARDI",
	"BLUE RIBAND","SMIRNOFF","VO DE FRANCE","LEMAR DE VONCON",
	"VINTAGE BUBBLY","KINGFISHER","BAGPIPER","EVIAN BRAND"};

    int bottleprice[32]={1500,4000,6000,3000,2500,2000,5000,1500,4000,1500,
	      2000,6000,1000,1500,1000,1000,1500,1500,500,550,600,4000,1500,
	      1000,1000,1500,5000,5500,8000,150,150,80};

		    char yn,newname[40];
		    class hotel h;

		    int n, bill=0, counter=0;
		    char ext;
		    barmenu:
		    clrscr();
		     for (int c=0; c<=22; c++)
		     {
			cout<<c+1<<"   "<<bottle[c];
			gotoxy(47,c+1);
			cout<<bottleprice[c]<<endl;
		      }
		      gotoxy(60,25);
		      cout<<"PRESS 0 TO GO BACK";
		      ext=getch();

		       if (ext=='0')
			   goto EXTI;

		      clrscr();
		      cout<<"Enter number to order: ";
		      cin>>n;
		      if( n>=1 && n<=23)
		       {
			  bill+=bottleprice[n-1];
			  cout<<"Your order has been confirmed ";
			  getch();
			  //goto barmenu;
			}

			else
			{
			  cout<<" Wrong choice try again ";
			  getch();
			  clrscr();
			  goto barmenu;
		       }
			retrybar:
	   counter=0;
	  clrscr();
	  cout<<"\nAre you staying in the hotel? (Y/N): ";
	  cin>>yn;

	  if(yn=='y' || yn=='Y')
	  {
	    cout<<"Enter your booking name: ";
	    gets(newname);
	    fstream abc("checkin.dat", ios::in|ios::out|ios::binary);
	    while(!abc.eof())
	    {
	      abc.read((char*)&h, sizeof(h));
	      if(abc.eof()) break;
	      if(strcmpi(newname,h.getname())==0)
	       {
		 counter++;
		 h.foodbill(bill);
		 h.display();

	       abc.seekg(abc.tellg()-sizeof(h));
	       abc.write((char*)&h, sizeof(h));
	       abc.close();

	       cout<<endl<<bill<<"Rs has been added to your hotel bill! Thank you!";
	       getch();
	       }//

	    }//while
	      if (counter==0)
		 {
		   cout<<"Name entered was incorrect! Enter again!";
		   getch();
		   goto retrybar;
		  }
	  }//if yn y

	  else if(yn=='n' || yn=='N')
	  {
	     cout<<"Pay "<<bill<<" Rs and have a nice day!";
	     getch();
	  }
      EXTI:
  }

  void games()
  {
    game:
    textcolor(YELLOW);
    clrscr();
    char k;
    cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t1) Hangman"
	<<"\n\t\t\t\t2) Snake"
	<<"\n\t\t\t\t3) Exit";
    outline();
    k=getch();


    switch(k)
    {
      case '1': hang(); break;
      case '2': snake(); break;
      case '3': break;
      default: goto game;
    }

  }//end of games


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void main()

{
  //empty();
  // frontpage();

   abc:
   textcolor(CYAN);
   clrscr();

   char choice;

   cout<<"\n\n\n\n\n\n\n\n\t\t\t\t1) Booking"
       <<"\n\t\t\t\t2) Check in"
       <<"\n\t\t\t\t3) Check out"
       <<"\n\t\t\t\t4) Restaurant"
       <<"\n\t\t\t\t5) Bar"
       <<"\n\t\t\t\t6) Games"
       <<"\n\t\t\t\t7) Exit ";
   outline();
   choice=getch();

   switch(choice)
   {
     case '1':  booking();  goto abc;
     case '2':  checkin();  goto abc;
     case '3':  checkout(); goto abc;
     case '4':  restaurant(); goto abc;
     case '5':  bar(); goto abc;
     case '6':  games(); goto abc;
     case '7':  exit(0);
     case 'd':  displayall(); goto abc;
     case 'c':  displaycheck(); goto abc;
     case 'r':  displayrooms(); goto abc;

     default: goto abc;
   }
}
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
//QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

  void displayall()
  {
    clrscr();
    hotel s;
    fstream book("booking.dat",ios::in|ios::binary);
    while(!book.eof())
    {
      book.read((char*)&s, sizeof(s));
      if(book.eof()) break;
      clrscr();
      s.display();
      cout<<endl;
     }
     book.close();
  }
  void displaycheck()
  {

    clrscr();
    hotel s;
    fstream book("checkin.dat",ios::in|ios::binary);
    while(!book.eof())
    {
      book.read((char*)&s, sizeof(s));
      if(book.eof()) break;
      s.display();
      cout<<endl;
     }
     getch();
     book.close();
  }

  void displayrooms()
  {
    clrscr();
    room r;
    fstream aroom("roomno.dat",ios::in|ios::binary);
      aroom.read((char*)&r, sizeof(r));
      for(int x=0; x<100; x++)
	cout<<x<<"."<<r.array[x]<<"      ";

    aroom.close();
 getch();
   }

   void empty()
   {
     room r;
   int c=0;
   fstream check("checkin.dat", ios::out|ios::binary);
   check.close();
   fstream aroom("roomno.dat", ios::out|ios::binary);
   aroom.write((char*)&r, sizeof(r));
   fstream room("booking.dat", ios::out|ios::binary);
   aroom.close();

   fstream oom("roomno.dat", ios::in|ios::binary);
     oom.read((char*)&r, sizeof(r));
	while(c<100) r.array[c++]='e';
	r.array[100]=NULL;

     oom.close();

   fstream om("roomno.dat", ios::out|ios::binary);
     om.write((char*)&r, sizeof(r));
      om.close();
  }


