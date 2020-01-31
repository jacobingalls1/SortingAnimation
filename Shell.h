#ifndef SFML_TEMPLATE_SHELL_H
#define SFML_TEMPLATE_SHELL_H


#include "Sort.h"

class Shell : public Sort {
    int gap, heldPh;
    bool found, done, backtrack;
public:
    Shell(int n);
    Shell(vector<int> v);
    vector<vector<int>> step();
};


#endif
