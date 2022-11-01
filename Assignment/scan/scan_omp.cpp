#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <omp.h>
#include "scans.h"

using namespace std;

const int NUM_THREAD = 8;

void omp_parallel_scan(vector<int> *out, vector<int> *in) {
    int i =0;
    int d =0;
    int length = in->size();
    int jump = log2(length);
    vector<int> a = *in;
    int change = 0;
    
    omp_set_dynamic(0);
    for (d = 0; d < jump; d++){
        change = pow(2, d+1);
        #pragma omp parallel for num_threads(NUM_THREAD) firstprivate(change)
        for (i =0; i < length; i+=change) {
            int x = i + pow(2, d+1)-1;
            int y = i + pow(2, d) -1;
            a[x] = a[y] + a[x];
        }
    }  

    a[length-1] = 0;
    for (d = jump -1; d >= 0; d--) {
        change = pow(2, d+1);
        #pragma omp parallel for num_threads(NUM_THREAD) shared(out, d, length) firstprivate(change)
        for (i =0; i < length; i += change) {
            int x = i + pow(2, d+1) - 1;
            int y = i + pow(2, d) -1;
            int t = a[y];
            a[y] = a[x];
            a[x] = t + a[x];

        }
    } 
    #pragma omp parallel for
    for (int j =0; j < length; j++) {
        out->at(j) = in->at(j) + a[j];
    } 
}