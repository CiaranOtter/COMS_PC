#include <vector>

void sequentialBitonic(std::vector<int> *arr, int beg, int dir, int center);
void omp_ParallelBitonic(std::vector<int> *arr, int beg, int dir, int center);
void mpi_ParallelBitonic(std::vector<int> *arr, int beg, int dir, int center);

