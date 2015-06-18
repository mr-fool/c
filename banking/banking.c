#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int numProc;           // The number of processes
int numResources;      // The number of resources
int arrayIndex;
int pid;
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
		//printf("numProc is %d\n", numProc);
		//printf("numResources is %d\n", numResources);
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
			if (fscanf(f, "P%d <", &arrayIndex) <= 0){
				break;
			};
			if (arrayIndex < 0 || arrayIndex >= numProc)  {
				printf("Invalid process ID: \n");
				return 1;
			}//end if
			//getting allocation vector
			for (i = 0; i < numResources;i++) {
				fscanf(f, "%d", &allocation[arrayIndex][i]);
				//printf("The allocation vector is %d\n", allocation[arrayIndex][i]); 
				fscanf(f, ">");
			}//end for
			//getting max vector
			for (i = 0; i < numResources;i++) {
				fscanf(f, " <");
				fscanf(f, "%d", &max[arrayIndex][i]);
				//printf("The max vector is %d\n", max[arrayIndex][i]); 
				fscanf(f, ">");
			}//end for 
		}//end while
		int request[numResources];
		fscanf(f, "request %d =", &pid);
			//printf("the pid is %d\n",pid);
		for (i = 0; i < numResources;i++) {
			fscanf(f, " <");
			fscanf(f, "%d", &request[i]);
			//printf("The request vector is %d\n", request[i]); 
			fscanf(f, ">");
			}//end for
		fclose(f);
		
		return 0;
	} //end else
}
