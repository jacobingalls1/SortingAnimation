#ifndef SFML_TEMPLATE_COCKTAIL_H
#define SFML_TEMPLATE_COCKTAIL_H

#include "Sort.h"

class Cocktail : public Sort {
    int held, first, last, find;
    bool rightward;
public:
    Cocktail(int n);
    Cocktail(vector<int> v);
    vector<vector<int>> step();
};


#endif
