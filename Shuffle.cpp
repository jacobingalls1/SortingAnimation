#include "Shuffle.h"


Shuffle::Shuffle(int n) : Sort(n) {}
Shuffle::Shuffle(vector<int> v) : Sort(v) {}

vector<vector<int>> Shuffle::step() {
    for (int i = 0; i < 4; i++) stepIn();
    return stepIn();
}

vector<vector<int>> Shuffle::stepIn() {
    if (held != data.size()) {
        int r = rand() % (data.size());
        swap(held, r);
        held++;
        return {{}, {held - 1, r + 1}, {-1, held}};
    }
    return {};
}