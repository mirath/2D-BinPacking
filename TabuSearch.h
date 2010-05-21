#define EPS 0.00001
#define INFINITY 1000000000
#define MAX_IT 10000 
#include "dataStructs.h"
#include "LocalSearch.h"
#include <queue>
#include "FiniteBestStrip.h"

Packing TabuSearch(vector<Item> &, int, int);
int lowerBound(int, vector<Item> &, int, int);
Packing searchtabu(int &, int &, bool &, int &, 
                   Packing &, int, int, vector<Triple> &,
                   vector<Triple>);
void diversification(int, int, int);
vector<Item> buildS(Item, Packing, int *,int, int);

