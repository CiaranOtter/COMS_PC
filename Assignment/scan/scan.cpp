#include <iostream>

using namespace std;

int * scan(int *out[], int in[], int l);
void printlist(int out[]);

int main() {

    int set[8] = {2,3,7,7,10,17,23,26};

    printList(set);
    int setResult[8] = scan(set, 8);
    printList(setResult);

    return 0;
}

int * scan(int in[], int l) {
    int i = 0;
    int out[l];
    out[0] = in[0];
    for (i = 1; i < l; i++) {
        out[i] = in[i] + out[i-1];
    }
    return out;
}

void printList(int out[]) {
    for (int el : out) {
        cout << el;
    }
    cout << endl;
}
