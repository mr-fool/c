#include <stdio.h>

//function prototype
void  swap( int *px, int *py);
int main(void) {
	int a = 3;
	int b = 4;
	int *px = &a;
	int *py = &b;
	printf("%s%d%s%d", "px and py before swapping ",&px," ",&py);
	swap(px,py);
	printf("%s%d%s%d", "px and py after swapping ",&px," ",&py);
	return 0;
}
/*interchange *px and *py */
void  swap( int *px, int *py) {
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
}
/*
gcc -Wall -c "swap.c" (in directory: /home/mr-fool/Documents/c/swap)
swap.c: In function ‘main’:
swap.c:10:2: warning: format ‘%d’ expects argument of type ‘int’, but argument 3 has type ‘int **’ [-Wformat=]
  printf("%s%d%s%d", "px and py before swapping ",&px," ",&py);
  ^
swap.c:10:2: warning: format ‘%d’ expects argument of type ‘int’, but argument 5 has type ‘int **’ [-Wformat=]
swap.c:12:2: warning: format ‘%d’ expects argument of type ‘int’, but argument 3 has type ‘int **’ [-Wformat=]
  printf("%s%d%s%d", "px and py after swapping ",&px," ",&py);
  ^
swap.c:12:2: warning: format ‘%d’ expects argument of type ‘int’, but argument 5 has type ‘int **’ [-Wformat=]
Compilation finished successfully.
*/
