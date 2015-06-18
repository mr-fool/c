#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int numProc;           // The number of processes
int numResources;      // The number of resources
int index;
FILE *f;

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("Usage: banker <config file>\n");
		exit(1);
	}
	else {
		int i;
		f = fopen(argv[1], "r"); //opening file
		fscanf(f, "numProc = %d\n", &numProc); //reading numProc
		fscanf(f, "numResources = %d\n", &numResources); //reading numResources
		printf("numProc is %d\n", numProc);
		printf("numResources is %d\n", numResources);
		int available[numResources];
		int max[numProc][numResources];
		int allocation[numProc][numResources];
		fscanf(f, "available = <"); 
		for (i = 0; i < numResources;i++) {
			fscanf(f, "%d", &available[i]);	
		}//end for 
		fscanf(f, ">");
		//debug
		/*for (int j = 0; j< numResources; j++) {
			printf("The available %d\n", available[j]);
		}*/
		
		//reading the rest of the file
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		while ((read = getline(&line, &len, f)) != -1) {
			fscanf(f, "P%d <", &index) || printf("didn't match 'P%%d <'\n");
			if (index < 0 || index >= numProc)  {
				printf("Invalid process ID: \n");
				return 1;
			}//end if
			for (i = 0; i < numResources;i++) {
				fscanf(f, "%d", &allocation[index][i]) || printf("didn't match %%d\n");
				fscanf(f, " ");
				printf("The allocation vector is %d\n", allocation[index][i]); 
			fscanf(f, ">");
			}//end for
			//printf("%s\n", line);
		fclose(f);
		}//end while
		
		return 0;
	} //end else
}
