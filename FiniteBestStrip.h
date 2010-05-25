using namespace std;
#include "dataStructs.h"

Packing FBS(vector <Item> &, int, int);

Packing merge_strips(vector <Strip>*,int, int);

vector<Placement>* genBin(int, vector<Item>*, vector<Placement>*);

vector<Placement>* putAbove(Strip &, int, int, vector<Placement>*);

vector<Placement> operator+(vector<Placement>,
                            vector<Placement>);

pair<int, bool> search4others(vector<Item>,int, int,int);

pair<int,bool> search4strips(int,vector<Strip>*,int, int,
                             int);
