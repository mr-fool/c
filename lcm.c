 
#include <stdio.h>
#include <pthread.h>

struct data {
    int num1;
    int num2;
	int result;
};

void *doSomeCalculation(void *argument)
{
    struct data *arg = (struct data *)argument;
	arg->result = arg->num1 + arg->num2;
    printf("Result of calculation: %d\n", arg->result);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char * argv[])
{
    FILE * fd;
    char str[80];
    
    // Check for the right number of parameters
    if (argc != 2)
    {
        printf("Usage: lcm_skeleton <filename>\n");
        return -1;
    }
	
    // Open the file for writing
    fd = fopen (argv[1], "r");

    //read file into array; assuming the file has only two numbers in separate lines
    int numberArray[2];
	for (int i = 0; i < 2; i++)
    {
        fscanf(fd, "%ld", &numberArray[i]);
    }
	
    // Close the file
    fclose(fd);

	
	// Create a thread
    pthread_t thread;
    struct data args;
    args.num1 = numberArray[0];
    args.num2 = numberArray[1];
	printf("Num 1: %d,  Num 2: %d\n", args.num1, args.num2);

    if (pthread_create(&thread, NULL, &doSomeCalculation, (void *)&args) != 0) {
        printf("Error! Thread not created.\n");
        return -1;
    }

    pthread_join(thread, NULL); /* Wait until thread is finished */
    return 0;
}

