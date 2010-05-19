#include "dataStructs.h"

bool compareHeight(Item, Item);

int * combinations(int,int,int*);

void init_visited(vector <Item> &);

void init_coord(vector <Item> &);

void init_vi_strip(vector <Strip> &);

int linS(const int*,int,int);

int searchItem(const vector<Placement>,int);

void printPack(const Packing);
