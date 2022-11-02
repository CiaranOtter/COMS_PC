#include "bitonics.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>

using namespace std;

void printList(vector<int> *arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << arr->at(i) << " ";
    }
    cout << endl;
}

void mpi_SwapItems(vector<int> *arr, int a, int b)
{
    int temp = arr->at(a);
    arr->at(a) = arr->at(b);
    arr->at(b) = temp;
}

void mpi_merge(vector<int> *data, int rank, int dir, double partner, int tag)
{
    if (partner != rank) {

        
        // int k = (partner-rank)/2;
        // mpi_merge(data, rank, dir, k, tag);
        // mpi_merge(data, rank+k, dir, k, tag);

        cout << "rank: " << rank << " partner " << partner << " dir " << dir << endl;
        // int next = partner/2;
        // int prev = floor(partner/2);
        // mpi_merge(data, rank ,1 , next, tag);
        // mpi_merge(data, rank, 0, (-1*next), tag);
        
    }
 
    // if (center > 1)
    // {
    //     int rank;
    //     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //     int k = center / 2;

    //     mpi_merge(data, beg, 1, k, tag);
    //     mpi_merge(data, beg + k, 0, k, tag);
        
    //         if (rank == beg)
    //         {
    //             if ((dir == (beg > beg+k))) {
    //                 int length = data->size();
    //                 vector<int> *importData = new vector<int>(length);
    //                 MPI_Recv(importData->data(), length, MPI_INT, beg + k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //                 // cout << "data recieved to be sorted" << endl;
    //                 // cout << "rank " << rank << endl;
    //                 importData->insert(importData->end(), data->begin(), data->end());
                    
    //                 sequentialBitonic(importData, 0, dir, length*2);
            
    //                 // printList(importData, importData->size());
    //                 data = new vector<int>(importData->begin(), importData->begin()+importData->size()/2);
    //                 importData = new vector<int>(importData->begin() + importData->size()/2, importData->end());
    //                 printList(data, data->size());
    //                 // printList(importData, importData->size());
    //                 MPI_Send(importData->data(), length, MPI_INT, beg + k, 0, MPI_COMM_WORLD);
    //                 tag = tag+2;
    //             } 
    //             if ( dir != (beg > beg+k))
    //             {
    //                 int length = data->size();
    //                 vector<int> newArr(length);
                    
    //                 MPI_Send(data->data(), length, MPI_INT, beg+k, 0, MPI_COMM_WORLD);
    //                 MPI_Recv(data->data(), length, MPI_INT, beg+k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //             }
                
    //         }

    //         if (rank == beg + k)
    //         {
    //             if ((dir == (beg > beg+k))) {
    //                 int length = data->size();
    //                 vector<int> *importData = new vector<int>(length);
    //                 MPI_Recv(importData->data(), length, MPI_INT, beg, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //                 // cout << "data recieved to be sorted" << endl;
    //                 // cout << "rank " << rank << endl;
    //                 importData->insert(importData->end(), data->begin(), data->end());
                    
    //                 sequentialBitonic(importData, 0, dir, length*2);
            
    //                 // printList(importData, importData->size());
    //                 data = new vector<int>(importData->begin(), importData->begin()+importData->size()/2);
    //                 importData = new vector<int>(importData->begin() + importData->size()/2, importData->end());
    //                 printList(data, data->size());
    //                 // printList(importData, importData->size());
    //                 MPI_Send(importData->data(), length, MPI_INT, beg, 0, MPI_COMM_WORLD);
    //                 tag = tag+2;
    //             } 
    //             if (dir != (beg > beg+k)){
    //                 int length = data->size();
                    
    //                 MPI_Send(data->data(), length, MPI_INT, beg, 0, MPI_COMM_WORLD);
    //                 MPI_Recv(data->data(), length, MPI_INT, beg,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //             }
    //         }

        

        
    // }
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

void swapNodes(vector<int> *data, int beg, int dir, double center, int tag)
{
    int pe;
    MPI_Comm_size(MPI_COMM_WORLD, &pe);
    if (center >= 0 && center != beg)
    {
        // if (center + beg < 0 || center + beg == 0) {
        //     return;
        // }
        int k = floor(center/2);
        int prev;
        prev = ceil(center/2);
        
        // cout << 
        
        
       
         
        if (k > 0) {
            if (k != 1 || (k == 1 && beg%2 == 0)) {
                swapNodes(data, beg, 1, center-k, tag);
            }
        }
        
        mpi_merge(data, beg,  dir, center, tag);

         if (prev > 0) {
            if (k != 1 || (k == 1 && beg%2 == 0)) {
                swapNodes(data, beg, 0, beg-prev, tag);
            }
        }
        
        
        // if (prev > 0) {
        //     swapNodes(data, beg, 0, beg-prev, tag);
        // }
        
        
        
            
        
        // }
        
        
       
        // MPI_Barrier(MPI_COMM_WORLD);
        // swapNodes(data, beg + k, 0, k, tag);
        // MPI_Barrier(MPI_COMM_WORLD);
        
        
        // mpi_merge(data, beg, 1, )
    }
}

void mpi_ParallelBitonic(vector<int> *arr, int beg, int dir, int center)
{
    
    int length = arr->size();
    int pe;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &pe);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    // cout << "rank " << rank << endl;
    // if (rank == 0) {
    //     printList(arr, arr->size());
    // }
    
    int localLength = length/pe;
    // cout << "length" << localLength;
    vector<int> localData(localLength);
    
    MPI_Scatter(arr->data(), localLength, MPI_INT, localData.data(), localLength, MPI_INT, 0, MPI_COMM_WORLD);
    // printList(&localData, localLength);
    sequentialBitonic(&localData, 0, 1, localLength);
    if (rank == 3) {
        swapNodes(&localData, rank, 1, (pe/2)+(rank), 0);
    }

    // if (rank == 4) {
    //     swapNodes(&localData, rank, 0, (pe/2), 0);
    // }
    
    // mpi_merge(&localData, rank, 1, pe - rank, 0);
    // MPI_Barrier(MPI_COMM_WORLD);
    // MPI_Gather(localData.data(), localLength, MPI_INT, arr->data(), localLength, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Barrier(MPI_COMM_WORLD);
    // printList(arr, arr->size());
}
