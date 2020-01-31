#include "Cocktail.h"

Cocktail::Cocktail(int n) : Sort(n) {
    held = 0;
    first = 0;
    last = n;
    find = 0;
    rightward = true;
}
Cocktail::Cocktail(vector<int> v) : Sort(v) {
    held = 0;
    first = 0;
    last = v.size();
    find = 0;
    rightward = true;
}

vector<vector<int>> Cocktail::step() {
    if (last == 0) {
        return tick();
    }
    if (rightward) {
        if (held < last - 1) {
            if (data[held] > data[held + 1]) {
                swap(held, held + 1);
                find = held;
            }
            held++;
            return {{held, held + 1}, {}, {-1, first, last - 1, (int)data.size()}};
        }
        vector<vector<int>> ret = {{0, 1}, {}, {-1, first, last - 1, (int)data.size()}};
        last = find + 1;
        held--;
        if (!find) last = 0;
        find = data.size();
        rightward = false;
        return ret;
    } else {
        if (held >= first) {
            if (data[held] > data[held + 1]) {
                swap(held, held + 1);
                find = held;
            }
            held--;
            return {{held + 2, held + 1}, {}, {-1, first, last - 1, (int)data.size()}};
        }
        vector<vector<int>> ret = {{0, 1}, {}, {-1, first, last - 1, (int)data.size()}};
        held++;
        first = find + 1;
        if (find == data.size()) last = 0;
        find = false;
        rightward = true;
        return ret;
    }
}
