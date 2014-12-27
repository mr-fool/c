/*Calculating compound interest*/
#include <stdio.h>
#include <math.h>

int main (void) {
	double amount;
	double principal;
	double rate;
	int year;
	int i;
	printf("Please enter the principal, rate, year\n");
	scanf("%lf %lf %d",&principal,&rate,&year);
	
	/*Printing the header*/
	printf("%4s%21s\n", "Year","Amount on deposit");
	
	/*Calculate the amount on deposit for x year*/
	for ( i = 0 ; i <= year; i++) {
		/*Calculate new amount for specified year*/
		amount = principal * pow (1.0 + rate, i);
		
		/*Output one table row*/
		printf("%4d%21.2lf\n",i,amount);
	}
	return 0;
} 
