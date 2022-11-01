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

void mpi_merge(vector<int> *data, int beg, int dir, int center) {

    if (center > 1) {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        int k = center/2;
        for ( int i = beg; i < beg+k; i++) {
            if (rank == i) {
                int length = data->size();
                vector<int> importData(length);
                MPI_Recv(importData.data(), length, MPI_INT, i+k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int a = 0; a < length; a++) {
                    if (data->at(a) > importData[a]){
                        int temp = importData[a];
                        importData[a] = data->at(a);
                        data->at(a) = temp;
                    }
                }

                MPI_Send(importData.data(), length, MPI_INT, i+k, 0, MPI_COMM_WORLD);
            }

            if (rank == i+k) {
                int length = data->size();
                MPI_Send(data->data(), length, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Recv(data->data(), length, MPI_INT, i+k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        mpi_merge(data, beg, dir, k);
        mpi_merge(data, beg+k, dir, k);
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

void swapNodes(vector<int> *data, int beg, int dir, int center) {
    if (center < 1) {
        int k = center / 2;
        swapNodes(data, beg, 1, k);
        swapNodes(data, beg+k, 0, k);

        mpi_merge(data, beg, dir, center);
    }
} 

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
