#include <iostream>

using namespace std;

void scan(out[], in[]);
void printlist(out[]);

int main() {

    int set[8] = {2,3,7,7,10,17,23,26};
    int *setResult[8];

    printList(set);
    scan(setResults, set);
    printList(setResult);

    return 0;
}

void scan(int *out[], int in[]) {
    int i = 0;
    int N = out->size();
    *out[0] = in[0];
    for (i = 1; i < N; i++) {
        *out[i] = in[i] + *out[i-1];
    }
}

void printList(int out[]) {
    for (int el : out) {
        cout << el;
    }
    cout << endl;
}
