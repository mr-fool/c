
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;


// You should pass the proper parameters to this function and implement the banker's algorithm inside
bool isSafe (int np, int nr, int *alloc[], int *max[], int avail[])
{
    int i, x, j, k, a;
    vector<int> seq;
    int need[np][nr];
    int av[np+1][nr];
    
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    cout << "Need matrix." << endl;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nr; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    for (j = 0; j < nr; j++)
    {
        av[0][j] = avail[j];
    }
    bool flag[np];
    bool test = true;
    for (i = 0; i < np; i++)
        flag[i] = false;
    int cnt = 0;
    while (cnt == 0)
    {
        for (i = 0; i < np; i++)
        {
            if (flag[i] == false)
            {
                bool test1 = true;
                for (j = 0; j < nr; j++)
                {
                    if ((need[i][j] > av[0][j]))
                        test1 = test1 && false;
                    if ((need[i][j] <= av[0][j]))
                        test1 = test1 && true;
                }
                if (test1 == true) // i.e if all need is less than all avail
                {
                    seq.push_back(i);
                    for (k = 0; k < nr; k++)
                    {
                        av[0][k] = av[0][k] + alloc[i][k];
                    }
                    for (j = 0; j < nr; j++)
                    {
                        cout << av[0][j] << " ";
                    }
                    cout << endl;
                    flag[i] = true;
                } //if test == true
                
            } //1st if
        } //1st for loop
        for (a = 0; a < np; a++)
        {
            if (flag[a] == false)
            {
                cnt = 0; //if any are false cnt = 0
                break;
            }
            else
                cnt++; // if all are true cnt != 0
        } //for
        
    } //while

    cout << "A possible sequence:" << endl;
    for (i = 0; i < np; i++)
        cout << "P" << seq[i] << " -> ";
    cout << endl;

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
    if (isSafe(numProc, numResources, allocation, max, available))
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
