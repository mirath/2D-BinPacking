//#ifndef utils
//#define utils
#include "dataStructs.h"
#include <list>

//Strip packing

bool compareHeight(Item, Item);

void init_visited(vector <Item> &);

//void init_coord(vector <Item> &);

void init_vi_strip(vector <Strip> &);


//Heuristics
int searchItem(const vector<Placement>,int);

int searchBin(const vector<Placement>,int);

bool linS(int*,int,int);

int linSlist(list<double>,double);

long factorial(int i);

long comb(int n, int k);

int * combinations(int,int,int*);

double nth(list<double>*,int);

//Others
void printPack(const Packing);

//#endif
