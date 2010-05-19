//#ifndef HFirstBest
//#define HFirstBest
#include "utils.h"
#include "dataStructs.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Item>* getItems(int*,int,int,Packing);

Packing update(Packing,Packing);

int HFirstBest(int,Packing,int,int);
//#endif
