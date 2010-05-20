#include "dataStructs.h"
#include "utils.h"
#include "FiniteBestStrip.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Item>* getItems(int*,int,int,Packing*);

Packing * update(Packing,Packing*,int*,int,int);

Packing* breakTie(Packing*,Packing*,int,int);

int HFirstBest(int,Packing*,int,int,int);

int HBestBest(int,Packing*,int,int,int);
