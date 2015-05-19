#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>

//Function Prototype
void printDirectory(void);
int numDir(const char* dirname);

int main ( int argc, char *argv[] ) {
	if (argc == 1) {
		printDirectory();
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

int numDir(const char* dirname) {
	while(*dirname) {
		if(!isdigit(*dirname++)) {
			 return 0;
		}
	}
	return 1;
}
