#ifndef SFML_TEMPLATE_SHUFFLE_H
#define SFML_TEMPLATE_SHUFFLE_H


#include "Sort.h"

class Shuffle : public Sort {
public:
    Shuffle(int n);
    Shuffle(vector<int> v);
    vector<vector<int>> step();
    vector<vector<int>> stepIn();
};



#endif
