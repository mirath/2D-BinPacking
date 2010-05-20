#include "dataStructs.h"
#include "utils.h"
#include "Heuristics.h"
#include <iostream>
#include <vector>
using namespace std;

Packing LocalSearch(vector<Item>,int,int);

int targetBin(Packing,int,int);

Packing initialPacking(vector<Item>);
