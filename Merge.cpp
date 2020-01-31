#include "Merge.h"

bool Merge::isSorted(int min, int max) {
//    return true;
//    moves.push_back({{min, max}, {}, {}});
//    if (min + 1 == max || min == max) return true; //ph[min] >= ph[max];
//    int avg = (min + max) / 2;
//    return isSorted(min, avg) && isSorted(avg, max);
    bool ret = true;
    for (int i = min; i < max - 1; i++) {
        if (ph[i] > ph[i + 1]) ret = false;
    }
    return ret;
}

void Merge::merge(int min, int max) {
    int avg = (min + max) / 2;
    for (int i = min + avg; i < max; i++) {
        int j = min;
        for (j; ph[j] < ph[i] && j < avg; j++);
        int place = ph[i];
        ph.erase(ph.begin() + i);
        ph.insert(ph.begin() + j, place);
        moves.push_back({{}, {i, j}, {}});
    }

}

void Merge::doSort(int min, int max) {
    if (isSorted(min, max)) {
        merge(min, max);
    } else {
        int avg = (min + max) / 2;
        doSort(min, avg);
        doSort(avg, max);
    }
}

Merge::Merge(int n) : Sort(n) {
    ph = data;
    count = 0;
    moves = {};
    doSort(0, n);
}

Merge::Merge(vector<int> v) : Sort(v) {
    ph = data;
    count = 0;
    moves = {};
    doSort(0, v.size());
}

vector<vector<int>> Merge::step() {
    if (count == data.size()) return tick();
    vector<vector<int>> ret = moves[count];
    count++;
    if (!ret.empty() && !ret[1].empty()) swap(ret[1][0], ret[1][1]);
    return ret;
}