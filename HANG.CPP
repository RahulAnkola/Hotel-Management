      void hang()
      {

	  clrscr();
	  cout<<"\t\t\tHOW TO PLAY THE GAME\n\n"
	  <<"THIS IS A TWO PLAYER GAME.ONE PLAYER WRITES A WORD"
	  <<" (of max. 18 letters) WITHOUT\nTHE NOTICE OF HIS OPPONENT."
	  <<"EACH LETTER WILL BE THEN REPLACED BY '_'."
	  <<"THE OPPONENTTHEN GUESSES IT BY TYPING ONE LETTER AT A TIME."
	  <<"IF THE WORD CONTAINS THE LETTER\nTHEN THE APPROPRIATE '_'"
	  <<"WILL BE REPLACED BY THE LETTER."
	  <<"OTHERWISE 'H' FROM\n'HANGMAN' WILL BE CUT."
	  <<"PROCEEDING LIKE THIS IF THE OPPONENT GUESSES IT BEFORE\n"
	  <<"THE LAST 'N' FROM 'HANGMAN' IS CUT THEN HE WINS OTHERWISE "
	  <<"HE LOSES\n\n\n\nPRESS ANY KEY TO CONTINUE";
	  getch();
	  HANGMAN:
	  clrscr();
	  char word[20], hangman[8]="HANGMAN", guess[20];
	  for(int i=0;i<20;i++) guess[i]=' ';
	  int y=0,k;
	  cout<<"\t\t\t"<<"HANGMAN"<<endl;
	  cout<<"ENTER THE WORD :: ";
	  gets(word);
	  int l=strlen(word);
	  for(i=0;i<l;i++) guess[i]='_';
	  for(i=0,k=0;i<8; i++, k++)
	  {
	    clrscr();
	    cout<<"\t\t\t"<<"HANGMAN"<<endl;
	    cout<<"\n\n\n";
	    puts(hangman);
	    for(int j=0;j<l;j++) cout<<guess[j];
	    for(j=0;j<7;j++) if(hangman[j]!=' ') goto WIN;
	    cout<<"\nYOU LOSE !!!\n";
	    cout<<"THE WORD WAS "<<word;
	    getch();
	    goto CONTINUE;
	    WIN:
	    if(strcmp(guess,word)==32)
	    {
	      cout<<"\nYOU WIN !!!";
	      getch();
	      goto CONTINUE;
	    }
	    char x=getch();
	    for(j=0; j<l; j++)
	      if(x==word[j]) { guess[j]=x; y++; }
	    if(y==0)  { hangman[k]=' '; cout<<"\a"; }
	    else if(y!=0) { i--; k--; }
	    y=0;
	  }
	  CONTINUE:
	  char a1;
	  clrscr();
	  cout<<"DO YOU WANT TO PLAY ONCE MORE ? (Y/N) ";
	  cin>>a1;
	  if(a1=='y'||a1=='Y') goto HANGMAN;
     }