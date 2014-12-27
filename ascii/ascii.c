#include <stdio.h>
int main(){
	int i=0; // 
	while (i<=127){ /*227 = total number of asii value*/
		if (i%8==0 ) {
			printf("\n");
			
		}
		if ((i<=32) || (i==127) ){ /*Since 1-32 and 127 is non-printable*/
			printf("%c",'.'); /*replace non-printable character with .*/
			i++; /*move forward*/
		}
	
		else { /*if not special case then just print normally*/
			printf("%c",i); 
			i++;
		}
	}
	printf("\n");
	return 0; /*Keep compiler happy*/
}
