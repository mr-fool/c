#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

//Function Prototype
void printDirectory(void);
int numDir(const char* dirname);
void printPID(int pid);
void commandCheck(int argc, char *argv[]);

int main ( int argc, char *argv[] ) {
	if (argc == 1) {
		printf("%s\n","PID");
		printDirectory();
	}
	else if (argc > 1) {
		commandCheck(argc,argv);
	}
	return 0;
}
void printDirectory(void){
	//data type represents a directory stream. 
	DIR *dir;
	struct dirent *ep;   
	//creating a directory stream  
	dir = opendir ("/proc");
	if (dir != NULL){
		while( (ep = readdir(dir)) ){
			if(numDir(ep->d_name)) {
				fprintf(stdout, "%s\n", ep->d_name);	
			}//end if
		}//end while
		
	(void) closedir (dir);
	}
	else
    perror ("Couldn't open the directory");
}
//iterate array to check if it is digit
int numDir(const char* dirname) {
	while(*dirname) {
		if(!isdigit(*dirname++)) {
			 return 0;
		}
	}
	return 1;
}

void printPID(int pid){
	printf("%d\t",pid);
}
void commandCheck(int argc, char *argv[]){
	int i;
	int pid;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'p':
					pid = atoi(argv[i+1]);
					printPID(pid);
					break;
				case 's':
					printf("%s\n","State option reached");
					break;
				case 'U':
					printf("%s\n","utime option reached");
					break;
				case 'S':
					printf("%s\n","utime option reached");
					break;
				case 'v':
					printf("%s\n","vmen option reached");
					break;
				case 'c':
					printf("%s\n","cmdline option reached");
					break;
			}//end switch
		}//end if
	}
}
