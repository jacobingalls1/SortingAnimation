#include "Insertion.h"

Insertion::Insertion(int n) : Sort(n) {
    last = 0;
}

Insertion::Insertion(vector<int> v) : Sort(v) {
    last = 0;
}

vector<vector<int>> Insertion::step() {
    if (last == data.size()) {
        return tick();
    }
    int ind = 0;
    for (ind; data[last] > data[ind] && ind <= last; ind++);
    int ph = data[last];
    data.erase(data.begin() + last);
    data.insert(data.begin() + ind, ph);
    last++;
    if (ind == 0) ind++;
    return {{}, {last - 1, ind - 1}, {-1, last - 1}};
}