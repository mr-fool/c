/*
 * banker.cpp
 * The Banker's Algorithm for deadlock avoidance.
 *
 * Student Name:
 * Student Number:
 * 
 * Class: CPSC 457 Spring 2015
 * Instructor: M. Reza Zakerinasab
 *
 * Copyright 2015 University of Calgary. All rights reserved.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;


// You should pass the proper parameters to this function and implement the banker's algorithm inside
bool isSafe ()
{
    return true;
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
        for (j = 0; j < numResources; j++)
            iss >> allocation[index][j];
        
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
	// You need to pass the required parameters to this function and implement the Banker's algorithm inside.
    if (isSafe())
        cout << "Safe execution order: " << sequence << ". Grant request "
            << reqStr << " from P" << pid << "." << endl;
    else
        cout << "Potential deadlock among processes. Reject request " << reqStr
            << " from P" << pid << "." << endl;
    
    
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
