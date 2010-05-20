#include "dataStructs.h"
#include "utils.h"
#include <iostream>
#include <vector>
using namespace std;

Packing _FBS(vector<Item>*,int,int,Packing);

vector<Item>* getItems(int*,int,int,Packing*);

Packing * update(Packing,Packing*);

Packing* breakTie(Packing*,Packing*,int,int);

int HFirstBest(int,Packing*,int,int,int);

int HBestBest(int,Packing*,int,int,int);
