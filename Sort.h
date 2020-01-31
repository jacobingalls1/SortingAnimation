#ifndef SFML_TEMPLATE_SORT_H
#define SFML_TEMPLATE_SORT_H


#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Sort {
public:
    vector<int> data;
    int count, held;
    Sort(int n=50);
    Sort(vector<int> v);
    vector<int> virtual contents();
    vector<vector<int>> step();
    void swap(int i, int j);
    vector<vector<int>> tick();
};


#endif
