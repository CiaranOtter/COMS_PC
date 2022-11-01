// #include "scans.h"
#include <vector>
#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int nprocs;


void mpi_parallel_scan(vector<int> *out, vector<int> *in) {

    int rank;
    int length = in->size();

    MPI_Comm activeComm;

    for (int i = 0; i < length; i++) {
        out->at(i) = in->at(i);
    }
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    int initSize = length/ nprocs;
    if (initSize < 2) {
        initSize = 2;
    }

    for (int d =initSize; d < length; d = d*2) {
        vector<int> localData(d);
        int flag = rank < length/ d;
        MPI_Comm_split(MPI_COMM_WORLD, flag, rank, &activeComm);

        if (flag) {
            MPI_Scatter(in->data(), d, MPI_INT, localData.data(), d, MPI_INT, 0, activeComm);
            for (int innerD =0; innerD < log2(d); innerD++) {
                for (int i =0; i < innerD; i += pow(2, innerD+1)) {
                    localData[i + pow(2, innerD+1) - 1] += localData[i + pow(2, innerD) -1];
                }
            }
        
            MPI_Gather(localData.data(), d, MPI_INT, in->data(), d, MPI_INT,0, activeComm);
        }
        
    }

    in->at(length-1) = 0;
    
    for (int d = length; d >= 2;  d -= floor(d/2)) {
        int flag = rank < length/d;

        MPI_Comm_split(MPI_COMM_WORLD, flag, rank, &activeComm);
        vector<int> localData(d);

        if (flag) {
            MPI_Scatter(in->data(), d, MPI_INT, localData.data(), d, MPI_INT, 0, activeComm);
            for (int innerD =0; innerD < log2(d); innerD++) {
                for (int i =0; i < innerD; i += pow(2, innerD+1)) {
                    int t = localData[i + pow(2, innerD) - 1];
                    localData[i + pow(2, innerD) -1] = localData[i + pow(2, innerD+1) - 1];
                    localData[i + pow(2, innerD+1) - 1] += t;
                }
            }
            
            MPI_Gather(localData.data(), d, MPI_INT, in->data(), d, MPI_INT, 0, activeComm); 
        }
    } 


    int gap = length/ nprocs;
    vector<int> localOut(gap);
    vector<int> localData(gap);

    MPI_Scatter(in->data(), gap, MPI_INT, localData.data(), gap, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(out->data(), gap, MPI_INT, localOut.data(), gap, MPI_INT, 0, MPI_COMM_WORLD);
    for (int j =0; j < gap; j++) {

        localOut[j] += localData[j];
    }

    MPI_Gather(localOut.data(), gap, MPI_INT, out->data(), gap, MPI_INT, 0, MPI_COMM_WORLD);

    if (MPI_COMM_NULL != activeComm) {
        MPI_Comm_free(&activeComm);
    }
    
}