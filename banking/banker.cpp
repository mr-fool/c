#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;


// You should pass the proper parameters to this function and implement the banker's algorithm inside
int safeFlag = 0;
int count1;
int count2;
int requestCheck;
int k;
bool isSafe (int safeFlag)
{
	if (safeFlag == 1){
		return true;
	}
	return false;
}

int main (int argc, char * const argv[])
{
    ifstream config;       // Configuration file
    string conffile;       // The configuration file name
    int numProc;           // The number of processes
    int numResources;      // The number of resources
    string sequence;       // The execution sequence returned by the Banker's Algorithm
    int i, j, index;       // Indices for the vectors and matrixes
    int pid;               // The ID of the process that is making the request
    string reqStr;         // The request vector in string format
    
    // Read in the config file name from the commanda-line arguments
    if (argc < 2)
    {
        cout << "Usage: banker <config file>" << endl;
        return 0;
    }
    else
    {
        conffile = argv[1];
    }

    // Open the file
    config.open(conffile.c_str());
    
    // Get the number of process and the number of resources
    string line, var, equal;    // strings for parsing a line in the config file
    getline(config, line);
    istringstream iss(line);
    iss >> var >> equal >> numProc;     // Get the number of processes
    iss.clear();
    
    getline(config, line);
    iss.str(line);
    iss >> var >> equal >> numResources;    // Get the number of resources
    iss.clear();
    
    // Create the available vector, the max matrix, and the allocation matrix
    // according to the number of processes and the number of resources
    int * available = new int[numResources];
    int ** max = new int*[numProc];
    int ** allocation = new int*[numProc];
    for (int i = 0; i < numProc; i++)
    {
        max[i] = new int[numResources];
        allocation[i] = new int[numResources];
    }
    
    // Get the available vector
    getline(config, line);
    replace(line.begin(), line.end(), '<', ' ');  // Remove "<" and ">"
    replace(line.begin(), line.end(), '>', ' ');
    iss.str(line);
    iss >> var >> equal;
    for (j = 0; j < numResources; j++)        // Read in the "available" vector
        iss >> available[j];
    iss.clear();
    
    // Get the max matrix and the allocation matrix
    for (i = 0; i < numProc; i++)
    {
        getline(config, line);
        replace(line.begin(), line.end(), '<', ' ');
        replace(line.begin(), line.end(), '>', ' ');
        iss.str(line);
        iss >> var;
        index = atoi(&var.at(1));            // Get the process ID
        if (index < 0 || index >= numProc)  
        {
            cerr << "Invalid process ID: " << var << endl;
            return 0;
        }
        
        // Get the number of resources allocated to process "index".
        for (j = 0; j < numResources; j++) {
            iss >> allocation[index][j];
            //printf("The line 100 allocation = %d\n",allocation[index][j]);
        }//end for
        // Get the max allocation to process "index".
        for (j = 0; j < numResources; j++)
            iss >> max[index][j];
        
        iss.clear();
    }
    
    // Get the request vector
    int * request = new int[numResources];
    getline(config, line);
    reqStr = line.substr(line.length() - 2 * numResources - 1, 2 * numResources + 1);
    replace(line.begin(), line.end(), '<', ' ');
    replace(line.begin(), line.end(), '>', ' ');
    iss.str(line);
    iss >> var >> pid >> equal;
    for (j = 0; j < numResources; j++)          // Read in the "request" vector
        iss >> request[j];
    iss.clear();
        
        
    // Check the request using the Banker's algorithm. 
    // Get the need vector
    int need[numProc][numResources];
	for (i =0;i < numProc;i++){
		for ( j = 0;j < numResources;j++){
			need[i][j] = max[i][j] - allocation[i][j];
			//printf("The need array %d\n", need[i][j]);
		}//end inner for 
		//printf("\n");
	}//end for 
	//printf("The pid is %d\n", pid);
	
	//initial request check
	for (j=0; j< numResources;j++) {
		if (request[j] > need[pid][j] || request[j] > available[j]){
			printf("Potential deadlock among processes. Reject request <");
			while (j< numResources) {
				printf("%d ",request[j]);
				j++;
			}//end  while
			printf("\b> from P%d\n",pid); 
			exit(1);
			}//end if
	}//end for
	bool completed[numProc];
	for (i=0; i < numProc;i++) {
		completed[i]=false;
	}//end for 
	for (j=0; j< numResources;j++) {
		if (request[j] <= need[pid][j] && request[j] <= available[j]) {
			requestCheck++;
		}//end if 	
	}//end for 
	//request granted
	int work[numResources];
	for (i=0; i < numResources; i++) {
		work[i] = 0;
	}//end for 
	int safeSequence[numProc];
	if (requestCheck == numResources) {
		//first stage
		for (j=0; j< numResources;j++) {
			available[j] = available[j] - request[j];
			allocation[pid][j] = allocation[pid][j] + request[j];
			need[pid][j] = need[pid][j] - request[j];
			//printf("The need vector in stage 1 %d\n",need[pid][j]);
			work[j] = available[j] + allocation[pid][j];
			//printf("work %d\n",work[j]);
		}//end for
		completed[pid] = true;
		printf("the sequence is P%d, ", pid);
		count1 = 0;
		//second stage
		for (i=0; i < numProc;i++) {
			for (j=0; j< numResources;j++) {
				//printf("The need vector P%d is %d ", i,need[i][j]);
				if (need[i][j] <= work[j]) {
					count1++;
					//printf("The count1 is %d\n", count1);
				}//end if
			}//end inner for 
			//printf("\n");
			if (count1 == numResources && completed[i] == false) {
				for (j=0; j< numResources;j++) {
					work[j] = work[j] + allocation[i][j];
					printf("work line 187 %d \n", work[j]);
				}//end for
				completed[i] = true; 
				printf("P%d, ", i);
				i = 0;
				j=0;
				printf("i being reset %d \n",i);
			}//end if
			count1 = 0;
		}//end for  
		printf("\n");
	}//end if
	for (j=0; j< numProc;j++) {
		printf("the completed %d status: %d\n", j, completed[j]);
	}//end for 
    // Free all allocated memory space
    delete[] available;
    for (int i = 0; i < numProc; i++)
    {
        delete[] max[i];
        delete[] allocation[i];
    }
    delete[] max;
    delete[] allocation;    
}
/*
./banker.out configBanker1.txt
the sequence is P1, work line 187 7 
work line 187 4 
work line 187 3 
P3, i being reset 0 
work line 187 10 
work line 187 4 
work line 187 5 
P2, i being reset 0 
work line 187 10 
work line 187 4 
work line 187 7 
P4, i being reset 0 

the completed 0 status: 0
the completed 1 status: 1
the completed 2 status: 1
the completed 3 status: 1
the completed 4 status: 1

*/
