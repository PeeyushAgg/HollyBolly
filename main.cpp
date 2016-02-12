



	/*******************************************************************

	 Header files used in Project

	********************************************************************/

	#include<iostream.h>
	#include<conio.h>
	#include<fstream.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<ctype.h>
	#include<string.h>
	#include<time.h>
	#include<graphics.h>
	#include<process.h>

	const int s1=5;    //Default size of p1(no. of players)

	/*******************************************************************

	 A Structure named play_data which contains the information
	 of a specific player. Information stored is :
	 1.Name (in the char array `user_name')
	 2.Score (in the variable `score')
	 3.Time i.e. Total time taken by player (in the variable `time')

	********************************************************************/

	struct play_data
		{
		 char user_name[20];
		 int score;
		 float time;
		};

	// start_graph()  initiates the GRAPHICS CONSOLE
	void start_graph();

	// score_read reads the PLAYER INFO from binary file "SCORE.DAT"
	void score_read();

	// rules() displays the rules of the game
	void rules();

	/*******************************************************************

	   A class `game' which contains a structure play_data and
	   various user-defined functions to execute the game.
	   Uses of various functions used are :

	   1. void initiate(void) - initiates the game
	   2. void get_user(play_data,int) - inputs the name of players
	   3. void getmovie(int,int,play_data) - inputs the movie name
	   4. void solve(char,play_data,int) - initiates the solving for
					       player
	   5. void score_sort(play_data,play_data,int) - sorts the data
							 of p1
	   6. void score_write(play_data,int) - writes data to `SCORE.DAT'
	   7. void score_display(play_data,int) - displays score during
						  gameplay
	   8. ~game() - Regular Destructor

	*******************************************************************/

	class game{

	private :
		play_data p1[s1];    // An array storing INFO of all the
				     //	players
	public :

	void initiate(void);
	void get_user(play_data p1[],int m);
	void getmovie(int i,int q,play_data p1[]);
	void solve(char a[],play_data p1[],int player_num);
	void score_sort(play_data p1[],play_data p2[],int m);
	void score_write(play_data p[],int m);
	void score_display(play_data p2[],int m);
	~game()
	{}
	};


	void main()
	{
		char a=16; /* variable storing ASCII value of arrow used
			      in main console for navigation */

		int y=128; /* variable for alignment of arrow in main
			      console for navigation */

	shuffle1:

	start_graph();   // GRAPHICS CONSOLE initiated
	shuffle2:

	cleardevice();   // GRAPHICS CONSOLE cleared
	setbkcolor(1);

	setlinestyle(0,1,3);
	rectangle(40,100,580,400);

	settextstyle(0,0,2);
	outtextxy(180,y,&a);

	settextstyle(5,0,5);
	outtextxy(50,30,"HOLLYWOOD BOLLYWOOD");

	settextstyle(1,0,2);
	outtextxy(270,120,"PLAY");
	outtextxy(215,170,"PREVIOUS SCORE");
	outtextxy(262,220,"RULES");
	outtextxy(270,270,"EXIT");

	int arrow;    /* variable storing position of the arrow used in
			  main console for navigation */

	while(1)
	   {
	    arrow=getch();
	    if(arrow==0)
		{
		 arrow=getch();

		 if(arrow==80)
		     {
		      if(y-8<270)
			y+=50;
		      goto shuffle2;
		     }
		 else if(arrow==72)
		     {
			if(y-8>120)
			 y-=50;
			 goto shuffle2 ;
		     }
		 else
		    continue;
		  }

	else if (arrow=='\r')
	  {
	   switch (y-8)
		{
		 case 120  :{
			    game w;
			    w.initiate();   // initiates the game
			    }
			    goto shuffle1;
		 case 170 : score_read();   // displays the score
			    goto shuffle1;

		 case 220 : rules();        // displays the rules
			    goto shuffle1;

		 case 270 : exit(0);        // exits the game

		 default : continue;

		}
	  }
	 else
	 continue;
	}
	}


	void game:: initiate(void)     // initiates the game
		{
		closegraph();
		play_data p2[s1];  // array of structure plat_data declared

		for (int i=0;i<s1;i++)     // variables initialized
			{
			 p1[i].score =0;
			 p1[i].time =0.0;
			}
		int m,q;     /* m stores the no. of players
				q is a dummy variable for game play
				representing the next player in sequence */

		textcolor(WHITE);
		gotoxy(2,2);
		cprintf("%s","Enter the Number of Players (min 2,max 5):");
		gotoxy(44,2);
		re_play_num:
		cin>>m;

		if(m<2)
			{
			cout<<"\nMINIMUN 2 OPPONENTS ..:";
			goto re_play_num;
			}
		else if(m>5)
			{
			 cout<<"MAXIMUM OPPONENTS 5 :";
			 goto re_play_num;
			}
		clrscr();
		get_user(p1,m);  //Player name inputted
		char get;

		restart:
		for( i=0,q=1;i<m;i++,q++)
			{
			if(i+1==m)
			q=0;

			getmovie(i,q,p1);

			if(i+1 ==  m)
				{
				clrscr();
				score_sort(p1,p2,m);
				score_display(p2,m);
				cout<<"\n\n\n\n\n\t\tWanna continue or terminate :('c' or 't')";
				correct:
				cin>>get;

				if(get=='c' || get=='C')
				    {
				    goto restart;
				    }
				else if(get=='t' || get=='T')
					{
					 score_write(p2,m);
					 clrscr();
					 cout<<"\n\t\t\t\tDEVELOPED BY ";
					 cout<<"\n\n1.PEEYUSH AGGARWAL";
					 cout<<"\n2.AMIT CHADHA";
					 cout<<"\n3.RISHABH KHANDELWAL";
					 cout<<"\n\n\n\n\t\t\t\tGAME ENDS ";
					 getch();
					 }
				else
					{
					cout<<"\n\n\t\tEnter a Valid Option !!:";
					goto correct;
					}
			 }
	    }


		}


	// Inputs the player name

	void game::get_user(play_data p1[],int m)
		{
		 for(int i=0;i<m;i++)
		    {
		    cout<<"\n\n Player"<<i+1<<"..  Enter a name :";
		    flag1:
		    gets(p1[i].user_name);
		    if(p1[i].user_name[0]=='\0')
			{
			textcolor(RED + BLINK);
			cprintf("%s","\n\nEnter a valid player name !!");
			textcolor(WHITE);
			cout<<"\n\nEnter :";
			goto flag1;
			}
		    }
		}

	//inputs movie name and handles game-play

	void game::getmovie(int i,int q,play_data p1[])
		{
		 clrscr();
		 cout<<"\n\n\n\n\t\t\t\t"<<p1[i].user_name;
		 cout<<"'s Turn \n\n\n\n\t\t\tPress any key when ready....";
		 getch();
		 clrscr();

		 /********************************************************

		   pword,ch,i2,i3 -variables for processing
		   a - stores name of movie
		   l - stores length of movie

		 ********************************************************/

		 char a[BUFSIZ],pword[BUFSIZ],ch;
		 int l,i2=0,i3=0;
		 cout<<"\n\n\n"<<p1[q].user_name;
		 cout<<"\n\nEnter the name of the movie \n(max 50 characters.)  :";
		 flag2:
		 fflush(stdout);

		while ((ch = getch()) != EOF
			&& ch != '\n'
			&& ch != '\r'
			&& i2 < sizeof(pword) - 1)
			{
			if (ch == '\b' && i2 > 0)
				{
				printf("\b \b");
				fflush(stdout);
				i2--;
				pword[i2] = '\0';
				}
			else if (isalnum(ch) || isspace(ch))
				 {
				 putchar('*');
				 pword[i2++] = (char)ch;
				}
			}

	 pword[i2] = '\0';
	   if(pword[0]=='\0')
	     {
	      cout<<"\n\n\nEnter a valid movie name :";
	      goto flag2;
	      }
	   strcpy(a,pword);

	  l=strlen(a);
	  for( i3=0;i3<l;i3++)
	     {
	      if(isupper(a[i3]));
	      a[i3]=tolower(a[i3]);
	     }


	   solve(a,p1,i);
		}

	   // Controls the processing of game

	void game::solve(char a[],play_data p1[],int player_num)
	     {
		/***********************************************************

		  used - stores the characters used by player as answer
		  and  - character inputted by player as answer
		  b    - name of movie with only vowels bring displayed
		  l    - length of the movie
	    movie_type - stores the type of movie as specified
		chance - max no. of chances a user have i.e 9
	    pre_chance - no. of blanks before the cycle begins
	   post_chance - no. of blanks after the cycle ends
	  init_pos_ans - positions the given answer in array `used'
		 start - stores the time at beginning of player's turn
		   end - stores the time at the end of player’s turn
		  i,i2 - variables for processing

		***********************************************************/
		char used[50],ans,b[BUFSIZ];
		int l,chance=9,pre_chance=0,post_chance,i2=0,init_pos_ans=0;
		 for(int i=0;i<50;i++)
		 used[i]='\0';
	      l=strlen(a);
	      strcpy(b,a);


	   for(i=0;i<l;i++)
	     {
	 if(b[i]=='.' || b[i]=='a' || b[i]=='e' || b[i]==' ' || b[i]=='\0' || b[i]=='i' || b[i]=='u' || b[i]=='o')
		   b[i]=b[i];
		else
		   {
		    b[i]='-';
		   pre_chance++;
		   }
	     }

	  char movie_type[9];
	  strcpy(movie_type,"HOLLYWOOD");

	  cout<<"\n\n\n The movie is ???[h-Hollywood/b-bollywood] :";
	 flag3:
	 cin>>movie_type[0];
	   if(movie_type[0]=='b' || movie_type[0]=='h' )
		{
		movie_type[0]=toupper(movie_type[0]);
		}
	   else if(movie_type[0]=='H' || movie_type[0]=='B')
		 {
		 goto flag_continue;
		 }
	   else
		{
	       cout<<"\nOnly `h' or `b' :";
	       goto flag3;
	       }

	 flag_continue:

	 clrscr();
	 gotoxy(25,10);
	 cprintf("\nPress a key when ready to solve");
	 getch();
	 clrscr();

	 cout<<"\n\nSolve the movie : "<<b;
	 post_chance=pre_chance;
	 int check_chance=chance;
	 used[0]='\0';

	clock_t start,end;   //variables for the purpose of time

	start=clock();
	while(chance>0)
	 {

	   if(check_chance!=chance)
	      {
		movie_type[i2]='-';
		cout<<"\n\n"<<movie_type;
		i2++;
	       }
	    else
	      cout<<"\n\n"<<movie_type;
	   reenter1:
	   cout<<"\nLetters used :"<< used<<"\n\nYour answer :(no vowels) :";
	   cin>>ans;
	   for(int i=0;i<50;i++)
	     {
	      if(used[i]==ans)
		 {
		 cout<<"\nLetter already used.";

		 goto reenter1;
		 }
	      }
	  used[init_pos_ans]=ans;
	  used[init_pos_ans+1]=' ';
	  init_pos_ans+=2;
   if(ans=='a' || ans=='e' || ans=='i' || ans=='o' || ans=='u')
	{
	 cout<<"\n\n"<<ans<<" is a vowel ";
	 goto reenter1;
	}

   if(isupper(ans))
     ans=tolower(ans);

    l=strlen(b);
      for(int m=0;m<=l;m++)
	{
	 if(b[m]=='-')
	   {
	    if(a[m]==ans)
	       {
		b[m]=ans;
		pre_chance--;
	       }
	   }}
  check_chance=chance;
 if(post_chance==pre_chance)
   chance--;
    post_chance=pre_chance;

 if (pre_chance==0)
    break;
 else
     {
       clrscr();
       cout<<"\n\nKeep solving :"<<b;
     }
 }
 clrscr();
 end=clock();
 p1[player_num].time+=(end-start)/CLK_TCK;
 p1[player_num].score+=chance;


 if(chance==0)

   {
    cout<<"\n\n\nThe Answer :"<<a;

    textcolor(RED+BLINK);
    textbackground(YELLOW);
    cout<<"\n\n\n";
    cprintf("%s","YOU LOSE THIS ROUND");
    cout<<"\n\nYour Current score :"<<chance;
    cout<<"\nYour Current time is :"<<(end-start)/CLK_TCK<<" seconds";
    cout<<"\n\nYour Total score is :"<<p1[player_num].score;
    cout<<"\nYour Total time is :"<<p1[player_num].time<<" seconds";
    cout<<"\n\n\n\n\t\t\tPress any key to continue ";
    textcolor(WHITE);
    textbackground(BLACK);
    }
 else
    {
    cout<<"\n\n\nThe Answer :"<<a;

    textcolor(RED+BLINK);
    textbackground(YELLOW);
    cout<<"\n\n\n";
    cprintf("%s","YOU WIN THIS ROUND ");
    cout<<"\n\n";
    cprintf("%s","");
    cout<<"\n\n\nYour Current score :"<<chance;
    cout<<"\nYour Current time is :"<<(end-start)/CLK_TCK<<" seconds";
    cout<<"\n\nYour Total score is :"<<p1[player_num].score;
    cout<<"\nYour Total time is :"<<p1[player_num].time<<" seconds";
    cout<<"\n\n\n\n\t\t\tPress any key to continue ";
    textcolor(WHITE);
    textbackground(BLACK);
    }
   getch();

	}

    // sorts the data of structure as per score and time taken

       void game::score_sort(play_data p1[],play_data p2[],int m)
       {
	  /****************************************************************

	     temp1 -  used for sorting score
	     temp2 -  used for sorting name
	     temp3 -  used for sorting time

	  *****************************************************************/
	int temp1;
	char temp2[20];
	float temp3;

	 for(int i=0;i<m;i++)
		{
		 p2[i].score=p1[i].score;
		 p2[i].time=p1[i].time;
		 strcpy(p2[i].user_name,p1[i].user_name);
		}

	for(i=1;i<m;i++)
	  {
	   for(int j=m-1 ; j>=i; j--)
	       {
		if(p2[j].score > p2[j-1].score)
			{
			temp1 = p2[j].score;
			p2[j].score = p2[j-1].score;
			p2[j-1].score = temp1;

			strcpy(temp2 , p2[j].user_name);
			strcpy(p2[j].user_name , p2[j-1].user_name);
			strcpy(p2[j-1].user_name , temp2);

			temp3 = p2[j].time;
			p2[j].time = p2[j-1].time;
			p2[j-1].time = temp3;
			}
		else if(p2[j].score == p2[j-1].score)
			{
			 if (p2[j].time < p2[j-1].time)
				{
				 temp1 = p2[j].score;
				p2[j].score = p2[j-1].score;
				p2[j-1].score = temp1;

				strcpy(temp2 , p2[j].user_name);
				strcpy(p2[j].user_name , p2[j-1].user_name);
				strcpy(p2[j-1].user_name , temp2);

				temp3 = p2[j].time;
				p2[j].time = p2[j-1].time;
				p2[j-1].time = temp3;
				}
			}
		}
	   }
       }

       // displays the score during gameplay

       void game::score_display(play_data p2[],int m)
	{ int i;
	 clrscr();
	 start_graph();
	 cleardevice();
	 setbkcolor(12);
	 setcolor(4);
	 settextstyle(1,0,7);
	 rectangle(110,30,545,95);
	 outtextxy(125,30,"SCORE SHEET");

	 settextstyle(1,0,2);
	 outtextxy(5,125,"Pos.");
	 outtextxy(55,125,"Name");
	 outtextxy(425,125,"Score");
	 outtextxy(530,125,"Time");
	 setfillstyle(1,4);
	 bar(0,148,630,148);
	 bar(0,125,630,125);

	 settextstyle(2,0,5);
	 int y_cor=150;
	 for( i=0;i<m;i++,y_cor+=20)
	      {
		 setcolor(1);
		 char temp_pos[20];

		 /******************************************************

		  itoa converts a integer to string .
		  Here it was used for purpose outputting the
		  position in proper graphics format

		 *******************************************************/
		 itoa(i+1,temp_pos,10);
		 outtextxy(5,y_cor,temp_pos);
		 setcolor(4);
		 bar(0,y_cor+15,630,y_cor+15);
	      }


	 setcolor(1);
	  y_cor=150;
	 for(i=0;i<m;i++,y_cor+=20)
		{
		   outtextxy(58,y_cor,p2[i].user_name);
		}

	 y_cor=150;
	 for(i=0;i<m;i++,y_cor+=20)
		{
		 char temp_score[5];

		  /*******************************************************

		  itoa converts a integer to string .
		  Here it was used for purpose outputting the score
		  in proper graphics format

		 *********************************************************/
		 itoa(p2[i].score,temp_score,10);
		 outtextxy(428,y_cor,temp_score);
		}

	 y_cor=150;
	 for(i=0;i<m;i++,y_cor+=20)
		{
		 char temp_time[10];

		 /*********************************************************

		  gcvt converts a floating-point no. to string .
		  Here it was used for purpose outputting the time
		  in proper graphics format

		 **********************************************************/
		 gcvt(p2[i].time,6,temp_time);
		 outtextxy(533,y_cor,temp_time);
		}

	 bar(43,125,43,y_cor-5);
	 bar(400,125,400,y_cor-5);
	 bar(500,125,500,y_cor-5);
	 bar(630,125,630,y_cor-5);

	 getch();
	 closegraph();
	}

	//Writes the score to binary file SCORE.DAT

	void game::score_write(play_data p[],int m)
		{
		 ofstream fout("SCORE.DAT",ios::binary,ios::app);

		 for(int i=0;i<m;i++)
			{
			fout.write((char *)&p[i], sizeof(p[i]));
			}
		fout.close();
		}

	// Reads the score of the previous game in main Console
	// from binary file SCORE.DAT

	void score_read()
		{
		 ifstream fin("SCORE.DAT",ios::binary | ios::in);
		 play_data p;

	 cleardevice();
	 setbkcolor(12);
	 setcolor(4);
	 settextstyle(1,0,7);
	 rectangle(110,30,545,95);
	 outtextxy(125,30,"SCORE SHEET");

	 settextstyle(1,0,2);
	 outtextxy(5,125,"Pos.");
	 outtextxy(55,125,"Name");
	 outtextxy(425,125,"Score");
	 outtextxy(530,125,"Time");
	 setfillstyle(1,4);
	 bar(0,148,630,148);
	 bar(0,125,630,125);

	 settextstyle(2,0,5);
	 int y_cor=150;
	 setcolor(1);

	  int i=1;
	  char temp_pos[5];

	  fin.read((char *)&p, sizeof(p));

	  while(!fin.eof())
		 {
		 itoa(i,temp_pos,10);
		 outtextxy(5,y_cor,temp_pos);

		 i++;

		 outtextxy(58,y_cor,p.user_name);

		 char temp_score[5];
		 itoa(p.score,temp_score,10);
		 outtextxy(428,y_cor,temp_score);

		  char temp_time[10];
		 gcvt(p.time,6,temp_time);
		 outtextxy(533,y_cor,temp_time);

		 bar(0,y_cor+15,630,y_cor+15);

		 y_cor+=20;
		 fin.read((char *)&p, sizeof(p));

		 }
	 fin.close();
	 bar(43,125,43,y_cor-5);
	 bar(400,125,400,y_cor-5);
	 bar(500,125,500,y_cor-5);
	 bar(630,125,630,y_cor-5);

	 getch();
	 closegraph();
		}

       // Displays the rules in the Main Console

       void rules()
		{
		 closegraph();
		 cout<<"\n\n\t\tThe Game is quite interesting and simple.\n";
		 cout<<"\n\n1.Input name of all the players.\n";
		 cout<<"\n2.The computer will ask a player to give a movie to ";
		 cout<<"an opponent .It will ask for movie and type(Hollywood/Bollywood).\n";
		 cout<<"\n3.The movie will be inputted in password form so no need to";
		 cout<<" worry.The movie will be displayed to concerned player with only VOWELS.\n";
		 cout<<"\n4.The Player has to begin to guess the movie in minimum";
		 cout<<" chances and time.\n";
		 cout<<"\n5.The player with best score and time @ the end wins.\n";
		 getch();
		}

       // Initiates the GRAPHICS CONSOLE

       void start_graph()
	{
	  /* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI\\");

	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
	   printf("Graphics error: %s\n", grapherrormsg(errorcode));
	   printf("Press any key to halt:");
	   getch();
	   exit(1); /* terminate with an error code */
	}

	}

