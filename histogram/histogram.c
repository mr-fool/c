#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Function Prototype*/
void initializeArray(int * arr, int size);
void initalizeLabel(char ** pointer, int size);
 
int main(void) {
        int i; //outer for counter for array elements
        int j;// inner for counter couts *s in each histogram bar
        int size; //the size of the array
        printf("Please enter the number of data\n");
        scanf("%d", &size);
        /*Initialize the size of the array data*/
        int data[size];
        initializeArray(data, size);
 
        /*Initialize the size of the array label*/
        char ** label = (char **)malloc(size * sizeof(char *));
        initalizeLabel(label, size);
        printf("%s%13s%17s\n", "Label", "Value", "Histogram");
 
        /*for each element of array data, output a bar of the histogram*/
        for (i = 0; i < size; i++){
                printf("%s%13d        ", label[i], data[i]);
                for (j = 1; j <= data[i]; j++) { //print one bar
                        printf("%c", '*');
                }
                printf("\n"); //end a histogram bar
        }
       
        return 0;
}
 
void initializeArray(int array[], int size) {
        int i = 0;
        printf("Please enter the data\n");
        for (i = 0; i < size; i++) {
                scanf("%d", &array[i]);
        }
}
void initalizeLabel(char ** pointer, int size){
        int i = 0;
        printf("Please enter the label\n");
        for (i = 0; i < size; i++) {
                pointer[i] = (char *)malloc(32);
                scanf("%s", pointer[i]);
        }
}


