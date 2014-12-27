#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*Declaring Constant */
int const BASE = 2;
int const BASE_TEN = 10;

/* converting from decimal require the following information number, quotient, remainder*/
int inputNumber;
int quotient;
int calculationRemainder;
int lengthForArray;
int lengthForDecimal;

/*Function Prototype*/
int length();
int calculation();


/*Calcuating the length of the input*/
int length() {
	/*Calculating the length for the array*/
	lengthForArray = floor((log(inputNumber) / log(BASE)) + 1);
	printf("%s%d\n","Legnth of the number in binary ",lengthForArray);
	
	/*Calculating the legth in decimal form */
	lengthForDecimal = floor((log(inputNumber) / log(BASE_TEN)) + 1);
	printf("%s%d\n","Legnth of the number input ",lengthForDecimal);
	return 0;
}

/*Actual calucation place*/
int calculation() {
	int location = 0; /*Used to keep track of the array*/
	int resultArray[lengthForArray],/*Setting an array size*/
	quotient = inputNumber;
	

	while (quotient != 0) {
		resultArray[location++] = quotient % 2; /* Any odd number mod 2 is always 1 
		and any even numver mod 2 is always 0*/
		quotient = quotient / 2; /* since quotient is integer the decimal part will always be dropped :P*/
	}
	printf ("%s\n","The binary result is:");
	/*Printing the the array aka the binary number*/
	for (location = location - 1; location >= 0; location--) {
		printf("%d", resultArray[location]);
	}
	printf ("\n");
	return 0;
}

int main(int arc, char *argv[]) {
	inputNumber = atoi( argv[1]);
	length();	
	calculation();
	return 0;
}
