#ifndef SFML_TEMPLATE_MERGE_H
#define SFML_TEMPLATE_MERGE_H

#include "Sort.h"
#include <queue>
using namespace std;

class Merge : public Sort {
    vector<vector<vector<int>>> moves;
    int count;
    vector<int> ph;
    bool isSorted(int min, int max);
    void merge(int min, int max);
    void doSort(int min, int max);
public:
    void up();
    void print();
    vector<int> range();
    Merge(int n);
    Merge(vector<int> v);
    vector<vector<int>> step();
};


#endif
