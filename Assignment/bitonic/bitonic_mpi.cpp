#include "bitonics.h"
#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

void mpi_SwapItems (vector<int> *arr, int a, int b) {
    int temp = arr->at(a);
    arr->at(a) = arr->at(b);
    arr->at(b) = temp;
}

void mpi_merge(vector<int> *arr, int beg, int dir, int center) {
    
    if (center > 1) {
        int k = center/2;
        for (int i=beg; i<beg+k; i++) {
            if (dir==(arr->at(i)>arr->at(i + k))) {
                mpi_SwapItems(arr, i, i+k);
            }
                
        }
        mpi_merge(arr, beg, dir, k);
        mpi_merge(arr, beg+k, dir, k);
    }
}


void findPartner() {
    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max = log2(size);
    for (int i = 0; i < max; i++) {

    }

}

void mpi_ParallelBitonic(vector<int> *arr, int beg, int dir, int center, int partner) {
        
        if (center >= 1) {
            int k;
            int rank;
            int pe;
            int localSize;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            MPI_Comm_size(MPI_COMM_WORLD, &pe);

            int localLength = center/pe;
            vector<int> localData(localLength);
            

            MPI_Scatter(arr->data(), localLength, MPI_INT, localData.data(), localLength, MPI_INT, 0, MPI_COMM_WORLD);
            if (rank % 2== 0) {
                mpi_ParallelBitonic(&localData, 0, 1, localLength, rank+1);
            } else {
                mpi_ParallelBitonic(&localData, 0, 0, localLength, rank -1);
            }
            
            
            
            
            
            mpi_merge(&localData, 0, dir, center);
            printList(arr, 8);
        }
        
} 
