#include <stdio.h>

//function prototype
void  swap( int *px, int *py);
int main(void) {
	int a = 3;
	int b = 4;
	int *px = &a;
	int *py = &b;
	printf("px and py before swapping %d %d\n", *px, *py);
	swap(px,py);
	printf("px and py after swapping %d %d\n", *px, *py);
	return 0;
}
/*interchange *px and *py */
void  swap( int *px, int *py) {
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
}
