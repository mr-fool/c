#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int studentID;
	char name[100];
	float balance; 
	
	//file pointer
	FILE *fee;
	if ( (fee = fopen("fee.txt","w") ) == NULL) {
		printf("File could not be opended\n");
		exit(0);
	}
	else {
		printf("Please enter the studentID, name, and fee owed\n");
		printf("Enter EOF to end input\n");
		scanf("%d%s%f",&studentID, name,&balance);
		fprintf(fee,"%s\t%s\t%s\n","Student ID","Student Name","Fee Owed");
		while (!feof(stdin) ) {
			fprintf(fee,"%d\t\t%s\t%f\n", studentID, name, balance);
			scanf("%d%s%f",&studentID, name,&balance);
		}
		fclose(fee);
	}
	return 0;
}
