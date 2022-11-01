#include "bitonics.h"
#include <vector>
#include <iostream>

using namespace std;

void SwapItems (vector<int> *arr, int a, int b) {
    int temp = arr->at(a);
    arr->at(a) = arr->at(b);
    arr->at(b) = temp;
}

void merge(vector<int> *arr, int beg, int dir, int center) {
    // cout << "sequential bitonic" << endl;
    if (center > 1) {
        int k = center/2;
        for (int i=beg; i<beg+k; i++) {
            if (dir==(arr->at(i)>arr->at(i + k))) {
                // cout << "sqwapping: " << arr->at(i) << " at position " << i << endl;
                // cout << "sqwapping: " << arr->at(i+k) << " at position " << i+k << endl;
                SwapItems(arr, i, i+k);
            }
                
        }
        merge(arr, beg, dir, k);
        merge(arr, beg+k, dir, k);
    }
}

void sequentialBitonic(vector<int> *arr, int beg, int dir, int center) {
        
        if (center > 1) {
            int k = center/2;
            sequentialBitonic(arr, beg, 1, k);
            sequentialBitonic(arr, beg+k, 0, k);
            
            merge(arr, beg, dir, center);
            // printList(arr, 8);
        }
        
} 


