#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int numProc;           // The number of processes
int numResources;      // The number of resources
FILE *f;

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("Usage: banker <config file>\n");
		exit(1);
	}
	else {
		int i;
		f = fopen(argv[1], "r");
		fscanf(f, "numProc = %d\n", &numProc);
		fscanf(f, "numResources = %d\n", &numResources);
		printf("numProc is %d\n", numProc);
		printf("numResources is %d\n", numResources);
		int available[numResources];
		fscanf(f, "available = <"); fscanf(f, "'>'");
		for (i = 0; i < numResources;i++) {
			fscanf(f, "%d", &available[i]);	
		}//end for 
		fscanf(f, ">");
		for (int j = 0; j< numResources; j++) {
			printf("The available %d\n", available[j]);
		}
		return 0;
	}//end if 
}
