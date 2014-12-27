/*A program that normalize fractions and simplify it*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int numerator;
int denominator;
char fraction[LINE_MAX];
/* Function Prototype*/
void normalize(void);
void errorChecking(void);
int reduce(int denominator, int numerator);
void swap( int *a, int *b);

void errorChecking(){
	//Checking to see if the denominator is zero
	if (denominator == 0 ) {
		printf("The fraction is undefined: %s\n",fraction);
		exit(0);
	}
}

void swap( int *a, int *b) {
	//temporarily variable that holds the immediate value
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int reduce(int denominator, int numerator){
	
	//Case 1: the denominator and the numerator is the same 
	if (denominator == numerator) {
		denominator = 1;
		numerator = 1;
		printf("The reduced fraction is 1\n");
		exit(0);
	}
	//Case 2: whole number situation
	if (numerator % denominator == 0) {
		int answer = numerator / denominator;
		printf("The reduced fraction is %d\n", answer);
		exit(0);
	}
	
	while (1) {
		denominator = denominator - numerator * (denominator/numerator);
		if (denominator == 0 ) {
			return numerator;
		}
		swap (&numerator,&denominator);
	}
	return 1;
}
void normalize(){
	if (denominator < 0 ) {
		// If the denominator is negative
		// Multiple both numerator and denominator by -1
		numerator = numerator * -1;
		denominator = denominator * -1;
	}
}
int main(void) {
	int gcd;
	printf("Please enter a fraction in the format of x/y\n");
	scanf("%s",fraction);
	sscanf(fraction,"%d/%d",&numerator, &denominator);
	normalize();
	errorChecking();
	gcd = reduce(denominator,numerator);
	numerator = numerator / gcd;
	denominator = denominator /gcd;
	printf("The reduce fraction is %d%s%d\n",numerator,"/",denominator);
	return 0;
}
