#include <vector>

void serial_scan(std::vector<int> *out, std::vector<int> *in);
void omp_parallel_scan(std::vector<int> *out, std::vector<int> *in);
void mpi_parallel_scan(std::vector<int> *out, std::vector<int> *in);