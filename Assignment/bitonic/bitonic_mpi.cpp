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
                // cout << "sqwapping: " << arr->at(i) << " at position " << i << endl;
                // cout << "sqwapping: " << arr->at(i+k) << " at position " << i+k << endl;
                mpi_SwapItems(arr, i, i+k);
            }
                
        }
        mpi_merge(arr, beg, dir, k);
        mpi_merge(arr, beg+k, dir, k);
    }
}


// void findPartner() {
//     int rank;
//     int size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     int max = log2(size);
//     for (int i = 0; i < max; i++) {

//     }

// }

void printList(vector<int> *arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr->at(i) << " ";
    }
    cout << endl;
}

void mpi_ParallelBitonic(vector<int> *arr, int beg, int dir, int center) {
        
        int length = arr->size();
        int pe;
        MPI_Comm_size(MPI_COMM_WORLD, &pe);
        vector<int> localData(length/pe);
        printList(arr, length);
        MPI_Scatter(arr->data(), length/pe, MPI_INT, localData.data(), length/pe, MPI_INT, 0, MPI_COMM_WORLD);
        sequentialBitonic(&localData, 0, 1, length/pe);
        MPI_Gather(localData.data(), length/pe, MPI_INT, arr->data(), length/pe, MPI_INT, 0, MPI_COMM_WORLD);
        printList(arr, length);
        
} 
