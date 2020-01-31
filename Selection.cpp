#include "Selection.h"


Selection::Selection(int n) : Sort(n) {
    held = 0;
    max = 0;
    last = n;
}
Selection::Selection(vector<int> v) : Sort(v) {
    held = 0;
    max = 0;
    last = v.size();
}

vector<vector<int>> Selection::step() {
    if (last == 0) {
        return tick();
    }
    if (held < last) {
        held++;
        if (data[held] > data[max]) {
            max = held;
        }
        return {{held}, {max}, {last, data.size()}};
    }
    vector<vector<int>> ret = {{0}, {0}, {last, data.size()}};
    swap(max, last);
    held = 0;
    max = 0;
    last--;
    return ret;
}