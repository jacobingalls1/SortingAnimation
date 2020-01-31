#include "Bubble.h"

Bubble::Bubble(int n) : Sort(n) {
    held = 0;
    last = n;
    find = 0;
}

Bubble::Bubble(vector<int> v) : Sort(v) {
    held = 0;
    last = v.size();
    find = 0;
}

vector<vector<int>> Bubble::step() {
    if (last == 0) {
        return tick();
    }
    if (held < last - 1) {
        if (data[held] > data[held + 1]) {
            swap(held, held + 1);
            find = held;
        }
        held++;
        return {{held, held + 1}, {}, {last - 1}};
    }
    vector<vector<int>> ret = {{0, 1}, {}, {last}};
    held = 0;
    last = find + 1;
    if (!find) last = 0;
    find = false;
    return ret;
}
