#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

//Function Prototype
void printDirectory(void);

void main ( int argc, char *argv[] ) {
	if (argc == 1) {
		printDirectory();
	}
}
void printDirectory(void){
	//data type represents a directory stream. 
	DIR *dir;
	struct dirent *ep;   
	//creating a directory stream  
	dir = opendir ("/proc");
	if (dir != NULL){
		while (ep = readdir (dir)) {
			puts (ep->d_name);
		}//end while
	(void) closedir (dir);
	}
	else
    perror ("Couldn't open the directory");
}
