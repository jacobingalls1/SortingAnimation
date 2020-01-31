#ifndef SFML_TEMPLATE_INSERTION_H
#define SFML_TEMPLATE_INSERTION_H

#include "Sort.h"

class Insertion : public Sort {
    int last;
public:
    Insertion(int n);
    Insertion(vector<int> v);
    vector<vector<int>> step();
};


#endif
