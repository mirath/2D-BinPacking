//#ifndef HFirstBest
//#define HFirstBest
#include "dataStructs.h"
#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Item>* getItems(int*,int,int,Packing);

Packing update(Packing,Packing);

int HFirstBest(int,Packing,int,int);
//#endif
