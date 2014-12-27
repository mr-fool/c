#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*Declaring Constant */
int const BASE = 2;
int const BASE_TEN = 10;

/* converting from decimal require the following information input number,quotient, remainder*/
int inputNumber;
int calculationRemainder;
int lengthForArray;
int lengthForDecimal;
int quotient;
int result = 0;
int exponent = 0;

/*Function Prototype*/
int length();
int calculation();

/*Calcuating the length of the input*/
int length() {
	/*Calculating the length for the array*/
	lengthForArray = floor((log(inputNumber) / log(BASE_TEN)) + 1);
	printf("%s%d\n","Legnth of the input number ",lengthForArray);
	return 0;

}

/*Actual calucation place*/


int calculation() {
	/*printf("%s%d\n","The precondition result is: ",result);*/
	quotient = inputNumber;
	while (quotient != 0) {
		calculationRemainder = quotient % 10; /*Finding the remainder */
		quotient = quotient / 10;
		result = result + calculationRemainder * pow(2,exponent);
		++exponent;
		/*printf("%s%d\n","The initial result is: ",result);*/

	}
	printf("%s%d\n","The result is: ",result); /*priting the final result*/
	return 0;
}



int main(int arc, char *argv[]) {
	inputNumber = atoi( argv[1]);
	length();	
	calculation();
	return 0;
}
