#include <vector>
#include <iostream>
#include <ctime>
#include <mpi.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include "scans.h"

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

int length =0;
ofstream outs;
vector<int> sizes;
vector<double> seqTimes;
vector<double> ompTimes;
vector<double> mpiTimes;

void printList(vector<int> *out);
void randoms(vector<int> * r);
bool checkValid(vector<int> * seq, vector<int> *par);
void scan_test(int size);

void printRes(int rank);

int main (int argc, char** argv) {
    srand(1000);

    MPI_Init(&argc, &argv);

    scan_test(3);

    MPI_Finalize();
    
}

void scan_test(int size) {

    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int length = pow(2, size);

    
    vector<int> set(length);

    vector<int> mpi_parallelResults(length);
    double deltaSequential;

    if (rank == 0) {
        randoms(&set);
        cout << "=======================" << endl;
        cout << "Testing scan function:" << endl;
        cout << "size of set: " << length << endl;
        sizes.push_back(length);
        cout << "------------------------" << endl;

        vector<int> serialResults(length);
        vector<int> omp_parallelResults(length);

        auto sequentialStart = Clock::now();
        serial_scan(&serialResults, &set);
        auto sequentialEnd = Clock::now();
        // printList(&serialResults);

        auto omp_parallelStart = Clock::now();
        omp_parallel_scan(&omp_parallelResults, &set);
        auto omp_parallelEnd = Clock::now();

        

        deltaSequential = std::chrono::duration<double>(sequentialEnd - sequentialStart).count();
        seqTimes.push_back(deltaSequential);
        auto delatOmpParallel = std::chrono::duration<double>(omp_parallelEnd - omp_parallelStart).count();
        ompTimes.push_back(delatOmpParallel);
        long double ompSpeedUp = deltaSequential/delatOmpParallel;
        cout << endl;
        cout << "sequential Time (base line): " << deltaSequential  << endl;
        cout << endl;
        if (checkValid(&serialResults, &omp_parallelResults)) {
            cout << "openMP scan vaild" << endl;
        } else {
            cout << "openMP scan invalid" << endl;
        }
        cout << "openMP parallel Time: " << delatOmpParallel << endl;
        cout << "openMp speed up: " << ompSpeedUp << endl;
    }

    // MPI_Bcast(set.data(), length, MPI_INT, 0, MPI_COMM_WORLD);

    auto mpi_parallelStart = Clock::now();
    mpi_parallel_scan(&mpi_parallelResults, &set);
    auto mpi_parallelEnd = Clock::now();
    
    auto deltaMpiParallel = std::chrono::duration<double>(mpi_parallelEnd - mpi_parallelStart).count();

    if (rank == 0) {
        long double mpiSpeedUp = deltaSequential/deltaMpiParallel;
        mpiTimes.push_back(deltaMpiParallel);
        cout<< endl;
        if (checkValid(&mpi_parallelResults, &mpi_parallelResults)) {
            cout << "MPI scan vaild" << endl;
        } else {
            cout << "MPI scan invalid" << endl;
        }
        cout << "MPI parallel Time: " << deltaMpiParallel << endl;
        cout << "MPI speedup: " << mpiSpeedUp << endl;
    }
    
    if (size == 24) {
        if (rank == 0) {
            cout << "====================" << endl;
        }
        

        printRes(rank);
        return;
    }

    scan_test(size+1);
}

bool checkValid(vector<int> * seq, vector<int> *par) {
    int size = seq->size();
    for (int i =0; i < size; i++) {
        if (seq->at(i) != par->at(i)) {
            return false;
        }
    }

    return true;
}

void randoms(vector<int>* r) {
    int length = r->size();

    for (int i =0; i < length; i++) {
        r->at(i) = rand()%10;
    }

}

void printList(vector<int> *out) {
    for (int i =0; i < length; i++) {
        cout << out->at(i) << " ";
    }

    cout << endl;
}

void printRes(int rank) {
    if (rank ==0) {
        outs.open("outputs.txt");
        int l = sizes.size();

        for (int i = 0; i < l; i++) {
            outs << seqTimes[i];
            if (i != l-1) {
                outs << ",";
            }
        }
        outs << endl;

        for (int i =0; i < l; i++) {
            outs << ompTimes[i];
            if (i != l-1) {
                outs << ",";
            }
        }
        outs << endl;

        for (int i =0; i < l; i++) {
            outs << mpiTimes[i];
            if (i != l-1) {
                outs << ",";
            }
        }
        outs << endl;

        outs.close();
    }
}
