/* A Russian Roulette Game */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

/* prototypes */
void introduction( int a);
void game( int b);
void credit( int c);
int getch(void);
int kbhit(void);

//void gameOverTimer(int choice);
int main(void) {
	system("clear");
	printf("Welcome to the Russian Roulette Game\a\n\n");
	
	//Printing the nagant revolver
	printf(",++IIIIII~++I==~~III+I$IMI+$+...........\n");
	printf(",O8888DD8Z88888D8=~=~~+I8III=I..........\n");
	printf(",,,,:~ZI=O88Z.ZO$7=$$77IMIII+...........\n");
	printf(",,,,,,::::::~~~O$ZOOZO8DZIII.=..........\n");
	printf(",,,,,,,,,,,:::~OIDNNNMMO8I77I+=+=+......\n");
	printf(",,,,,,,,,,,,,::~OO$ZIOZ$$$$IIIZ$$$......\n");
	printf("......,....,,,,:~$~~=OIO$$7IIO$ZZZI:....\n");
	printf("...........,.,,::O::~~$~~~7I78$O$8Z7I...\n");
	printf(",,,..........,,,:I,:::+:::I::~=OZ$88$...\n");
	printf(",,,,...,,...,,,,,,,I8Z~$8,,,::~=8I$ZI7..\n");
	printf(",,,,,,,,,,....,,,,,,,,,,,,,,,,:=ZIOZII..\n");
	printf(",,,,,,,,,,,,,,,,.,,,..,:I.=8O=:~8OO7II..\n");
	printf(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:::7...\n");
	
	
	printf("\n");
	
	//seed random-number generator
	srand( time(0) );
	/*Initialize array of 3 pointers to functions that each take 
	 * an int argument and return void*/
	void (*selection[3])(int) = {introduction,game,credit};
	
	//Hold user's choice
	int static choice;
	
	
	do {
		// set a character for reading user input
		char ch;
		// set a timer for 30 seconds to time out if no input
		long end_time = (time(0) + 30);
		
		// prompt the user to enter something
		printf("Enter a number between 0 and 2\n");
		while (time(0) < end_time){
			
			if( kbhit() && ( ch = getch() ) != EOF && ch >= '0' && ch <= '3'){
				// the character they input matches what we're looking for
				// turn it into a number 0-2 by subtracting the character value of '0'
				// which just so happens to work because '0', '1', and '2' are right beside each other :P
				choice = ch - '0';

				// also break out of the first while loop
				break;
			}//end if
		} //end while
		if(time(0) >= end_time){
			printf("30 SECOND HAVE PASSED COMRADE.\n NO MERCY FOR TRAITORS\n");
			//printing the rope for the traitors
			printf("                    =.7  .. ..      ....\n");
			printf("                    ~.7  .. ..        ..\n");
			printf("                   +:$7 .               \n");
			printf("                   |,$. .               \n");
			printf("                   ~$|OO=               \n");
			printf("                 7$$.8I:$               \n");
			printf("                 =|88Z$DZZ              \n");
			printf("                 O8ZZ+D8~            .  \n");
			printf("                ~D,DIN$|              . \n");
			printf("                .~7,NZ8OZ7              \n");
			printf("               ::=8ZZ+OZOO$             \n");
			printf("                |=7ZZN78OO$             \n");
			printf("                :7NNO|Z8OZ+             \n");
			printf("                 $NDNZ8OZ$              \n");
			printf("                7$OO7N8OZ               \n");
			printf("               +I ZOOZ=Z                \n");
			printf("              I8 OOZZO8|                \n");
			printf("             I|.ZZ. +7O8|               \n");
			printf("           ,:I7OZ      OI=              \n");
			printf("          .=IZZ$        88I             \n");
			printf("          D7ZZ           OZ+            \n");
			printf("          DOO             I8            \n");
			printf("         IO8.              8$           \n");
			printf("         ZIO               ~I           \n");
			printf("         7,$                8~          \n");
			printf("          8=               ,I8          \n");
			printf("          ZZ.              ON~          \n");
			printf("           8$.            O~N.          \n");
			printf("            OI,         :O=D.           \n");
			printf("..           DZ|.I...=,~$DD           ..\n");
			printf("......         N8$$,OZODD$         .. ..\n");
			printf("............      8.NZ.   . ...    .....\n");
			printf(".............     ......................\n");
			exit(EXIT_FAILURE);
		}
		else if(choice < 3) {
			//Invoke function at location choice in array f and pass choice as an argument
			(*selection[choice])(choice);
		}
	}
	while(choice < 3);
	// exit if user types 3 or above
	printf("Game Ended\n");
	return 0;
}
void introduction( int a) {
	printf("Russian roulette is a potentially lethal game of chance in which a player\n"
		   "places a single round in a revolver, spins the cylinder, places the muzzle\n"
		   "against their head, and pulls the trigger.\n\n");
	
}
void game( int b) {
	char userName[100];
	FILE *score;
	//loop control
	int i;
	
	//Game play variable
	const int cylinder = 6;
	int roundsLeft = cylinder;
	unsigned int status;
	int const DEAD = 1;
	char continueGame;
	printf("Please enter your user name\n");
	scanf("%s",userName);
	if ( (score = fopen("score.txt","w") ) == NULL) {
		printf("File could not be opended\n");
		exit(0);
	}
	
	printf("Are you ready\a\n");
	fprintf(score,"%s %s %s\n","userName", "round", "status");
	for ( i = 1; i <=cylinder; i++) {
		status = rand() % roundsLeft;
		if (status == DEAD) {
			fprintf(score,"%s %d %s\n",userName, i, "DEAD");
			printf("Player %d is DEAD \n\a",i);
			printf("GAME OVER\n");
			//printing a skull
			
printf("            =M$. . . .+NMM              \n");
printf("          ZN.            .OM:           \n");
printf("         M.                 $M          \n");
printf("       NM.                   .I         \n");
printf("      MN                       =,       \n");
printf("     .M                         M.      \n");
printf("     M,    ~$N7+       7..~=,   =M      \n");
printf("    .M   :NOMMMMMM    MMMMMMMM   M      \n");
printf("    ,M  :OMMMMMMMMM . MM8NMZOMN. DI     \n");
printf("     M  NMDMM8MOMMM.  MMMMMMMMMM ZM     \n");
printf("     M  IMMMMMMMMM$   IMNMMMN$OO ZM     \n");
printf("     M.  MMMMMMMNZ  . ~MMMO8NN=  M|     \n");
printf("     :M   DNMMMM.  |,. .D|Z7~.   M.     \n");
printf("      M+          ZM.M:         =|      \n");
printf("       MM        $M= ..         M       \n");
printf("        .M,                   O7        \n");
printf("          .M. ..O$$MNM,$NDM~8M          \n");
printf("            O8MM~M..Z.=MM=M M.          \n");
printf("             D.M.M O~:..I:D M           \n");
printf("             .I   ,.~~,..  M=           \n");
printf("              :M.        MM8            \n");
printf("                  :ZOZ$=.               \n");
                                
			exit(0);
		}
		else {
			fprintf(score,"%s %d %s\n",userName, i, "ALIVE");
			int turnLeft = cylinder - i;
			printf("Player %d is ALIVE \a\n",i);
			printf("%d rounds left\n",turnLeft); 
			printf("enter c and a to abort to continue\n");
			scanf(" %c",&continueGame);

			roundsLeft--;
			
			//Continue the madness or stop
			switch (continueGame) {
				case 'c':
					continue;
					break;
				case 'a':
					printf("Goodbye coward\n");
					exit(0);
				default:
					printf("Nagant revolver jammed and today is your lucky day\n");
					exit(0);
			}//end of switch statement 
			
		} // end of else statement
	} //end of for statement
}

void credit( int c) {
	printf("Dedicated to the fallen comrade\n"
		   "To the dead, and the next one to die\n\n");
	printf("Special thanks to poutine, fury and mrexodia for helping\n");
}

int getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int kbhit(void){
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
 
