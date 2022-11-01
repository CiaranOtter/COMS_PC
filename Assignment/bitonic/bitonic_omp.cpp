#include "bitonics.h"
#include <vector>
#include <omp.h>

using namespace std;

void omp_SwapItems(vector<int> *arr, int a, int b) {
    int temp = arr->at(a);
    arr->at(a) = arr->at(b);
    arr->at(b) = temp;
}

void omp_merge(vector<int> *arr, int beg, int dir, int center) {
    if (center > 1) {
        int k = center/2;
        int i;
            for (i=beg; i<beg+k; i++) {
                if (dir==(arr->at(i)>arr->at(i + k))) {
                    omp_SwapItems(arr, i, i+k);
                }          
            }
            omp_merge(arr, beg, dir, k);
            omp_merge(arr, beg+k, dir, k);
        
    
        
    }
}

void omp_ParallelBitonic(vector<int> *arr, int beg, int dir, int center) {
        
        if (center > 1) {
            int k = center/2;
            #pragma omp parallel 
            #pragma omp single nowait
            {
                #pragma omp task shared(arr, beg, dir, k) 
                {
                    omp_ParallelBitonic(arr, beg, 1, k);
                }
                
                #pragma omp task shared(arr, beg, dir, k) 
                {
                    omp_ParallelBitonic(arr, beg+k, 0, k);
                }
               

                #pragma omp taskwait 
                {
                    omp_merge(arr, beg, dir, center);
                }
                
            }
            
        }  
} 
