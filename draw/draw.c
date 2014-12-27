/* Program that draw rectangle, circle and triangle
 There is an eastern egg function here*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

/* Function Prototype*/
void circle(void);
void drawRectangle(void);
void drawTriangle(void);
void drawRightTriangle(void);
void drawEquilateralTriangle(void);
void drawInvertedTriangle(void);
void drawIsoscelesTriangle(void);
int MyCaseInsensitiveCompare( char * s1, char * s2);

/*Compare the string */
int MyCaseInsensitiveCompare( char * s1, char * s2) { 
	int i; 
	char ch1, ch2; 
	for(i = 0; ch1 = tolower(s1[i]), ch2 = tolower(s2[i]), ch1 || ch2; i++)  {
		if(ch1 > ch2) {
			return 1; 
		}
		if(ch1 < ch2) {
			return -1; 
		}
	} 
	return 0; 
}
/*drawing rectangle*/
void drawRectangle(void) {
	/*index*/
	int i;
	int j;
	/*information necessary to draw a rectangle*/
	int height;
	int width;
	
	printf("Please enter the height\n");
	scanf("%d", &height);
	
	printf("Please enter the width\n");
	scanf("%d", &width);
	/*Drawing */
	for (i = 0; i < height; i++) {
		
		for ( j = 0; j < width; j++) {
			
			if (i == 0 || i == height -1 || j == 0 || j == width -1) {
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf ("\n");
	}
	
}
/*Calling Helper Functions to Draw Triangle*/
void drawTriangle(void) {
	char type[LINE_MAX];
	char* equilateral = "equilateral";
	char* isosceles = "isosceles";
	char* scalene = "scalene";
	char* right = "right";
	char* invertedRight = "inverted";
	/*Prompt the type of triangle that the user would like the draw*/
	printf("Please enter the traingle that you would like to draw: \n");
	printf("equilateral\nisosceles\nscalene\nright\n");
	scanf("%s", type);
	/*Deciding which helper function to call*/
	if ( MyCaseInsensitiveCompare(type,equilateral) == 0) {
		drawEquilateralTriangle();
	}
	else if ( MyCaseInsensitiveCompare(type,isosceles) == 0) {
		drawIsoscelesTriangle();
	}
	else if ( MyCaseInsensitiveCompare(type,scalene) == 0) {
		
	}
	else if ( MyCaseInsensitiveCompare(type,right) == 0) {
		drawRightTriangle();
	}
	else if ( MyCaseInsensitiveCompare(type,invertedRight) == 0) {
		drawInvertedTriangle();
	} 
	else {
		printf("wrong shape\n");
	}
}
/*Drawing right triangle*/
void drawRightTriangle(void) {
	/*necessary information to draw a right triangle*/
	int side;
	int i;
	int j;
	/*Prompting for size */
	printf("Please enter the side size of the triangle: \n");
	scanf("%d", &side);
	/*Drawing the top vertex*/
	printf("*\n");
	for (i = 2; i <= side ; i++ ) {
		/* Drawing the height */
		printf("*");
		for ( j = 2; j <= i-1; j++) {
			/*Drawing the hollow part*/
			printf(" ");
		}
		/* draw the hypotenuse*/
			printf("*\n");
		
	}     		
	/*Drawing the bottom line*/
	for (i = 1; i <= side + 1; i++) {
		printf("*");
	}
	printf("\n");
}
/*Drawing Inverted Right Triangle*/
void drawInvertedTriangle(void) {
	/*necessary information to draw a right triangle*/
	int side;
	int i = 0;
	int j = 0;
	/*Prompting for size */
	printf("Please enter the side size of the triangle: \n");
	scanf("%d", &side);
	for ( i = 0, j = 0; i < side; i = 0, j = 1) {
		for (i = 0; i < side; i++) {
			if (i == side -1 || i == 0 || j == 0) {
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
		side = side -1;

	}
}

/*Drawing Equilateral Triangle*/
void drawEquilateralTriangle(void){
	
}
/*Draw Isosceles Triangle*/
void drawIsoscelesTriangle(void){

	int i,j,k,n;
	printf("Enter number of sides of the triangle \n");
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n-i;j++){
			printf(" ");
		}
		for(k=1;k<=(2*i)-1;k++){
			if ( k == 1 || k == (2*i)-1 || i == n) {
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}
int main(void) {
	char shape[LINE_MAX]; 
	char* rectangle = "rectangle"; 
	char* circle = "circle";
	char* triangle = "triangle";
	printf("Please enter the shape you want to draw: ");
	printf("rectangle,circle,triangle\n");
	scanf("%s", shape);
	
	if ( MyCaseInsensitiveCompare(shape,rectangle) == 0) {
		drawRectangle();
	}
	else if ( MyCaseInsensitiveCompare(shape,circle) == 0) {
		printf("circle\n");
	}
	else if ( MyCaseInsensitiveCompare(shape,triangle) == 0) {
		drawTriangle();
	}
	else {
		printf("wrong shape\n");
	}
	return 0;
}
