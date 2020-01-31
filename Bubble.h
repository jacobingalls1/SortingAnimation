#ifndef SFML_TEMPLATE_BUBBLE_H
#define SFML_TEMPLATE_BUBBLE_H

#include "Sort.h"


class Bubble : public Sort {
    int held, last, find;
public:
    Bubble(int n);
    Bubble(vector<int> v);
    vector<vector<int>> step();
};


#endif
