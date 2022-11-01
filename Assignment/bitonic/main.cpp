#include "bitonics.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

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

int main() {

    srand(time(0));
    int length = 8;
    vector<int> set;
    generate_Random(&set, length);
    printList(&set, length);
    sequentialBitonic(&set,0, 1, length);

    printList(&set, length);

    return 0;
}

