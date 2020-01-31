#include "Sort.h"

const int MAX = 10;

Sort::Sort(int n) {
    data.resize(n);
    count = 0;
    held = 0;
    for (int i = 1; i <= n; i++) {
        int r;
        do {
            r = rand() % n;
        } while (data[r] != 0);
        data[r] = i;
    }
//    for (int i = 0; i < n; i++) data[i] = rand() % n;
}

Sort::Sort(vector<int> v) {
    data = v;
    count = 0;
    held = 0;
}

vector<int> Sort::contents() {
    return data;
}

vector<vector<int>> Sort::step() {
    return {{0}, {0}, {0}};
}

void Sort::swap(int i, int j) {
    int ph = data[i];
    data[i] = data[j];
    data[j] = ph;
}

vector<vector<int>> Sort::tick() {
    if (held < data.size()) {
        held += 5;
//        held++;
        return {{held}};
    }
    if (count < MAX) {
        count++;
        return {{held}};
    }
    return {};
}