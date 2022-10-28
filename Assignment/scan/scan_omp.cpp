#include <iostream>
#include <vector>

using namespace std;

const int length = 8;

void scan(vector<int> *out, vector<int> in) ;
void printList(vector<int> *out);

int main() {

    vector<int> set = {2, 1, 4, 0, 3, 7, 6, 3};
    vector<int> *setResults = new vector<int>(length);
    scan(setResults, set);
    printList(setResults);

    return 0;
}

void scan(vector<int> *out, vector<int> in) {
    int i =0;
    out->at(0)= in [0];
    #pragma omp parallel for scan(+: y)
    for ( i =1; i < length; i ++) {
        out->at(i)= in [ i ]+ out->at(i -1);
    }
}

void printList(vector<int> *out) {
    for (int i =0; i < length; i++) {
        cout << out->at(i) << " ";
    }

    cout << endl;
}
