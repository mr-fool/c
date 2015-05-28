#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//Function Prototype
void printDirectory(void);
int numDir(const char* dirname);
void printPID(int pid);
void printState(char stateChar);
void commandCheck(int argc, char *argv[]);
int directoryList(void);
bool checkPid(int id);
char state(int id);
void resultHeader(void);
void utime(int id);
void stime(int id);
void vmem(int id);
void cmdline(int id);
void noPID(void);
//Global variable
int pid;
int directory[100000];
char stateChar = '1';
int flag_pid;
int flag_state;
int flag_utime;
int flag_stime;
int flag_vmem;
int flag_cmdline;
int size;
char filename[PATH_MAX];
FILE *file;

int main ( int argc, char *argv[] ) {
	if (argc == 1) {
		printf("%s\n","PID");
		printDirectory();
	}
	else if (argc > 1) {
		commandCheck(argc,argv);
	}
	//printf("%s%c\n","the state is ",stateChar);
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
	if (pid != 0) {
		printf("%d\t",pid);
	}
	fflush(stdout);
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
					/*if ( checkPid(pid) == false) {
						printf("%s\n", "the directory is incorrect");
						exit(0);
					}*/
					flag_pid = 1;
					//printPID(pid);
					break;
				case 's':
					flag_state = 1;
					break;
				case 'U':
					flag_utime = 1;
					break;
				case 'S':
					flag_stime = 1;
					break;
				case 'v':
					flag_vmem = 1;
					break;
				case 'c':
					flag_cmdline = 1;
					break;
			}//end switch
		}//end if
	}//end for
	printf("PID\t");
	resultHeader();
	if (flag_pid != 0) { // there is pid	
		checkPid(pid);
		printPID(pid);
		if (flag_state == 1) {
			state(pid);
			printState(stateChar);
		}
		if (flag_utime == 1) {
			utime(pid);
		}
		if (flag_stime == 1){
			stime(pid);
		}
		if (flag_vmem == 1){
			vmem(pid);
		}
		if (flag_cmdline ==1) {
			cmdline(pid);
		}
		printf("\n");
	}// end if 
	//no pid case
	else if (pid == 0 && flag_pid == 0) {
		int j;
		directoryList();
		//int size = 5;
		for (j=0; j < size; j++) {
			printPID(directory[j]);
		if (flag_state == 1) {
			state(directory[j]);
			printState(stateChar);
		}
		if (flag_utime == 1) {
			utime(directory[j]);
		}
		if (flag_stime == 1){
			stime(directory[j]);
		}
		if (flag_vmem == 1){
			vmem(directory[j]);
		}//end if
		if (flag_cmdline ==1) {
			cmdline(directory[j]);
		}
		printf("\n");
		}//end for 
	}//end else
	//printf("%s%c\n","The stateChar is ", stateChar);
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
int directoryList(void){
	int i = 0;
	//data type represents a directory stream. 
	DIR *dir;
	struct dirent *ep;   
	//creating a directory stream  
	dir = opendir ("/proc");
	//printf("%s\n","directory");
	int tmp = 0;
	if (dir != NULL){
		while( (ep = readdir(dir)) ){
			sprintf(filename, "/proc/%s", ep->d_name);
			if(numDir(ep->d_name)) {
				tmp = atoi( (ep->d_name) );
				if (tmp == 0) {
					break;
				}
				//directory[i] = atoi( (ep->d_name) );
				directory[i] = tmp;
				//printf("%d\t",directory[i]);
				i++;
			}//end if
		}//end while
		
	closedir (dir);
	}
	else {
		perror ("Couldn't open the directory");
	}//end else
	size = i;
	return size;
}
char state(int id){
	//int i;
	//reading file
	FILE *fp;
	char address[100000];
	char str[100000];
	sprintf(address,"%s%d%s","/proc/",id,"/stat");
	//printf("%s%s\n","the directory is ",address);
	fp=fopen(address, "r");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}//end if
	while( fscanf(fp, "%s", str) != EOF) {
        //printf("%s\n", str);	
        if ( strcmp(str,"R") ==0) {
			stateChar = 'R';
		}
		else if ( strcmp(str,"S") == 0 ) {
			stateChar = 'S';
		}
		else if ( strcmp(str,"D") == 0 ) {
			stateChar = 'D';
		}
		else if ( strcmp(str,"Z") == 0 ) {
			stateChar = 'Z';
		}
		else if ( strcmp(str,"T") == 0 ) {
			stateChar = 'T';
		}
	}//end while
	return stateChar;
}
void resultHeader(void) {
	if (flag_state == 1) {
		printf("state\t");
	}
	if (flag_utime == 1) {
		printf("utime\t");
	}
	if (flag_stime == 1) {
		printf("stime\t");
	}
	if (flag_vmem == 1) {
		printf("vmem\t");
	}
	if (flag_cmdline == 1) {
		printf("cmdline\t");
	}
	printf("\n");
}
void printState(char stateChar){
	if (stateChar != '1') {
		printf("%c\t", stateChar);
	}
	fflush(stdout);
}
void utime(int id) {
	int utime;
	sprintf(filename, "/proc/%d/stat", id);
	file = fopen(filename, "r");
	fscanf(file, "%*d %*[^)]) %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d", &utime);
	printf("%d\t", utime);
	fclose(file);
	fflush(stdout);
}
void stime(int id){
	int stime;
	sprintf(filename, "/proc/%d/stat", id);
	file = fopen(filename, "r");
	fscanf(file, "%*d %*[^)]) %*c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d", &stime);
	printf("%d\t", stime);
	fclose(file);
	fflush(stdout);
}
void vmem(int id) {
	int vmem;
	sprintf(filename, "/proc/%d/statm", id);
	file = fopen(filename, "r");
	fscanf(file, "%d", &vmem);
	printf("%d\t", vmem);
	fclose(file);
	fflush(stdout);
}
void cmdline(int id) {
	sprintf(filename, "/proc/%d/cmdline", id);
	file = fopen(filename, "r");
	int array_size;
	char buf[512];
	while(0 < (array_size = fread(buf, 1, 512, file))){
		int i;
		for(i = 0; i < array_size; i++) {
			if(buf[i] == 0) {
				buf[i] = ' ';
			} //end if
		}//end for 
		printf("%.*s", array_size, buf);
	}//end while
	fclose(file);
	fflush(stdout);
}
