#include <stdio.h>
#include <pthread.h>

//Function Prototype
int *inputArray(char * argv[]);

int main(int argc, char * argv[]){
    
    // Check for the right number of parameters
    if (argc != 3){
        printf("Usage: lcm_skeleton <filename>\n");
        return -1;
    } //end if
    int newArray[1000000];
	newArray= inputArray(argv);
	
    return 0;
}

int *inputArray(char * argv[]){
	FILE * fd;
	// Open the file for writing
    fd = fopen (argv[1], "r");
	int numberArray[1000000];

    //read file into array; assuming the file has only two numbers in separate lines
	for (int i = 0; i < 2; i++){
        fscanf(fd, "%ld", &numberArray[i]);
        //printf("the number array is %d\n",numberArray[i]);
    }
	
    // Close the file
	fclose(fd);
	return numberArray;
}
