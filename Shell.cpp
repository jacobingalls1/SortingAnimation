#include "Shell.h"

Shell::Shell(int n) : Sort(n) {
    gap = n / 2;
    found = true;
    done = false;
    backtrack = false;
    heldPh = held;
}

Shell::Shell(vector<int> v) : Sort(v) {
    gap = v.size() / 2;
    found = true;
    done = false;
    backtrack = false;
    heldPh = 0;
}

vector<vector<int>> Shell::step() {
    if (done) return tick();
    if (held + gap < data.size()) {
        if (data[held] > data[held + gap]) {
            swap(held, held + gap);
            found = true;
            vector<vector<int>> ret = {{}, {held, held + gap}, {}};
            if (held - gap >= 0) {
                if (!backtrack) heldPh = held;
                backtrack = true;
                held -= gap;
            } else held++;
            return ret;
        }
        if (backtrack) {
//            vector<vector<int>> ret = {{}, {held + gap, held + 2 * gap}, {}};
            held = heldPh;
            backtrack = false;
            return {{held, held + gap}, {}, {}};
        }
        else held++;
        return {{held, held + gap}, {}, {}};
    } else {
        held = 0;
        if (true) {
            if (gap > 1) gap /= 2;
            else done = true;
        }
    }
    found = false;
    return {{}, {}, {}};
}