#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//Function Prototype
void printDirectory(void);
int numDir(const char* dirname);
void printPID(int pid);
void commandCheck(int argc, char *argv[]);
int *directoryList(void);
bool checkPid(int id);

//Global variable
int pid;
int directory[100000];

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
		
	closedir (dir);
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
//parsing command line option
void commandCheck(int argc, char *argv[]){
	int i;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case 'p':
					pid = atoi(argv[i+1]);
					directoryList();
					if ( checkPid(pid) == true) {
						printf("%s\n", "the directory is correct");
					}
					//printPID(pid);
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
bool checkPid(int id){
	int i;
	int array_size = sizeof(directory)/sizeof(int);
	for(i=0; i< array_size;i++){
		if (id == directory[i]) {
			return true;
		}//end if
	}
	return false;
}
int *directoryList(void){
	int i = 0;
	//data type represents a directory stream. 
	DIR *dir;
	struct dirent *ep;   
	//creating a directory stream  
	dir = opendir ("/proc");
	//printf("%s\n","directory");
	if (dir != NULL){
		while( (ep = readdir(dir)) ){
			if(numDir(ep->d_name)) {
				directory[i] = atoi( (ep->d_name) );
				//printf("%d\t",directory[i]);
				i++;
			}//end if
		}//end while
		
	closedir (dir);
	}
	else {
		perror ("Couldn't open the directory");
	}//end else
	return directory;
}

