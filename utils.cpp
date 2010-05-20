#include "utils.h"
#include <iostream>
using namespace std;

bool compareHeight(Item a, Item b) {
  // We add the outer minus sign to get nonincreasing 
  // ordering.
  return (a.height >= b.height);
}

void init_visited(vector <Item> &items) {
  // Setting all items to not visited
  int nItems = items.size();
  for(int i = 0; i < nItems; i++) 
    items[i].visited = false;
}

// void init_coord(vector <Item> &items) {
//   vector<Item>::iterator it;
//   for(it = items.begin(); it != items.end(); it++) {
//     (*it).coord.x = 0;
//     (*it).coord.y = 0;
//   }
// }

// void init_vi_strip(vector <Strip> &sset) {
//   vector<vector<Item> > p = sset.strips;
//   vector<Item>::iterator it;
// }

int searchItem(vector<Placement> vect, int item){
  int where = -1;
  int i = 0;

  while (i < vect.size()){
    if (vect[i].item.id == item)
      where = i;
    i += 1;
  }

  return where;
}

int searchBin(vector<Placement> vect, int bin){
  int where = -1;
  int i = 0;

  while (i < vect.size()){
    if (vect[i].bin == bin)
      where = i;
    i += 1;
  }

  return where;
}

int linSlist(list<double> lst, double N){
  int where = -1;
  list<double>::iterator lstIt;
  int i = 0;

  for(lstIt=lst.begin(); lstIt != lst.end(); lstIt++){
    if (*lstIt == N)
      where = i;
    i += 1;
  }

  return where;
}

bool linS(int * arr, int N, int elem){
  bool is = false;
  int i = 0;

  while (i<N){
    is = is | arr[i]==elem;
    i += 1;
  }

  return is;
}

long factorial(int i){
  long fac = 1;

  while(i > 1){
    fac = fac*i;
    i -=1;
  }

  return fac;
}

long factorial_n(int i,int n){
  long fac = 1;

  while(i >= n){
    fac = fac*i;
    i -=1;
  }

  return fac;
}

long comb(int n, int k){
  long comb;
  comb = factorial_n(n,(n-k)+1)/factorial(k);
  return comb;
}

//Based on the class by:
//Michael Gilleland, http://www.merriampark.com/comb.htm
//Based on the algorithm by:
//Kenneth H. Rosen, Discrete Mathematics and Its Applications, 2nd edition (NY: McGraw-Hill, 1991), pp. 284-286.
int * combinations(int k, int n, int* arr){
  int i = k-1;
  int j;

  if (arr[i] < n-1)
    arr[i] += 1;
  else if (arr[0] == n-k)
    return 0;
  else{
    j = 0;
    while(arr[i] >= n-1-j && i>0){
      arr[i-1] += 1;
      i -= 1;
      j += 1;
    }

    while(i < k-1){
      arr[i+1] = arr[i]+1;
      i += 1;
    }
  }

  return arr;
}

void printPack(Packing p){
  int i = 0;

  cout<<"Total bins: ";
  cout<<p.binNum;
  cout<<"\n";
  
  // for(i=0;i<p.packing.size();++i){
  //   cout<<"------------\n";
  //   cout<<"Item: " << p.packing[i].item.id << "\n";
  //   cout<<"Bin: " << p.packing[i].bin << "\n";
  //   cout<<"Coor: " << p.packing[i].coord.x << "," << p.packing[i].coord.y << "\n";
    // cout<<"Height: " << p.packing[i].item.height << "\n";
    // cout<<"Width: " << p.packing[i].item.width << "\n";
  //}
}

//Credit: Raymond Hettinger, David Eppstein, Shane Holloway, Chris Perkins
double nth(list<double> *lst, int N){

  list<double>::iterator lstIt;
  list<double> over;
  list<double> under;

  double pivot;
  int pivotCount=0;
  int numUnder;

  while(true) {
    lstIt = lst->begin();
    pivot = *lstIt;

    pivotCount = 0;

    under.clear();
    over.clear();

    for (lstIt = lst->begin(); lstIt != lst->end(); lstIt++) {
      if (*lstIt < pivot) {
	under.push_front(*lstIt);
      }
      else if (*lstIt > pivot) {
	over.push_front(*lstIt);
      }
      else
	pivotCount += 1;
    }
    numUnder = under.size();
    if (N < numUnder)
      lst = new list<double> (under);
    else if (N < numUnder + pivotCount)
      return pivot;
    else{
      lst = new list<double> (over);
      N -= numUnder + pivotCount;
    }
  }
}
