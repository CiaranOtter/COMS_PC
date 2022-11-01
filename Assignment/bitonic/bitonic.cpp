#include "bitonics.h"
#include <vector>
#include <iostream>

using namespace std;

// void printList(vector<int> *arr, int length) {
//     for (int i = 0; i < length; i++) {
//         cout << arr->at(i) << " ";
//     }
//     cout << endl;
// }

void merge(vector<int> *arr, int beg, int dir, int center) {
    cout << "sequential bitonic" << endl;
    if (center > 1) {
        int k = center/2;
        for (int i=beg; i<beg+k; i++) {
            if (dir==(arr->at(i)>arr->at(i + k))) {
                iter_swap(arr->begin() +i ,arr->begin()+i+k);
            }
                
        }
    }
}

void sequentialBitonic(vector<int> *arr, int beg, int dir, int center) {
        cout << "sequential bitonic" << endl;
        cout << "begin_is" << beg << endl;
        cout << "center is: " << center << endl;
        if (center > 1) {
            int k = center/2;
            sequentialBitonic(arr, beg, 1, k);
            sequentialBitonic(arr, beg+k, 0, k);
            
            merge(arr, beg, dir, center);
            // printList(arr, 8);
        }
        
} 


