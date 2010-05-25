#define EPS 0.00001
#define INFINITY 100000 
#define MAX_IT 10000  //10  mil
#define KMAX 3
#define PENCONST 500
#define DMAX 2
#include "dataStructs.h"
#include "LocalSearch.h"
#include <queue>
#include "FiniteBestStrip.h"

Packing TabuSearch(vector<Item> &, int, int);
int lowerBound(int, vector<Item> &, int, int);
void searchtabu(int &, int &, bool &, int &, 
                Packing &, int, int,
                vector<vector<Triple> > &);
void diversification(int &, int, int &, Packing &,
                     int, int,vector<vector<Triple> >);
vector<Item> buildS(Item, Packing, int *,int, int, int);
bool not_tabu(vector<vector <Triple> >, 
              Packing, int, int,int);
bool singleSet(Item, vector<Item>);
vector<Item> buildS_target(int, Packing);
void extract_item(vector<Item> &, Item);
vector<Item> operator+(vector<Item>, vector<Item>);
int targetBin_minus(Packing, int, int, int);
bool check_sol(Packing, Packing);
int deleteItem(Packing &, int);
Packing updateSol(Packing &, Packing &,int *, int, int, int);

