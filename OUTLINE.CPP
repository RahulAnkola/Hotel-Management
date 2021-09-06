void outline()
{
    int lc=2, rc=23,br=2,tr=80;

    for(int a=1; a<50; a++)
  {
    if(rc>1 && lc<24)
    {
      gotoxy(1,lc); cout<<(char)219;
      gotoxy(80,rc); cout<<(char)219;
      lc++; rc--;
    }
    if(br<81 && tr>1)
    {
      gotoxy(br,23); cout<<(char)219;
      gotoxy(tr,2); cout<<(char)219;
      br++; tr--;

      gotoxy(br,23); cout<<(char)219;
      gotoxy(tr,2); cout<<(char)219;
      br++; tr--;
    }
    delay(10);
  }
  }