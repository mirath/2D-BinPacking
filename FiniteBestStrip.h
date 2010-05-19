using namespace std;
#include "dataStructs.h"

Packing FBS(vector <Item> &, int, int);

Packing merge_strips(vector <Strip> &,int, int);

vector<Placement> genBin(int, vector<Item>);

vector<Placement> putAbove(Strip &, int, int);

vector<Placement> operator+(vector<Placement>,
                            vector<Placement>);





