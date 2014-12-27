/*A survey data analysis program that computes the mean, median and mode of the data*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function Prototypes
void mean (const int answer[], const int size);
void median(int answer[],const int size);
void mode(int const data[],const int size);
void merge(int array[], int l, int m, int r);
void mergeSort(int arry[], int l, int r);
void initializeArray(int array[],const int size);

int main(void) {
	system("clear");
	int size;
	printf("Please enter the number of data\n");
	scanf("%d",&size);
	
	/*Initialize the size of the array data*/
	int data[size];
	initializeArray(data,size);
	
	//Process responses
	mean(data,size);
	median(data,size);
	mode(data,size);
	return 0;
}

void mean (const int answer[],const int size) {
	int i;
	int sum = 0;
	
	//Sum of the data
	for (i = 0; i < size; i++) {
		sum = sum + answer[i];
	}
	//Final answer
	//printf("the sum is %d\n", sum);
	double mean = (double) sum/ size;
	printf("The mean is %.2f\n", mean);
	
}
//Will call merge sort to sort the array and calculate the median
void median(int answer[],const int size) {
	
	mergeSort(answer, 0, size - 1 );
	
	//testing the sorted array
	
	/*int i;
	for ( i = 0 ; i < size; i++) {
		printf("The sorted array %d\n",answer[i]);
	}*/
	
	//the medium calculation
	
	//odd number case
	if (size % 2 ) {
		int median = answer[size/2];
		printf("The median is %d\n",median);
	}
	else {
		int rightIndex = size/2;
		int leftIndex = rightIndex - 1;
		double median =  ( answer[rightIndex] + answer[leftIndex] ) /2.0;
		printf("The median is %.2f\n",median);
	}
} 
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int array[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = array[l + i];
    for(j = 0; j < n2; j++)
        R[j] = array[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the sub-array
  of arr to be sorted */
void mergeSort(int array[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
    }
}

void mode(int const data[],const int size) {
	int sizeDetermination(int const data[],const int size);
	int largest = sizeDetermination(data,size);
	//printf("the largest number in mode function %d\n", largest);
	int realSize = largest + 1;
	int frequency[realSize];
	
	//loop control
	int i;
	int j;
	int z;
	
	//mode finding
	int modeValue = 0;
	int modeFrequency = 0;
	
	//initialize the frequency array
	for ( z = 0; z < realSize; z++) {
		frequency[z] = 0;
		//printf("the value of z: %d\n", z);
	}
	
	//frequency counter
	for ( i = 0; i < size; i++) {
		++frequency[ data[i] ];
		//printf("the value of i: %d\n", i);
		//printf("frequency counter check %d\n",frequency[ data[i] ] );
	}
	
	//displaying the frequency
	printf("data\tfrequency\n");
	for ( j = 0; j < realSize; j++) {
		if (frequency[j] != 0) {
			printf("%d\t%d\n",j,frequency[j]);
		}
		if (frequency[j] > modeFrequency) {
			modeFrequency = frequency[j];
			modeValue = j;
		}
	}
	printf("The mode is %d and its frequency is %d\n",modeValue,modeFrequency);
		
}

//Find the largest element of the array and use it to set the size of the frequency array
int sizeDetermination(int const data[],const int size) {
	int largest = 0;
	int i;
	for (i = 0; i < size; i++) {
		if (data[i] > largest) {
			largest = data[i];
		}
	}
	//printf("the largest number in the data array %d\n", largest);
	return largest;
}

void initializeArray(int array[], int size) {
	int i = 0;	
	printf("Please enter the data\n");
	for ( i = 0; i < size; i++) {
		scanf("%d", &array[i]);
	}
}

