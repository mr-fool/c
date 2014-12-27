/*Cleaner Version*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main (void) {
	unsigned guess; //user guess
	unsigned answer; //the computer random answer
	Guess:
		printf("Guess a number between 1-10\n");
		scanf("%u", &guess);
		printf("Your guess is %2u\n", guess);
		srand(time(NULL)); //randomizing the number using seed
		answer = 1 + (rand() % 10 );
		printf("The answer is %2u\n", answer);
		if (answer != guess) {
			printf("Your guess is incorrect, please try again\n");
			goto Guess;
		}
		else {
			printf("Your guess is correct\n");
		}
		return 0;
}
