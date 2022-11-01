#include "scans.h"
#include <vector>

using namespace std;

void serial_scan(vector<int> *out, vector<int> *in) {
    int i =0;
    int length = in->size();
    out->at(0)= in->at(0);
    for ( i =1; i < length; i ++) {
        out->at(i)= in->at(i)+ out->at(i -1);
    }
}
