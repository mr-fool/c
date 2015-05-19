#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

//Function Prototype
void printDirectory(void);

void main ( int argc, char *argv[] ) {
	if (argc == 0) {
		printDirectory();
	}
}
void printDirectory(void){
	//data type represents a directory stream. 
	DIR *dir;
	struct dirent *ep;   
	//creating a directory stream  
	dir = opendir ("/proc");
	while (ep = readdir (dir)) {
		if ( isdigit(ep)) {
			puts (ep->d_name); //not print directory name for some reasons
		}
	}//end while
	(void) closedir(dir);//close stream
}
