/*Calculate the diameter,circumference and area of a circle
  Using C pi*/

/*Including Library*/
#include <math.h> 
#include <stdio.h>

int main (void) {
	/*Declaring the variable*/
	int radius;
	int diameter;
	int area;
	int circumference;
	printf("Please enter the radius of the circle\n");
	scanf("%d", &radius); /*reading radius*/
	printf("The radius is %d", radius);
	
	/*Calculation part*/
	diameter = radius * 2;
	area = M_PI * (radius *radius); /*pi *r^2*/
	circumference = 2* M_PI * radius; /*2pir*/
	
	printf("\t The diameter is %d\n", diameter);
	printf("The area is %d\n", area);
	printf("The circumference is %d\n", circumference);
	return 0;
}
