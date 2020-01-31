#ifndef SFML_TEMPLATE_SELECTION_H
#define SFML_TEMPLATE_SELECTION_H

#include "Sort.h"


class Selection : public Sort {
    int held, max, last;
public:
    Selection(int n);
    Selection(vector<int> v);
    vector<vector<int>> step();
};


#endif
