/*#include<iostream.h>
#include<conio.h>
#include<dos.h>
void main() */
void box()
{
  clrscr();
    int lc=2, rc=23,br=2,tr=59;

    for(int a=1; a<30; a++)
  {
    if(rc>1 && lc<24)
    {
      gotoxy(1,lc); cout<<(char)219;
      gotoxy(60,rc); cout<<(char)219;
      lc++; rc--;
    }
    if(br<60 && tr>1)
    {
      gotoxy(br,23); cout<<(char)219;
      gotoxy(tr,2); cout<<(char)219;
      br++; tr--;

      gotoxy(br,23); cout<<(char)219;
      gotoxy(tr,2); cout<<(char)219;
      br++; tr--;
    }
    delay(20);
  }


    gotoxy(64,4);
    cout<<"SCORE: "<<"0";      //71,4  s
    gotoxy(64,7);
    cout<<"HIGH SCORE: ";      //76,7  hs
    gotoxy(64,10);    cout<<"Enter any key ";
    gotoxy(64,11);    cout<<"other than";
    gotoxy(64,12);    cout<<"'w' 'a' 's' 'd'";
    gotoxy(64,13);    cout<<"to restart";

  }