#include "bitonics.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <mpi.h>

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

double sequentialTime;

void generate_Random(vector<int> *arr, int length) {
    for (int i =0; i < length; i++) {
        arr->push_back(rand()%100);
    }
}

void printList(vector<int> *arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr->at(i) << " ";
    }
    cout << endl;
}

bool validateSort(vector<int> *arr) {
    int length = arr->size();
    for (int i =1; i < length; i++) {
        if (arr->at(i-1) > arr->at(i)){
            return false;
        }
    }

    return true;
}

void printStats(vector<int> *arr, double deltaTime, string name) {

    double speedUp = sequentialTime/deltaTime;
    cout << name << endl;
    cout << "-------------------------------------" << endl;
    cout << "size of set: " << arr->size() << endl;

    if (validateSort(arr)) {
        cout << name << " sort valid" << endl;
    } else {
        cout << name << " sort invalid" << endl; 
    }

    cout << name <<" run time: " << deltaTime << endl;
    cout << name << " speed up: " << speedUp << endl;
    cout << "-------------------------------------" << endl;

}

void TestSequentialBitonic(vector<int> set) {
    int length = set.size();
    auto start = Clock::now();
    sequentialBitonic(&set, 0, 1, length);
    auto end = Clock::now();

    double deltaTime = std::chrono::duration<double>(end - start).count();
    sequentialTime = deltaTime;
    printStats(&set, deltaTime, "Sequential Bitonic");
}

void TestopenMPBitonic(vector<int> set) {
    int length = set.size();
    auto start = Clock::now();
    omp_ParallelBitonic(&set, 0, 1, length);
    auto end = Clock::now();

    double deltaTime = std::chrono::duration<double>(end - start).count();
    printStats(&set, deltaTime, "OpenMP Parallel Bitonic");
}

void TestMPIBitonic(vector<int> set) {
    int length = set.size();
    int nprocs;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Bcast(set.data(), length, MPI_INT, 0, MPI_COMM_WORLD);

    auto start = Clock::now();
    mpi_ParallelBitonic(&set, 0, 1, length);
    auto end = Clock::now();

    double deltaTime = std::chrono::duration<double>(end - start).count();
    if (rank == 0) {
        printStats(&set, deltaTime, "MPI Parallel Bitonic");
        printList(&set, length);
    }
}

int main(int argc, char** argv) {

    int rank;
    MPI_Init(&argc, &argv);  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (int i = 3; i < 4; i++) {
        srand(time(0));
        int length = pow(2, i);
        vector<int> set;
        generate_Random(&set, length);
        if (rank == 0) {
            printList(&set, length);
            TestSequentialBitonic(set);
            TestopenMPBitonic(set);
        }
        TestMPIBitonic(set);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    
    // auto sequentialStart = Clock::now();
    // sequentialBitonic(&set,0, 1, length);
    // auto sequentialEnd = Clock::now();
    // double deltaSequential = std::chrono::duration<double>(sequentialEnd - sequentialStart).count();
    // printStats(&set, deltaSequential);

    return 0;
}
